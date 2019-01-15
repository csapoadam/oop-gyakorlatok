#include "stdafx.h"
#include "csapat.h"
#include "jatekos.h"
#include <iostream>

Csapat::Csapat(const std::string& n) : name(n) {}

std::string Csapat::getName() {
	return name;
}

void Csapat::jatekosok() {
	std::cout << "***" << std::endl;
	std::cout << name << " csapat jatekosai:" << std::endl;
	for (std::vector<Jatekos*>::iterator i = players.begin(); i != players.end(); i++) {
		std::cout << (*i)->getName() << std::endl;
	}
	std::cout << "***" << std::endl;
}

void Csapat::leigazol(Jatekos* j) {
	Csapat* currentTeam = j->getCsapat();
	if (currentTeam) {
		currentTeam->elad(j);
	}
	j->setCsapat(this);
	players.push_back(j);
	goalsScored.push_back(0);
}

void Csapat::elad(Jatekos* j) {
	for (std::vector<Jatekos*>::iterator i = players.begin(); i != players.end(); i++) {
		if (*i == j) {
			players.erase(i);
			break;
		}
	}
}
