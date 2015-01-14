#ifndef _ERROR_H_
#define _ERROR_H_

#include <string>
#include <queue>
#include <map>

typedef enum Error_level {
	ERROR = 2,
	WARNING = 1,
	ADVICE = 0
} Error_level;

struct basic_error {
	std::string content;
	Error_level lvl;
};

class Error {
	protected:
		std::queue<struct basic_error> errors_;
		std::map<Error_level, std::pair<unsigned int, std::string> > data_; // pour chaque niveau d'erreur, leur nombre et la manière de l'afficher
	public:
		Error();
		void set(std::string const& error, Error_level lvl = ERROR);
		void setBeginMessage(Error_level lvl, std::string const& msg);
		std::string get(); // renvoie la première erreur et la supprime
		unsigned int getErrorsCount(Error_level lvl = ERROR);
		unsigned int getAllErrorsCount() const;
		void clear();
};

#endif // _ERROR_H_