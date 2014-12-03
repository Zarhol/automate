#include "grid.h"
#include <iostream>
#include "cell.h"

using namespace std;

typedef std::map<std::pair<long long, long long>, GridSection<Cell> >::iterator GridIterator;

int main(int argc, char const *argv[])
{
	Cell defaultCell(4); // on crée une cellule à 4 états (elle sera la cellule par défaut utilisée dans la grille)
	Grid<Cell> a(10, defaultCell); // on crée une grille de cellule, composée de sections de grilles de 10*10, chaque cellule ayant pour base defaultCell

	a.at(0, 0).unset(1); // on désactive l'état 1 de la cellule (0, 0)
	a.at(120, 10).set(3); // on active l'état 3 de la cellule (120, 10)
	a.at(200, 5).set(0);
	a.at(201, 6).set(2);

	cout << "0, 0 activé ? : " << a.at(0, 0).isSet(1) << endl; // vérifie si la cellule (0, 0) a son état 1 activé
	cout << "120, 10 activé ? : " << a.at(120, 10).isSet(3) << endl;

	// maintenant, on ne se déplace que dans les sections déclarées :
	Grid<Cell>::iterator it = a.begin(); // on initialise l'itérator sur la grille
	// ces itérators renvoient des GridSections
	for(; it != a.end(); ++it) {
		cout << "On a trouvé une section" << endl;
		// ici, *it vaut la section courante, elle est forcément déclarée, on peut la modifer
		// c'est ce qu'il faudra utiliser pour l'update
		int nb = 0;
		for(int i = 0; i < a.getSectionSize()*a.getSectionSize(); ++i) {
			if(!it->second.get(i).isEmpty()) {
				++nb;
			}
		}
		cout << nb << " cellules y sont déclarées" << endl;
	}
	return 0;
}