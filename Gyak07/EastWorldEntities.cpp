#include "stdafx.h"
#include "EastWorldEntities.h"

#include <iostream>


// ennek a fajlnak leginkabb az az ertelme, hogy ha tobb forras fajl includeolja az EastWorldEntities.h-t,
// akkor nem jo, ha abban van implementacio is. Ugyanis ha az implementacio valtozna, mindent ujra kellene forditani!!
// nagy projekteknel ennek nagy jelentosege van!

namespace EastWorld {

const int Battery::maximumCharge = 100;
const double Battery::depletionThreshold = 0.2; // ezeket ne szanaszet a kodban drotozzuk be!
const double Human::hungerThreshold = 0.2; // a legszebb, ha itt csinaljuk
const double EastWorldEntity::depletionConstant = 0.9;

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

void Robot::tickWithScaling(double scaling) {
	Battery::tick(scaling); //meg kell mondani, hogy melyik tick-et hivjunk meg, kulonben rekurziv lehet...
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
	foodWeight = 0.0;
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

void FakeHuman::eatUponInvitation() {
	foodWeight += 0.1;
	std::cout << "Hello I'm " << getName() << ". I am growing heavy indeed. My foodweight is now " << foodWeight << std::endl;
}

void FakeHuman::tick() {
	Robot::tickWithScaling(1.0 + foodWeight);
	foodWeight *= depletionConstant; // legyunk igazsagosak, neha a robot hadd konnyithessen magan
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
		std::cout << "My name is " << getName() << "... hello! I am hungry! My hunger level is " << hungerLevel << std::endl;
	}
	else {
		std::cout << "My name is " << getName() << "... hello! Don't worry, I've had my fair share of food! My hunger level is " << hungerLevel << std::endl;
	}
}

void Human::inviteToEat(EastWorldEntity* ewe) {
	// ilyenkor az ember maga is eszik
	eat();
	// mivel nem tudjuk, mi is az az entity, dynamic castot hasznalunk.
	// Csak ket eset lehetseges (ServantBot-ot pl. nem lehet meghivni enni, csak az embert, vagy akirol azt hisszuk, hogy az)
	if (Human* hp = dynamic_cast<Human*>(ewe)) {
		hp->eat();
	}
	else if (FakeHuman* fh = dynamic_cast<FakeHuman*>(ewe)) {
		fh->eatUponInvitation();
	}
}

void Human::tick() {
	hungerLevel *= depletionConstant; // az emberek csak eheznek
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
		batteryCharge = static_cast<double>(maximumCharge);
	}
	else {
		if (charge > 0) batteryCharge = charge;
	}
}

void Battery::chargeForRandomTime() {
	double potentialNewBatteryCharge = static_cast<double>(((std::rand() % 100) + 100) * batteryCharge / 100);
	batteryCharge = potentialNewBatteryCharge > maximumCharge ? static_cast<double>(maximumCharge) : potentialNewBatteryCharge;
}

void Battery::tick(double scalingfactor) {
	std::cout << "battery with charge " << batteryCharge << " ticked."; // teszteles celjabol
	batteryCharge = batteryCharge > scalingfactor ? batteryCharge - scalingfactor : 0; // ha scalingfactor = 1.2, nem 1-el csokkentjuk
	std::cout << " New charge is: " << batteryCharge << std::endl;
}


};