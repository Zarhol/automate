
template<typename T>
Grid<T>::Grid(unsigned int sectionSize, T defaultValue) {
	sectionSize_ = sectionSize;
	default_ = defaultValue;

	// on initialise l'origine de la grille (la section (0, 0))
	sections_[std::make_pair<long long, long long>(0, 0)].setSize(sectionSize_, default_);
}

template<typename T>
void Grid<T>::set(long long const& x, long long const& y, T value) {	
	std::pair<long long, long long> key = std::make_pair<long long, long long>(x/sectionSize_, y/sectionSize_);
	typename std::map<std::pair<long long, long long>, GridSection<T> >::iterator it = sections_.find(key);
	
	if(it == sections_.end()) {
		// la section demandée n'existe pas, on la crée
		sections_[key].setSize(sectionSize_, default_);
		sections_[key].set(x%sectionSize_, y%sectionSize_, value); // et on assigne la valeur ou il faut dans la grille
	}
	else { // la section existe déja, on ne fait qu'y accéder
		it->second.set(x%sectionSize_, y%sectionSize_, value);
	}
}

template<typename T>
T const& Grid<T>::get(long long const& x, long long const& y) const {
	std::pair<long long, long long> key = std::make_pair<long long, long long>(x/sectionSize_, y/sectionSize_);
	typename std::map<std::pair<long long, long long>, GridSection<T> >::const_iterator it = sections_.find(key);

	if(it == sections_.end()) { // la section demandée n'existe pas
		// on ne la crée pas, on renvoie juste la valeur par défaut en lecture seule
		return default_;
	}
	return it->second.get(x%sectionSize_, y%sectionSize_); // on renvoie la véritable valeur en lecture seule
}

template<typename T>
T & Grid<T>::at(long long const& x, long long const& y) {
	std::pair<long long, long long> key = std::make_pair<long long, long long>(x/sectionSize_, y/sectionSize_);
	typename std::map<std::pair<long long, long long>, GridSection<T> >::iterator it = sections_.find(key);

	if(it == sections_.end()) { // la section demandée n'existe pas
		// on la crée
		sections_[key].setSize(sectionSize_, default_);
		return sections_[key].at(x%sectionSize_, y%sectionSize_); // on retourne la cellule demandée
	}
	else { // la section existe, on retourne la valeur directement
		return it->second.at(x%sectionSize_, y%sectionSize_);
	}
}

template<typename T>
unsigned int Grid<T>::getSectionSize() const {
	return sectionSize_;
}

template<typename T>
bool Grid<T>::existsSection(long long const& x, long long const& y) const {
	std::pair<long long, long long> key = std::make_pair<long long, long long>(x/sectionSize_, y/sectionSize_);
	typename std::map<std::pair<long long, long long>, GridSection<T> >::iterator it = sections_.find(key);
	return it != sections_.end();
}

template<typename T>
typename Grid<T>::iterator Grid<T>::begin() {
	return sections_.begin();
}

template<typename T>
typename Grid<T>::const_iterator Grid<T>::begin() const {
	return sections_.begin();
}

template<typename T>
typename Grid<T>::iterator Grid<T>::end() {
	return sections_.end();
}

template<typename T>
typename Grid<T>::const_iterator Grid<T>::end() const {
	return sections_.end();
}