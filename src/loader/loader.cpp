#include "loader.hpp"

using namespace std;

Loader::Loader() {
	canUse_ = false;
	canUseColor_ = false;
	isColor_ = false;
	handle_ = NULL;
	err_.setBeginMessage(ERROR, "Erreur : ");
	err_.setBeginMessage(WARNING, "Attention : ");
	err_.setBeginMessage(ADVICE, "Conseil : ");
}

Loader::Loader(string const& pathname) {
	canUse_ = false;
	canUseColor_ = false;
	isColor_ = false;
	handle_ = NULL;
	err_.setBeginMessage(ERROR, "Erreur : ");
	err_.setBeginMessage(WARNING, "Attention : ");
	err_.setBeginMessage(ADVICE, "Conseil : ");

	load(pathname);
}

Loader::~Loader() {
	if(handle_) {
		dlclose(handle_);
	}
}

pair<string, string> Loader::defineCut(string const& filename, pair<unsigned int, unsigned int> & lines) {
	ifstream in(filename.c_str(), ifstream::in);
	if(!in.is_open()) {
		err_.set("impossible d'ouvrir le fichier source `" + filename + "`", ERROR);
		return make_pair<string, string>("", "");
	}

	string prgm((istreambuf_iterator<char>(in)), (istreambuf_iterator<char>()));
	in.close();

	removeComments(prgm);

	long defPos = prgm.find("#STATE");
	long rulePos = prgm.find("#RULE"); // peut bugger si un nom d'état contient 'RULE'

	if(defPos == string::npos) {
		err_.set("mot clé `STATE` introuvable", ERROR);
		return make_pair<string, string>("", "");
	}

	if(rulePos == string::npos) {
		err_.set("mot clé `RULE` introuvable", ERROR);
		return make_pair<string, string>("", "");
	}

	pair<string, string> ret;

	defPos = prgm.find("\n", defPos)+1; // où commence la ligne d'après STATE

	lines.first = countOccur(prgm, "\n", defPos) + 1;

	ret.first = prgm.substr(defPos, rulePos - defPos); // tout ce qui commence à la igne d'après STATE
	rulePos = prgm.find("\n", rulePos)+1; // où commence la ligne d'après RULE
	
	lines.second = countOccur(prgm, "\n", rulePos) + 1;

	ret.second = prgm.substr(rulePos);

	return ret;
}

pair<string, string> Loader::cdtCut(string const& line) {
	long place = line.find("=>");
	if(place == string::npos) {
		cout << line << endl;
		err_.set((boost::format("l%1%: opérateur => manquant") % -5).str(), ERROR);
		return make_pair<string, string>("", "");
	}
	return make_pair<string, string>(line.substr(0, place), line.substr(place+2));
}

vector<pair<string, string> > Loader::cutSep(string const& asgn, unsigned int line) {
	vector<pair<string, string> > ret;
	string buf;
	int place;
	unsigned int nAssign = 0;

	boost::regex valid("((?:\\d*[RLTBS])+:(?: |,|[a-zA-Z0-9_])+)"); // ce qui ne match pas ne renvoie pas d'erreur apr contre :/
	boost::match_results<string::const_iterator> what;
	boost::match_flag_type flags = boost::match_default;
	string::const_iterator start = asgn.begin(),
					   	   end = asgn.end();

	while(boost::regex_search(start, end, what, valid, flags)) {
		++nAssign;
		buf = string(what[0].first, what[0].second);

		place = buf.find(":");
		if(place != string::npos) {
			ret.push_back(make_pair<string, string>(buf.substr(0, place), buf.substr(place+1)));
		}
		else {
			err_.set((boost::format("l%1%: opérateur `:` manquant dans la %2%ème assignation. auto-assignation effectuée") % line % nAssign).str(), WARNING);
			ret.push_back(make_pair<string, string>("S", buf));
		}

		start = what[0].second;
	    flags |= boost::match_prev_avail;
	    flags |= boost::match_not_bob;
	}
	return ret;
}

