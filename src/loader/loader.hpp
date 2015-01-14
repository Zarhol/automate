#ifndef _LOADER_H_
#define _LOADER_H_

#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

#include <boost/regex.hpp>
#include <boost/format.hpp>


#include <dlfcn.h> // dlopen


#include "../core/cell.h"
#include "../core/grid.hpp"

#include "../utils/tools.h"
#include "../utils/error.h"
#include "../utils/color.h"
#include "loaderContent.h"


#define VALID_STATE_NAME "[a-zA-Z0-9_]+"
#define VALID_COORD_NAME "[0-9]*[TLBR]+"
#define OUT_NAME "./local/tmp_cmpl.cc"
#define OUT_LIB_NAME "./local/tmp_cmpl.so"

typedef enum Rule_type {
	type_rule,
	type_color
} Rule_type;

class Loader {
	private:
		void (*apply_)(Cell*, Cell**); // fonction à lancer
		bool (*color_)(Cell*); // la fonction à lancer pour récupérer la couleur à appliquer

		bool canUse_; // vrai si on peut utiliser apply
		bool canUseColor_; // vrai si on peut utiliser color_
		std::map<std::string, unsigned int> states_; // mappage des noms d'états en index
		std::map<std::string, unsigned int> colorStates_; // mappage des noms d'états de la règle de couleur
		std::map<std::pair<int, int>, unsigned int> cells_; // mappage des coordonnées des cellules en index
		std::vector<std::pair<int, int> > coords_; // coordonnées des cellules à envoyer, dans l'ordre où elles sont nécessaires
		Error err_;

		std::string ruleFunc_;
		std::string colorFunc_;
		bool isColor_;
		void* handle_;

		// renvoie les 2 parties du programme
		std::pair<std::string, std::string> defineCut(std::string const& filename, std::pair<unsigned int, unsigned int> & lines);

		// coupe la ligne à l'operateur '=>'
		std::pair<std::string, std::string> cdtCut(std::string const& line);

		// renvoie les élements de l'assignations (*:**;*:**;*:**)
		// line est le numéro de la ligne actuelle
		std::vector<std::pair<std::string, std::string> > cutSep(std::string const& asgn, unsigned int line);

		// renvoie les états activés (***,***,***)
		std::vector<std::string> cutStateAssign(std::string const& asgn, unsigned int line);

		// enregistre tous les états valides dans la def
		void retrieveStates(std::string const& states, unsigned int origin, std::map<std::string, unsigned int> & target);

		// retire les commentaires du programme
		void removeComments(std::string & prgm) const;

		// convertit la condition en sa version C
		bool normalizeCdt(std::string & cdt, unsigned int line);

		// convertit l'assignation en sa version C
		bool normalizeAsgn(std::string & cdt, unsigned int line);

		bool normalizeColor(std::string & cdt, unsigned int line);

		bool toCoord(std::string const& coord, std::pair<int, int> & c) const;

		bool toColor(std::string const& color, Color & c) const;

		int getState(std::string const& state) const; // -1 si l'état n'existe pas, son index sinon

		// retourne vrai si state peut être un nom d'état
		bool isValidStateName(std::string const& state) const;

		bool compile();
	public:
		Loader();
		explicit Loader(std::string const& pathname); // charge un fichier pathname
		~Loader();

		//bool load(std::string const& pathname); 

		bool load(std::string const& pathname, Rule_type type = type_rule);

		bool gen();

		void apply(Cell* self, Cell** near) const;

		bool applyColor(Cell* self) const;

		bool isProperlyLoaded() const;

		std::string getError();
		bool hasError() const;
		bool hasFatalError();

		unsigned int getStatesCount() const; // retourne le nombre d'état qu'une cellule peut avoir

		std::string const& getStateName(unsigned int id) const; // retourne le nom d'un état en fct de son id

		std::vector<std::pair<int, int> > const& getOrdCoords() const; // retourne les cellules à récupérer, dans l'ordre
};

#endif // _LOADER_H_