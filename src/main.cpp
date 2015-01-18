#include "core/core.hpp"

using namespace std;

void reset(vector<string> & s, Rect const& win) {
	s.clear();
	string buf;
	for(unsigned int i = 0; i < win.height; ++i) {
		buf = "";
		for(unsigned int j = 0; j < win.width; ++j) {
			buf += " ";
		}
		s.push_back(buf);
	}
}

void fill(vector<string> & s, Core & c, Rect const& rect) {
	Core::const_iterator it = c.begin();
	Rect coord;
	for(; it != c.end(); ++it) {
		if(c.isInRect(it, rect, &coord) && it->second.hasColor()) {
			s[coord.y][coord.x] = 'x';
		}
	}
}

void disp(vector<string> const& s) {
	for(unsigned int i = 0; i < s.size(); ++i) {
		cout << s[i] << endl;
	}
}

int main(int argc, char const *argv[])
{
	Core &a = Core::getInstance();

	cout << "Compilation de la règle..." << endl;
	if(!a.load("file2.acr", "file2.acc")) {
		cout << "erreur lors du chargement. Arrêt" << endl;
		while(a.hasError()) {
			cout << a.getError() << endl;
		}
		return 1;
	}

	Rect win;
	win.x = 0;
	win.y = 0;
	win.width = 30;
	win.height = 1;
	vector<string> lines;
	a.set(0, 0, 0);// bugge avec a.set(1, 1, 0); ... je ne sais pas pourquoi

	for(unsigned int i = 0; i < 1000000; ++i) {
		reset(lines, win);
		fill(lines, a, win);
		disp(lines);
		a.update();

	}

	return 0;
}