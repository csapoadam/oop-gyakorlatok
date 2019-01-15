#pragma once

#include<string>
#include "csapat.h"
#include "playerstats.h"

class Jatekos {
private:
	std::string name;
	int dob;
	PlayerStats* currentStats;
	Csapat* csapat;
public:
	Jatekos(const std::string&, int);
	std::string getName();
	int getAge(int currentYear);
	void setCsapat(Csapat*);
	Csapat* getCsapat();
	void gol();
	void statisztika();
};