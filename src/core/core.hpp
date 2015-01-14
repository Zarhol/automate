#ifndef _CORE_H_
#define _CORE_H_

#include <string>

#include "../loader/loader.hpp"
#include "grid.hpp"
#include "cell.h"
#include "../utils/color.h"

typedef struct Rect {
	double x;
	double y;
	double width;
	double height;
} Rect;

class Core {

	protected:
		static Core instance_; // pas de pointeur... Obligation de l'utiliser

		Loader rule_;
		Grid * front_;
		Grid * back_;
		std::vector<std::pair<int, int> > ordinCoords_;

		Core();
		~Core();

		void swap();

	public:
		static Core & getInstance();

		typedef Grid::iterator iterator;
		typedef Grid::const_iterator const_iterator;

		bool load(std::string const& rule);
		bool load(std::string const& rule, std::string const& color);

		bool update(); // fait faire une itération à la grille

		// active un état d'une cellule aux coordoonées précises x,y
		void set(long long const& x, long long const& y, unsigned int state);
		void set(long long const& x, long long const& y, std::vector<unsigned int> const& states);

		// désactive un état d'une cellule aux coordoonées précises x,y
		void unset(long long const& x, long long const& y, unsigned int state);
		void unset(long long const& x, long long const& y, std::vector<unsigned int> const& states);

		void clear(); // vide la grille intégralement
		void clear(long long const& x, long long const& y); // reset une cellule

		bool hasColor(long long const& , long long const& y) const; // revoie true si la cellule a une couleur
		Color const& getColor(long long const& x, long long const& y) const;

		std::string getStateName(unsigned int state); // renvoie le nom de l'état correspondant à l'index state

		// renvoie si une cellule it est dans la fenêtre de vue win. Si oui et que coord != NULL
		// rempli coord avec sa coordonnée dans la fenêtre
		bool isInRect(const_iterator const& it, Rect const& win, Rect * toCoord = NULL) const;

		const_iterator end() const;
		iterator end();
		const_iterator begin() const;
		iterator begin();

		std::string getError();
		bool hasError() const;

};

#endif // _CORE_H_