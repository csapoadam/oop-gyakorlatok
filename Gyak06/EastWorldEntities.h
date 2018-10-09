#ifndef EAST_WORLD_ENTITIES_HPP
#define EAST_WORLD_ENTITIES_HPP

#include <iostream>
#include <string>
#include <ctime>

namespace EastWorld {

class EastWorldEntity {
public:
	EastWorldEntity(const std::string n) : name(n) {}
	virtual void whatsYourName() {
		std::cout << "My name is " << name << "... hello!" << std::endl;
	}
private:
	const std::string name;
	//szemelyigazolvany szam nincs, mert ilyen a robotoknak altalaban nincs
	//(kiveve fake humaneknek)
};

class Robot : public EastWorldEntity { // public orokles, mert Robot egyfajta Entity!!
									   // (interfeszt oroklunk, nem implementaciot hasznalunk fel ujra / rejtunk el)
public:
	/*
	Robot(const std::string name) {
		this->name = name; //nem jo, mert konstanst valtozot inicializalni kell!!
		//Raadasul name a szuloben private is szoval... innen nem elerheto
	};
	*/
	// minden robot objektum tartalmaz egy Entity-t is a mem.teruleten
	//tehat az entity-t is letre kell hozni
	Robot(const std::string name) : EastWorldEntity(name) {
		std::srand(std::clock()); //ha kikommentelem, mindig ugyanannyi lesz az elso, masodik, stb. charge. Ki lehet probalni!
		batteryCharge = std::rand() % maximumCharge;
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
private:
	static const int maximumCharge = 100;
	int batteryCharge; // if zero, needs to recharge!
};


class ServantBot : public Robot {
public:
	ServantBot(std::string name) : Robot(name) {}
	void whatsYourName() override { //override nem kotelezo, de ha elirjuk a szignaturat, pl. intet ad vissza, akkor a fordito szol! ezert az override hasznos
		// name sajnos private
		// std::cout << "Hi Master, my name is " << name << "... what can I do for you?" << std::endl;
		std::cout << "Hi, I'm a servant bot, but I forgot my name. However, I can tell you my battery level is: " << getCharge() << std::endl;
	}
};

class BehavesLikeHuman { // nem szarmazik EastWorldEntitybol, ld. lentebb, h miert
public:
	BehavesLikeHuman(std::string nid) : nationalid(nid) {}
private:
	const std::string nationalid;
};

class FakeHuman : public Robot, BehavesLikeHuman {
	// megj: BehavesLikeHuman azert nem szarmazik EastWorldEntitybol, mert
	// akkor Roboton es BehavesLikeHumanen keresztul FakeHuman ket kulonbozo
	// EastWorldEntity-t is tartalmazna (hires diamond shape problem)
	// Ez tulmutat a targy keretein, de veszelyes mert akkor 2 name lenne pl.
public:
	FakeHuman(std::string name, std::string nid) : Robot(name), BehavesLikeHuman(nid) {}
};

class Human : public EastWorldEntity, BehavesLikeHuman {
public:
	Human(std::string name, std::string nid) : EastWorldEntity(name), BehavesLikeHuman(nid) {}
};

}

#endif // !EAST_WORLD_ENTITIES_HPP
