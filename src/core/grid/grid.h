#ifndef _GRID_H_
#define _GRID_H_

#include <map>
#include "gridSection.h"

/*
*	Classe conteneur de la grille de cellules de l'automate cellulaire
*	Simulation de grille infinies.
*	Coordonnées de cellules préservées
*	vides possibles dans la grille
*/

template <typename T>
class Grid {
	protected:
		std::map<std::pair<long long, long long>, GridSection<T> > sections_; // les sections
		unsigned int sectionSize_; // la largeur des cellules
		unsigned int stateNumber_; // nombre d'état des cellules dans cette grille
		T default_; // la valeur par défaut en cas de get de truc inexistant

	public:
		/*
		*	Le constructeur par défaut (et unique constructeur possible pour Grid)
		*	sectionSize : la largeur des sections utilisées
		*	defaultValue : une valeur qui sera utilisée pour toutes les cases vides de la grille
				lors d'une demande d'accès en lecture simple
		*/
		Grid(unsigned int sectionSize, T defaultValue); 

		// pas de support des grid bounded pour le moment

		/*
		*	set permet d'assigner une valeur à un place précise de la grille
		*/
		void set(long long const& x, long long const& y, T value);

		/*
		*	get : permet d'accéder à un élément en lecture simple. Si l'élément demandé d'existe pas,
		*	la valeur par défaut spécifiée au constructeur est renvoyée, aucune cellule n'est créée
		*/
		T const& get(long long const& x, long long const& y) const; // si n'existe pas, default_ est renvoyé
		
		/*
		*	at : permet d'accéder en lecture/écriture 
		*	Si la valeur demandée n'existe pas, elle est crée
		*/
		T & at(long long const& x, long long const& y);

		// utiliser at lorsque qu'on veut modifier l'objet pointé. Get sinon

		unsigned int getSectionSize() const; // retourne la largeur des sections
		bool existsSection(long long const& x, long long const& y) const; // renvoie vrai si la SECTION (pas des coordonnées de cases, mais des coordonnées de sections) existe


		// un itérator sur la structure
		typedef typename std::map<std::pair<long long, long long>, GridSection<T> >::iterator iterator;
		typedef typename std::map<std::pair<long long, long long>, GridSection<T> >::const_iterator const_iterator;

		const_iterator end() const;
		iterator end();
		const_iterator begin() const;
		iterator begin();
};


#include "grid.tpp" // les implémentations des méthodes

#endif // _GRID_H_