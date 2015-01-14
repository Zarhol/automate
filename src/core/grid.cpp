#include "grid.hpp"

using namespace std;

Grid::Grid(unsigned int cellStates) {
	cellStates_ = cellStates;
}

Cell & Grid::get(long long const& x, long long const& y) {
	pair<long long, long long> coord = make_pair<long long, long long>(x, y);
	iterator it = grid_.find(coord);

	if(it == grid_.end()) {
		// cette cellule n'existe pas
		grid_[coord] = Cell(cellStates_);
		return grid_[coord];
	}
	return it->second;
}

Grid::iterator Grid::begin() {
	return grid_.begin();
}

Grid::const_iterator Grid::begin() const {
	return grid_.begin();
}

Grid::iterator Grid::end() {
	return grid_.end();
}

Grid::const_iterator Grid::end() const {
	return grid_.end();
}