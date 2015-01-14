#include "core.hpp"

using namespace std;

Core Core::instance_ = Core();

Core & Core::getInstance() {
	return Core::instance_;
}

Core::Core() {
	cout << "construction du coeur" << endl;
	front_ = NULL;
	back_ = NULL;
}

Core::~Core() {
	cout << "destruction du coeur" << endl;
	if(front_ != NULL) delete front_;
	if(back_ != NULL) delete back_;
}

bool Core::load(string const& rule) {
	if(front_ != NULL) delete front_;
	if(back_ != NULL) delete back_;

	if(!rule_.load(rule)) { // on charge la règle
		return false;
	}

	if(!rule_.gen()) {
		return false;
	}

	ordinCoords_ = rule_.getOrdCoords();
	front_ = new Grid(rule_.getStatesCount());
	back_ = new Grid(rule_.getStatesCount());

	// il reste à dessiner le motif de base
	return true;
}

bool Core::load(string const& rule, string const& color) {
	if(front_ != NULL) delete front_;
	if(back_ != NULL) delete back_;

	if(!rule_.load(rule) || !rule_.load(color, type_color)) { // on charge la règle
		return false;
	}

	if(!rule_.gen()) {
		return false;
	}
	
	ordinCoords_ = rule_.getOrdCoords();
	front_ = new Grid(rule_.getStatesCount());
	back_ = new Grid(rule_.getStatesCount());

	// il reste à dessiner le motif de base
	return true;
}

bool Core::update() { // Attention, cette fonction n'est pas thread-safe !!
	Grid::iterator it = front_->begin();
	Cell** near = (Cell**)malloc(ordinCoords_.size() * sizeof(Cell*)); // le tableau de pointeur sur les cellules voisines
	long long cx, cy; // coordonnées des cellules
	if(near == NULL) {
		return false; // faudra gérer les erreurs un ptit peu
	}

	// étape 1. On parcours toute la grille actuelle (front)
	for(; it != front_->end(); ++it) {
		if(it->second.isEmpty()) continue; // on ne traite pas les cellules vides
		// doit t'on supprimer les cellules vides et les recréer à chaque itération ou pas (trop cher je pense)
		cx = it->first.first;
		cy = it->first.second;

		// on récupère dans back tous les voisins de la cellule courante dans front
		for(unsigned int i = 0; i < ordinCoords_.size(); ++i) {
			near[i] = &back_->get(cx + ordinCoords_[i].first, cy + ordinCoords_[i].second);
		}

		// on applique les changement à toutes ces cellules
		rule_.apply(&it->second, near);

		// on clear la cellule traitée
		it->second.clear();
	}

	// étape 2. on parcours toute la grille qu'on viens d'updater (back) et on assigne les couleurs
	for(it = back_->begin(); it != back_->end(); ++it) {
		if(it->second.isEmpty()) continue;
		rule_.applyColor(&it->second);
	}

	// étape 3. On swappe
	swap();

	// étape 4, on vide l'ancien front
	for(it = back_->begin(); it != back_->end(); ++it) {
		it->second.clear();
	}
	return true;
}

void Core::swap() {
	Grid * tmp = front_;
	front_ = back_;
	back_ = tmp;
}

void Core::set(long long const& x, long long const& y, unsigned int state) {
	Cell * tmp = &front_->get(x, y);
	tmp->set(state);
	rule_.applyColor(tmp); // on update la couleur de la cellule
}

void Core::set(long long const& x, long long const& y, std::vector<unsigned int> const& states) {
	Cell * tmp = &front_->get(x, y);
	for(unsigned int i = 0; i < states.size(); ++i) {
		tmp->set(states[i]);
	}
	rule_.applyColor(tmp);
}

void Core::unset(long long const& x, long long const& y, unsigned int state) {
	Cell * tmp = &front_->get(x, y);
	tmp->unset(state);
	rule_.applyColor(tmp); // on update la couleur de la cellule
}

void Core::unset(long long const& x, long long const& y, std::vector<unsigned int> const& states) {
	Cell * tmp = &front_->get(x, y);
	for(unsigned int i = 0; i < states.size(); ++i) {
		tmp->unset(states[i]);
	}
	rule_.applyColor(tmp);
}

void Core::clear() {
	if(front_ != NULL) delete front_;
	if(back_ != NULL) delete back_;
	front_ = new Grid(rule_.getStatesCount());
	back_ = new Grid(rule_.getStatesCount());
}

void Core::clear(long long const& x, long long const& y) {
	front_->get(x, y).clear();
}

bool Core::hasColor(long long const& x, long long const& y) const {
	return front_->get(x, y).hasColor();
}

Color const& Core::getColor(long long const& x, long long const& y) const {
	return front_->get(x, y).getColor();
}

string Core::getStateName(unsigned int state) {
	return rule_.getStateName(state);
}
bool Core::isInRect(const_iterator const& it, Rect const& win, Rect * toCoord) const {
	if(it->first.first < win.x || it->first.first > win.x + win.width
	|| it->first.second < win.y || it->first.second > win.y + win.height) {
		return false;
	}
	if(toCoord != NULL) {
		toCoord->x = (it->first.first - win.x);
		toCoord->y = (it->first.second - win.y);
	}
	return true;
}

Core::iterator Core::begin() {
	return front_->begin();
}

Core::const_iterator Core::begin() const {
	return front_->begin();
}

Core::iterator Core::end() {
	return front_->end();
}

Core::const_iterator Core::end() const {
	return front_->end();
}

string Core::getError() {
	return rule_.getError();
}
bool Core::hasError() const {
	return rule_.hasError();
}