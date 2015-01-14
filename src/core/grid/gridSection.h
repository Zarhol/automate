#ifndef _GRID_SECTION_H_
#define _GRID_SECTION_H_

#include <vector>

#include <iostream>

template <typename T>
class GridSection {
	protected:
		std::vector<T> cells_;
		unsigned int width_; // la largeur du carré

	public:
		GridSection();

		void setSize(unsigned int size, T defaultValue); // permet de définir la taille de la section
		// clear le contenu !!
		// size : la largeur de la section (contiendra donc size*size cellules)
		// defaultValue : la valeur des cellules vides

		void set(long long const& x, long long const& y, T & value); // change la valeur des cellules à des coordonnées données dans la section
		T const& get(long long const& x, long long const& y) const;
		T & at(long long const& x, long long const& y);

		void set(long long const& index, T & value); // même chose mais de manière linéaire (correspondant à la size du vector)
		T const& get(long long const& index) const;
		T & at(long long const& index);

};

#include "gridSection.tpp"

#endif // _GRID_SECTION_H_