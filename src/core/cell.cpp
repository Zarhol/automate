#include "cell.h"

using namespace std;

Cell::Cell(unsigned int stateNumber) {
	changeNumberOfStates(stateNumber);
	nStates_ = 0;
	hasColor_ = false;
}

void Cell::changeNumberOfStates(unsigned int stateNumber) {
	states_.clear();
	states_.resize(stateNumber, false);
	hasColor_ = false;
}

void Cell::set(unsigned int index) {
	states_[index] = true;
	++nStates_;
	hasColor_ = false;
}

void Cell::unset(unsigned int index) {
	states_[index] = false;
	--nStates_;
	hasColor_ = false;
}

bool Cell::isSet(unsigned int index) const {
	return states_[index];
}

bool Cell::isEmpty() const {
	return nStates_ == 0;
}

unsigned int Cell::getNOfStates() const {
	return nStates_;
}

void Cell::clear() {
	unsigned int sz = states_.size();
	for(unsigned int i = 0; i != sz; ++i) {
		states_[i] = false;
	}
	hasColor_ = false;
}

void Cell::setColor(Color color) {
	color_ = color;
	hasColor_ = true;
}

Color const& Cell::getColor() const {
	return color_;
}

bool Cell::hasColor() const {
	return hasColor_;
}

void Cell::removeColor() {
	hasColor_ = false;
}