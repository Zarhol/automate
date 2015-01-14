#ifndef _CELL_H_
#define _CELL_H_

#include <vector>
#include <utility> // pair
#include "../utils/color.h"


class Cell {
	protected:
		std::vector<bool> states_; // plus tard, on pourra en faire un bitset, mais là... nope
		unsigned short nStates_; // nombre d'état activés sur la cellule
		Color color_; // l'indice de la couleur de la cellule
		bool hasColor_;


		void changeNumberOfStates(unsigned int nOfStates); // permet de modifier le nomnbre d'états de la cellule

	public:
		Cell(unsigned int nOfStates = 10);
		void set(unsigned int index); //  active un état particulier (les états commencent à 0)
		void unset(unsigned int index); // désactive un état particulier
		bool isSet(unsigned int index) const; // renvoie vrai si l'état est activé
		bool isEmpty() const; // renvoie true si la cellule ne possède pas d'états
		unsigned int getNOfStates() const; // renvoie le nombre d'état total de la cellule
		void clear(); // remet tous les états à 0

		void setColor(Color c);
		Color const& getColor() const;

		bool hasColor() const;
		void removeColor(); // indique que la cellule n'a pas de couleur
};

#endif // _CELL_H_