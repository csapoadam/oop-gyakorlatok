#ifndef EAST_WORLD_ENTITIES_HPP
#define EAST_WORLD_ENTITIES_HPP

#include <iostream>
#include <string>
#include <ctime>

namespace EastWorld {

class EastWorldEntity {
public:
	virtual const std::string getName() = 0; //pure virtual fv: EastWorldEntity mostantol absztrakt osztaly - nem peldanyosithato!
	virtual void whatsYourName() { // absztrakt osztalynak lehet nem pure virtual fuggvenye is, de ahhoz h absztrakt legyen, legalabb 1 pure virtual fv kell
		std::cout << "My name is " << getName() << "... hello!" << std::endl;
	}
};

class Robot : public EastWorldEntity { // public orokles, mert Robot egyfajta Entity!!
									   // (interfeszt oroklunk, nem implementaciot hasznalunk fel ujra / rejtunk el)
public:
	Robot(const std::string name) : name(name) {
		std::srand(std::clock()); //ha kikommentelem, mindig ugyanannyi lesz az elso, masodik, stb. charge. Ki lehet probalni!
		batteryCharge = std::rand() % maximumCharge;
	}
	const std::string getName() override {
		return name;
	}
	void recharge(int charge) {
		if (charge > maximumCharge) {
			batteryCharge = maximumCharge;
		}
		else {
			if (charge > 0) batteryCharge = charge;
		}
	};
protected: // ez es szarmazo osztalyok elerik, de kivulrol nem lehet
	// ezzel szemben: public: szarmazo osztalyokbol ES kivulrol is elerheto
	// ezzel szemben: private: sem szarmazo osztalyokbol, sem kivulrol NEM elerheto
	// Stroustrup: protectedet csak fuggvenyekre hasznaljunk. Valtozoknal mindig kerdes, hogy miert protected??
	// ha protected -> ki fogja irni? Ha senki, miert protected?
	int getCharge() {
		return batteryCharge;
	}
	bool isDepleted() {
		return (static_cast<double>(getCharge()) / maximumCharge) < depletionThreshold;
	}
	void recharge() {
		int potentialNewBatteryCharge = static_cast<int>(((std::rand() % 100) + 100) * batteryCharge / 100);
		batteryCharge = potentialNewBatteryCharge > maximumCharge ? maximumCharge : potentialNewBatteryCharge;
	}
private:
	const std::string name;
	static const int maximumCharge = 100;
	// static const double depletionThreshold = 0.2; hopp ez nem mukodik! Ez az osztaly deklaracioja, static tagot pedig definialni kell. A const intek kivetelek
	static const double depletionThreshold;
	int batteryCharge; // if zero, needs to recharge!
};


class ServantBot : public Robot {
public:
	ServantBot(std::string name) : Robot(name) {}
	void whatsYourName() override { //override nem kotelezo, de ha elirjuk a szignaturat, pl. intet ad vissza, akkor a fordito szol! ezert az override hasznos
		// name sajnos private
		// std::cout << "Hi Master, my name is " << name << "... what can I do for you?" << std::endl;
		std::cout << "Hi Master, my name is " << getName() << "... and my battery charge is " << getCharge() << ". What can I do for you ? " << std::endl;
	}
};

class BehavesLikeHuman { // nem szarmazik EastWorldEntitybol, ld. lentebb, h miert
public:
	BehavesLikeHuman(std::string nid) : nationalid(nid) {}
	const std::string getNationalId() {
		return nationalid;
	}
	// jo lenne, ha BehavesLikeHuman se lenne peldanyosithato. Ehhez kell egy pure virtual fv.
	// kicsit most visszafele gondolkodunk (akkor csinaljunk abstract base osztalyt, ha van ertelme)... de a pelda kedveert csinaljunk egyet direkt
	virtual void eat() = 0;
private:
	const std::string nationalid;
};

class FakeHuman : public Robot, BehavesLikeHuman {
	// megj: BehavesLikeHuman azert nem szarmazik EastWorldEntitybol, mert
	// akkor Roboton es BehavesLikeHumanen keresztul FakeHuman ket kulonbozo
	// EastWorldEntity-t is tartalmazna (hires diamond shape problem)
	// Ez tulmutat a targy keretein, de veszelyes mert akkor 2 name lenne pl.
public:
	FakeHuman(std::string name, std::string nid) : Robot(name), BehavesLikeHuman(nid) {} //attol h abstract base class, meg mindig meghivhato BehavesLikeHuman(nid)!
	// (BehavesLikeHumant ekkor nem peldanyositjuk, hanem az objektum egy reszet inicializaljuk!!)
	void eat() override {
		recharge();
	}
	void whatsYourName() override {
		if (isDepleted()) { //igy sokkal szebb, mert ezt a funkcionalitast hadd dontse el a Robot!
			std::cout << "My name is " << getName() << "... hello! I am hungry!" << std::endl;
		} else {
			std::cout << "My name is " << getName() << "... hello! Don't worry, I've had my fair share of food!" << std::endl;
		}
	}
private:
	const std::string nationalid;
};

class Human : public EastWorldEntity, BehavesLikeHuman {
public:
	Human(std::string name, std::string nid) : name(name), BehavesLikeHuman(nid) {
		hungerLevel = 1.0;
	}
	const std::string getName() override {
		return name;
	}
	void eat() override {
		hungerLevel = 1.0;
	}
	void whatsYourName() override {
		if (hungerLevel < hungerThreshold) {
			std::cout << "My name is " << getName() << "... hello! I am hungry!" << std::endl;
		}
		else {
			std::cout << "My name is " << getName() << "... hello! Don't worry, I've had my fair share of food!" << std::endl;
		}
	}
private:
	const std::string name;
	double hungerLevel; // from 0 to 1
	static const double hungerThreshold;
};

const double Robot::depletionThreshold = 0.2; // ezeket ne szanaszet a kodban drotozzuk be!
const double Human::hungerThreshold = 0.2; // ezeket muszaj a classok deklaracioja utan definialni kulonben a fordito meg nem tudja mi a Robot es Human

}

#endif // !EAST_WORLD_ENTITIES_HPP