vector<string> Loader::cutStateAssign(string const& asgn, unsigned int line) {
	vector<string> ret;
	string buf;
	boost::regex valid("([a-zA-Z0-9_]+)");
	boost::match_results<string::const_iterator> what;
	boost::match_flag_type flags = boost::match_default;
	string::const_iterator start = asgn.begin(),
					   	   end = asgn.end();
	while(boost::regex_search(start, end, what, valid, flags)) {
		buf = string(what[0].first, what[0].second);

		if(getState(buf) != -1) {
			ret.push_back(buf);
		}
		else {
			err_.set((boost::format("l%1%: `" + buf + "`, nom d'état inconnu. Vérifiez qu'il a bien été défini") % line).str());
		}

		start = what[0].second;
	    flags |= boost::match_prev_avail;
	    flags |= boost::match_not_bob;
	}
	return ret;
}

bool Loader::normalizeCdt(std::string & cdt, unsigned int line) {
	// on regarde tous les noms donnés dans la condition
	// ceux inconnus sont signalés
	boost::regex valid(VALID_STATE_NAME);
	boost::match_results<string::const_iterator> what;
	boost::match_flag_type flags = boost::match_default;
	string::const_iterator start = cdt.begin(),
						   end = cdt.end();
	string buf;
	string out;
	bool errors = false;
	int index;

	while(boost::regex_search(start, end, what, valid, flags)) {
		buf = string(what[0].first, what[0].second);

		index = getState(buf); // récupère l'id de l'état

		if(index == -1) {
			// non d'état inconnu
			err_.set((boost::format("l%1%: `" + buf + "`, nom d'état inconnu") % line).str(), ERROR);
			errors = true;
		}
		else {
			// contenu de ce qui se trouve avant la state qui a matché la regex
			out += string(start, what[0].first);
			out += (boost::format("self->isSet(%1%)") % index).str();
		}

		start = what[0].second;
    	flags |= boost::match_prev_avail;
    	flags |= boost::match_not_bob;
	}

	replaceAll(out, "&", "&&");
	replaceAll(out, "|", "||");

	boost::cmatch match;
	if(boost::regex_match(out.c_str(), match, boost::regex("(self->isSet\\([0-9]+\\)| |\\|\\||&&|!|\\(|\\))+"))) {
		// seuls les charactères autorisés sont présents dans la condition.
		if(!charEvenMatch(out, '(', ')') && !errors) { // vérification de la symétrie des parenthèses
			err_.set((boost::format("l%1%: erreur de parenthèse") % line).str(), ERROR);
			errors = true;
		}
	}
	else {
		err_.set((boost::format("l%1%: caractère non autorisé") % line).str(), ERROR);
		errors = true;
	}

	if(errors) {
		// on annule, et on retourne une chaîne qui ne pourra pas être executée
		return false;
	}

	cdt = out;
	return true;
}

bool Loader::normalizeAsgn(string & cdt, unsigned int line) {
	unsigned int errCount = err_.getAllErrorsCount();
	pair<int, int> coords;
	pair<int, int> self = make_pair<int, int>(0, 0);
	string out;
	int state;
	vector<string> cuts;
	vector<pair<string, string> > parts = cutSep(cdt, line);
	for(vector<pair<string, string> >::const_iterator it = parts.begin(); it != parts.end(); ++it) {
		if(!toCoord(it->first, coords)) {
			err_.set((boost::format("l%1%: coordonnées `" + it->first + "` invalides") % line).str(), ERROR);
			continue;
		}
		if(cells_.find(coords) == cells_.end()) {
			// coordonnées jamais utilisée
			cells_[coords] = cells_.size()-1;
			// on les ajoute dans l'ordre :
			coords_.push_back(coords);
		}

		cuts = cutStateAssign(it->second, line);
		for(vector<string>::const_iterator jt = cuts.begin(); jt != cuts.end(); ++jt) {
			// chaque état à activer dans la cellule coords
			state = getState(*jt);
			if(state == -1) {
				err_.set((boost::format("l%1%: `" + *jt + "`, nom d'état non défini. Vérifiez qu'il a bien été déclaré") % line).str(), ERROR);
				continue;
			}

			out += (boost::format("near[%1%]->set(%2%);\n") % cells_[coords] % state).str();
		}
	}

	if(err_.getAllErrorsCount() - errCount > 0) {
		// y'a eu des erreurs
		return false;
	}

	cdt = out;
	return true;
}

