
template<typename T>
GridSection<T>::GridSection() {}

template<typename T>
void GridSection<T>::setSize(unsigned int size, T defaultValue) {
	cells_.resize(size*size, defaultValue);
	width_ = size;
}

template<typename T>
void GridSection<T>::set(long long const& index, T & value) {
	cells_[index] = value;
}

template<typename T>
T const& GridSection<T>::get(long long const& index) const {
	return cells_[index];
}

template<typename T>		
T & GridSection<T>::at(long long const& index) {
	return cells_[index];
}

template<typename T>
void GridSection<T>::set(long long const& x, long long const& y, T & value) {
	cells_[width_*y + x] = value; // aucune vérification de si on est dans ou hors du vector, à l'user de faire gaffe
}

template<typename T>
T const& GridSection<T>::get(long long const& x, long long const& y) const {
	return cells_[width_*y + x];
}

template<typename T>
T & GridSection<T>::at(long long const& x, long long const& y) {
	return cells_[width_*y + x];
}