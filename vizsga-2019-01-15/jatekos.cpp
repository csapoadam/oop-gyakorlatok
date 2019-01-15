#include "stdafx.h"
#include "jatekos.h"

#include <iostream>

Jatekos::Jatekos(const std::string& name, int dateOfBirth) : name(name), dob(dateOfBirth), csapat(nullptr), currentStats(nullptr) {
}

std::string Jatekos::getName() {
	return name;
}

int Jatekos::getAge(int currentYear) {
	return currentYear - dob;
}

void Jatekos::setCsapat(Csapat* csapat) {
	this->csapat = csapat; // megoldas 2-esert
	PlayerStats* newps = new PlayerStats(); // innentol megoldas jobb jegyert
	newps->setTeam(csapat);
	if (currentStats) {
		newps->setPrevious(currentStats);
	}
	currentStats = newps;
}

Csapat* Jatekos::getCsapat() {
	//if (csapat) { // megoldas 2-esert
	//	return csapat;
	//}
	if (currentStats) {
		return currentStats->team;
	}
	return nullptr;
}

// fuggvenyek jobb jegyert
void Jatekos::gol() {
	if (currentStats) {
		currentStats->goal();
	}
}

void Jatekos::statisztika() {
	if (!currentStats) {
		std::cout << name << " hasn't played in any team yet!!" << std::endl;
	}
	else {
		std::cout << "Stats for " << name << std::endl;
		PlayerStats* curptr = currentStats;
		while (curptr) {
			std::cout << curptr->team->getName() << ": ";
			std::cout << curptr->goals << std::endl;
			curptr = curptr->previousStats;
		}
	}
}