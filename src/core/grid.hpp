#ifndef _GRID_H_
#define _GRID_H_

#include <map>
#include "cell.h"


class Grid {
	protected:
		std::map<std::pair<long long, long long>, Cell> grid_; // changer les coordonnées par des bigint
		unsigned int cellStates_; // nombre d'état de la cellule

	public:
		Grid(unsigned int cellStates);

		Cell & get(long long const& x, long long const& y); // retourne la cellule située à ces coordonnées. La crée si elle n'existe pas

		typedef std::map<std::pair<long long, long long>, Cell >::iterator iterator;
		typedef std::map<std::pair<long long, long long>, Cell >::const_iterator const_iterator;


		const_iterator end() const;
		iterator end();
		const_iterator begin() const;
		iterator begin();
};

#endif // _GRID_H_
