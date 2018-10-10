#include "stdafx.h"
#include "EastWorldEntities.h"

#include <iostream>
#include <ctime>


// ennek a fajlnak leginkabb az az ertelme, hogy ha tobb forras fajl includeolja az EastWorldEntities.h-t,
// akkor nem jo, ha abban van implementacio is. Ugyanis ha az implementacio valtozna, mindent ujra kellene forditani!!
// nagy projekteknel ennek nagy jelentosege van!

namespace EastWorld {

const int Robot::maximumCharge = 100;
const double Robot::depletionThreshold = 0.2; // ezeket ne szanaszet a kodban drotozzuk be!
const double Human::hungerThreshold = 0.2; // a legszebb, ha itt csinaljuk

void EastWorldEntity::whatsYourName() {
	std::cout << "My name is " << getName() << "... hello!" << std::endl;
}

Robot::Robot(const std::string) : name(name) {
	std::srand(std::clock()); //ha kikommentelem, mindig ugyanannyi lesz az elso, masodik, stb. charge. Ki lehet probalni!
	batteryCharge = std::rand() % maximumCharge;
}

const std::string Robot::getName() {
	return name;
}

void Robot::recharge(int charge) {
	if (charge > maximumCharge) {
		batteryCharge = maximumCharge;
	}
	else {
		if (charge > 0) batteryCharge = charge;
	}
}

int Robot::getCharge() {
	return batteryCharge;
}
bool Robot::isDepleted() {
	return (static_cast<double>(getCharge()) / maximumCharge) < depletionThreshold;
}
void Robot::recharge() {
	int potentialNewBatteryCharge = static_cast<int>(((std::rand() % 100) + 100) * batteryCharge / 100);
	batteryCharge = potentialNewBatteryCharge > maximumCharge ? maximumCharge : potentialNewBatteryCharge;
}

ServantBot::ServantBot(std::string name) : Robot(name) {}

void ServantBot::whatsYourName() {
	std::cout << "Hi Master, my name is " << getName() << "... and my battery charge is " << getCharge() << ". What can I do for you ? " << std::endl;
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



};