bool Loader::normalizeColor(string & cdt, unsigned int line) {
	unsigned int errCount = err_.getAllErrorsCount();
	Color a;
	trim(cdt);
	if(toColor(cdt, a)) {
		cdt = (boost::format("Color c;\nc.r = %1%;\nc.g = %2%;\nc.b = %3%;\nself->setColor(c);\nreturn true;") 
			% (int)a.r % (int)a.g % (int)a.b).str();
		return true;
	}
	else {
		err_.set((boost::format("l%1%: `" + cdt + "`, couleur non valide") % line).str(), ERROR);
	}
	return false;
}

bool Loader::toCoord(string const& coord, pair<int, int> & c) const {
	c = make_pair<int, int>(0, 0);

	if(coord.find("S") != string::npos) return true;

	boost::regex reg("(?:\\d*[RTBL])+");
	boost::cmatch what;

	if(boost::regex_match(coord.c_str(), what, reg)) {
		string buf;
		unsigned int val;
		reg = boost::regex("\\d*[RTBL]");
		boost::match_results<string::const_iterator> mr;
		boost::match_flag_type flags = boost::match_default;
		string::const_iterator start = coord.begin(),
						   	   end = coord.end();

		while(boost::regex_search(start, end, mr, reg, flags)) {
			buf = string(mr[0].first, mr[0].second);

			// on récupère le nombre devant le reste.
			val = atoi(buf.c_str());

			if(val == 0) val = 1; // ajout d'une seule unité de coordonné par défaut quand aucune indication
			
			// le dernier charactère de buf est notre orientation de coordonnée
			switch(buf[buf.size()-1]) {
				case 'T':
					c.second += val;
					break;
				case 'B':
					c.second -= val;
					break;
				case 'R':
					c.first += val;
					break;
				case 'L':
					c.first -= val;
					break;
			}

			start = mr[0].second;
	    	flags |= boost::match_prev_avail;
	    	flags |= boost::match_not_bob;
		}

		return true;
	}
	return false;
}

bool Loader::toColor(std::string const& color, Color & c) const {
	boost::regex reg("rgb *\\( *(\\d{1,3}) *, *(\\d{1,3}) *, *(\\d{1,3}) *\\)");
	boost::cmatch what;

	if(boost::regex_match(color.c_str(), what, reg)) {
		c.r = atoi(string(what[1].first, what[1].second).c_str());
		c.g = atoi(string(what[2].first, what[2].second).c_str());
		c.b = atoi(string(what[3].first, what[3].second).c_str());
		return true;
	}
	return false;
}

int Loader::getState(std::string const& state) const {
	map<string, unsigned int>::const_iterator t = states_.find(state);
	return (t == states_.end()) ? -1 : t->second;
}

void Loader::retrieveStates(std::string const& states, unsigned int origin, map<string, unsigned int> & target) {
	string line;
	istringstream f(states);
	while(getline(f, line)) {
		trim(line);
		if(line.empty()) continue;
		if(isValidStateName(line)) {
			target[line] = target.size() - 1; // la taille de states est incrémentée avant l'assignation
		}
		else {
			err_.set((boost::format("l%1%: `" + line + "`, nom d'état invalide") % origin).str());
		}
		++origin;
	}
}

void Loader::removeComments(std::string & prgm) const {
	boost::regex reg("(\\/\\/.[^\n]*)");
	prgm = boost::regex_replace(prgm, reg, string("")); // remplace tous les commentaire par une chaîne vide
}

bool Loader::isValidStateName(std::string const& state) const {
	boost::regex valid(VALID_STATE_NAME);
	boost::cmatch what;
	return boost::regex_match(state.c_str(), what, valid);
}

