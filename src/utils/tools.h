#ifndef _TOOLS_H_
#define _TOOLS_H_


#include <string>

static inline void ltrim(std::string & str) {
	str.erase(0, str.find_first_not_of(" \n\r\t"));
}

static inline void rtrim(std::string & str) {
	str.erase(str.find_last_not_of(" \n\r\t") + 1);
}

static inline void trim(std::string & str) {
	ltrim(str);
	rtrim(str);
}

static void replaceAll(std::string & str, std::string const& from, std::string const& to) {
	long place = 0;
	while((place = str.find(from, place)) != std::string::npos) {
		str.replace(place, from.size(), to);
		place += to.size(); // permet de ne pas iterférer avec la partie remplacée
	}
}

static bool charEvenMatch(std::string const& str, char open, char close) {
	int pos = 0, cpt = 0;
	std::string opcl;
	opcl += open;
	opcl += close;

	while((pos = str.find_first_of(opcl, pos)) != std::string::npos) {
		if(str[pos] == open) {
			++cpt;
		}
		else {
			--cpt;
		}

		if(cpt < 0) return false;

		++pos; // on saute le charactère actuel
	}
	return cpt == 0;
}
#include <iostream>
// retourne le nombre de charactères donnés situés avant un certain point dans une string
static unsigned long countOccur(std::string const& str, std::string const& oc, unsigned long place) {
	unsigned long count = 0;
	unsigned long current = 0;
	while((current = str.find(oc, current)) != std::string::npos) {
		if(current >= place) {
			break;
		}
		current += oc.size();
		++count;
	}
	return count;
}

#endif // _TOOLS_H_