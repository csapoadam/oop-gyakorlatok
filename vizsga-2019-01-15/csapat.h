#pragma once
#include <vector>

class Jatekos; // ez a forward deklaracio. include "jatekos.h" nem mukodik, mert az is include-olja a csapat.h-t...

class Csapat {
private:
	std::string name;
	std::vector<Jatekos*> players;
	std::vector<int> goalsScored;
	void elad(Jatekos*);
public:
	Csapat(const std::string&);
	void jatekosok();
	void leigazol(Jatekos*);
	std::string getName();
};