bool Loader::load(std::string const& pathname, Rule_type type) {
	switch(type) {
		case type_rule : canUse_ = false;
			states_.clear();
			colorStates_.clear();
			cells_.clear();
			coords_.clear();
			ruleFunc_ = "";
			colorFunc_ = "";
			isColor_ = false;
			break;
		case type_color : canUseColor_ = false;
						  isColor_ = false;
				colorFunc_ = "";
			break;
		default: return false;
	}
	if(handle_) {
		dlclose(handle_);
	}

	err_.clear();

	pair<unsigned int, unsigned int> lineOrigins;
	pair<string, string> def = defineCut(pathname, lineOrigins);
	retrieveStates(def.first, lineOrigins.first, (type == type_color ? colorStates_ : states_));

	string buf;
	istringstream f(def.second);

	string out;

	while(getline(f, buf)) {
		trim(buf);
		if(buf.empty()) continue;
		def = cdtCut(buf);
		if(type == type_color) {
			if(!normalizeCdt(def.first, lineOrigins.second) || !normalizeColor(def.second, lineOrigins.second)) {
				continue;
			}
		}
		else {
			if(!normalizeCdt(def.first, lineOrigins.second) || !normalizeAsgn(def.second, lineOrigins.second)) {
				continue;
			}
		}			
		out += "if(" + def.first + ") {\n" + def.second + "}\n";
		++lineOrigins.second;
	}

	if(hasError()) {
		return false;
	}

	if(type == type_rule) {
		ruleFunc_ = out;
	}
	else {
		colorFunc_ = out;
		isColor_ = true;
	}
	
	return true;
}

bool Loader::gen() {
	ofstream prgm(OUT_NAME);

	if(!prgm.is_open()) {
		err_.set("Impossible de créer le fichier source de la lib", ERROR);
		return false;
	}

	if(isColor_) {
		prgm << LOADER_PRE_CONTENT_COLOR;
		prgm << LOADER_SIGN_COLOR;
		prgm << colorFunc_;
		prgm << LOADER_POST_CONTENT_COLOR;
	}
	else {
		prgm << LOADER_PRE_CONTENT;
	}

	prgm << LOADER_SIGN_RULE;
	prgm << ruleFunc_;
	prgm << LOADER_POST_CONTENT;

	prgm.close();

	if(handle_) {
		dlclose(handle_);
	}

	if(!compile()) {
		err_.set("la compilation a échouée. Désole :/", ERROR);
		return false;
	}

	handle_ = dlopen(OUT_LIB_NAME, RTLD_LAZY);
	if(!handle_) {
		err_.set("erreur lors du chargement de la règle", ERROR);
		cout << dlerror() << endl;
		return false;
	}
	
	apply_ = (void (*)(Cell*, Cell**))dlsym(handle_, "apply");
	if(isColor_) {
		color_ = (bool (*)(Cell*))dlsym(handle_, "color");
	}

	if(dlerror()) {
		err_.set("erreur lors de l'extraction de la règle", ERROR);
		return false;
	}

	canUse_ = true;
	if(isColor_) {
		canUseColor_ = canUse_ && states_.size() == colorStates_.size();
	}
	return true;
}


bool Loader::compile() {
	boost::format a("g++ %1% -o %2% local/cell.o -shared -fPIC -ldl");
	a % OUT_NAME % OUT_LIB_NAME;
	if(system(a.str().c_str()) != 0) {
		return false;
	}
	return true;
}


void Loader::apply(Cell* self, Cell** near) const {
	if(canUse_) {
		(*apply_)(self, near);
	}
}

bool Loader::applyColor(Cell* self) const {
	if(canUseColor_ && color_ != NULL) {
		return (*color_)(self);
	}
	return false;
}

string Loader::getError() {
	return err_.get();
}

bool Loader::hasError() const {
	return err_.getAllErrorsCount() != 0;
}

bool Loader::hasFatalError() {
	return err_.getErrorsCount(ERROR);
}

bool Loader::isProperlyLoaded() const {
	return canUse_;
}

unsigned int Loader::getStatesCount() const {
	return states_.size();
}

string const& Loader::getStateName(unsigned int id) const {
	map<string, unsigned int>::const_iterator it = states_.begin();
	for(; it != states_.end(); ++it) {
		if(it->second == id) return it->first;
	}
}

vector<pair<int, int> > const& Loader::getOrdCoords() const {
	return coords_;
}