#include "stdafx.h"
#include "EastWorldEntities.h"

#include <iostream>
#include <ctime>


// ennek a fajlnak leginkabb az az ertelme, hogy ha tobb forras fajl includeolja az EastWorldEntities.h-t,
// akkor nem jo, ha abban van implementacio is. Ugyanis ha az implementacio valtozna, mindent ujra kellene forditani!!
// nagy projekteknel ennek nagy jelentosege van!

namespace EastWorld {

const int Battery::maximumCharge = 100;
const double Battery::depletionThreshold = 0.2; // ezeket ne szanaszet a kodban drotozzuk be!
const double Human::hungerThreshold = 0.2; // a legszebb, ha itt csinaljuk

void EastWorldEntity::whatsYourName() {
	std::cout << "My name is " << getName() << "... hello!" << std::endl;
}

Robot::Robot(const std::string name) : name(name) {
	setChargeRandom(); // szep!
}

const std::string Robot::getName() {
	return name;
}

void Robot::recharge() {
	chargeForRandomTime();
}

int Robot::getBatteryLevel() {
	int blevel = getCharge();
	int numGradations = 5;
	if (blevel < 1.0 / numGradations) return 1;
	if (blevel < 2.0 / numGradations) return 2;
	if (blevel < 3.0 / numGradations) return 3;
	if (blevel < 4.0 / numGradations) return 4;
	else return 5;
}

bool Robot::isDepleted() {
	return Battery::isDepleted(); // ezt is ertjuk egyben az implementacio felhasznalasa alatt. Itt most direktben hasznaljuk, de lehetne maskepp is!
	// peldaul modellezhetnenk, hogy erintkezesi hiba van, es az esetek kis szazalekaban akkor is depleted, ha valojaban az akksi nem az.
}

void Robot::tick() {
	Battery::tick(); //meg kell mondani, hogy melyik tick-et hivjunk meg, kulonben rekurziv lehet...
	// De esetunkben nem ez a problema, Robot osztalyban 2 tick() van... az egyik public a masik privat ezert ez a definicio sem feltetlenul egyertelmu
	// (persze a gyakorlatban atengedheti a fordito, mivel privat fv-t nem lehet amugy sem feluldefinialni...
}

ServantBot::ServantBot(std::string name) : Robot(name) {}

void ServantBot::whatsYourName() {
	std::cout << "Hi Master, my name is " << getName() << "... and my battery level is " << getBatteryLevel() << ". What can I do for you ? " << std::endl;
}

BehavesLikeHuman::BehavesLikeHuman(std::string nid) : nationalid(nid) {

}

const std::string BehavesLikeHuman::getNationalId() {
	return nationalid;
}

FakeHuman::FakeHuman(std::string name, std::string nid) : Robot(name), BehavesLikeHuman(nid) {

}

void FakeHuman::eat() {
	recharge();
}
void FakeHuman::whatsYourName() {
	if (isDepleted()) { //igy sokkal szebb, mert ezt a funkcionalitast hadd dontse el a Robot!
		std::cout << "My name is " << getName() << "... hello! I am hungry!" << std::endl;
	}
	else {
		std::cout << "My name is " << getName() << "... hello! Don't worry, I've had my fair share of food!" << std::endl;
	}
}

Human::Human(std::string name, std::string nid) : name(name), BehavesLikeHuman(nid) {
	hungerLevel = 1.0;
}

const std::string Human::getName() {
	return name;
}

void Human::eat() {
	hungerLevel = 1.0;
}

void Human::whatsYourName() {
	if (hungerLevel < hungerThreshold) {
		std::cout << "My name is " << getName() << "... hello! I am hungry!" << std::endl;
	}
	else {
		std::cout << "My name is " << getName() << "... hello! Don't worry, I've had my fair share of food!" << std::endl;
	}
}

void Human::tick() {
	hungerLevel *= 0.9; // az emberek csak eheznek
}

int Battery::getCharge() {
	return batteryCharge;
}

bool Battery::isDepleted() {
	return (static_cast<double>(getCharge()) / maximumCharge) < depletionThreshold;
}

void Battery::setChargeRandom() { // De elegans! Hat ez ide tartozik!!
	// most mar neve van annak, amit csinalunk: random set (korabban teljesen ossze-vissza csinaltuk amit hirtelen kigondoltunk
	// nem a robotnak kell tudnia, mi a maximum charge. Ezt az akksi tudja
	std::srand(std::clock());
	setCharge(std::rand() % maximumCharge);
}

void Battery::setCharge(int charge) {
	if (charge > maximumCharge) {
		batteryCharge = maximumCharge;
	}
	else {
		if (charge > 0) batteryCharge = charge;
	}
}

void Battery::chargeForRandomTime() {
	int potentialNewBatteryCharge = static_cast<int>(((std::rand() % 100) + 100) * batteryCharge / 100);
	batteryCharge = potentialNewBatteryCharge > maximumCharge ? maximumCharge : potentialNewBatteryCharge;
}

void Battery::tick() {
	std::cout << "battery with charge " << batteryCharge << " ticked."; // teszteles celjabol
	batteryCharge = batteryCharge > 0 ? batteryCharge - 1 : 0;
	std::cout << " New charge is: " << batteryCharge << std::endl;
}



};