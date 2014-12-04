#include "cell.h"

using namespace std;

Cell::Cell(unsigned int stateNumber) {
	changeNumberOfStates(stateNumber);
	nStates_ = 0;
}

void Cell::changeNumberOfStates(unsigned int stateNumber) {
	states_.clear();
	states_.resize(stateNumber, 0);
}

void Cell::set(unsigned int index) {
	states_[index] = 1;
	++nStates_;
}

void Cell::unset(unsigned int index) {
	states_[index] = 0;
	--nStates_;
}

bool Cell::isSet(unsigned int index) const {
	return states_[index];
}

bool Cell::isEmpty() const {
	return nStates_ == 0;
}

void Cell::clear() {
	unsigned int sz = states_.size();
	for(unsigned int i = 0; i != sz; ++i) {
		states_[i] = 0;
	}
}