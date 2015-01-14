#include "error.h"

using namespace std;

Error::Error() {}

void Error::set(string const& error, Error_level lvl) {
	if(data_.find(lvl) == data_.end()) {
		data_[lvl].first = 0;
	}
	basic_error e;
	e.content = error;
	e.lvl = lvl;
	++data_[lvl].first;
	errors_.push(e);
}

void Error::setBeginMessage(Error_level lvl, string const& msg) {
	if(data_.find(lvl) == data_.end()) {
		data_[lvl].first = 0;
	}
	data_[lvl].second = msg;
}

string Error::get() {
	if(!errors_.empty()) {
		string r = data_[errors_.front().lvl].second + errors_.front().content;
		--data_[errors_.front().lvl].first;
		errors_.pop();
		return r;
	}

	return "";
}

unsigned int Error::getErrorsCount(Error_level lvl) {
	if(data_.find(lvl) == data_.end()) {
		data_[lvl].first = 0;
	}
	return data_[lvl].first;
}

unsigned int Error::getAllErrorsCount() const {
	return errors_.size();
}

void Error::clear() {
	while(!errors_.empty()) errors_.pop();
	data_.clear();
}