#ifndef EAST_WORLD_ENTITIES_HPP
#define EAST_WORLD_ENTITIES_HPP

#include <iostream>
#include <string>
#include <ctime>

class EastWorldEntity {
public:
	EastWorldEntity(const std::string n) : name(n) {}
	void whatsYourName() {
		std::cout << "My name is " << name << "... hello!" << std::endl;
	}
private:
	const std::string name;
	//szemelyigazolvany szam nincs, mert ilyen a robotoknak altalaban nincs
	//(kiveve fake humaneknek)
};

class Robot : public virtual EastWorldEntity { // public orokles, mert Robot egyfajta Entity!!
									   // (interfeszt oroklunk, nem implementaciot hasznalunk fel ujra / rejtunk el)
									// mivel az orokles virtualis, a Robotbol oroklo tovabbi osztalyokban garantaltan csak 1 db EastWorldEntity lesz!
									// ennek eleresehez Robot konstruktora atugorja EastWorldEntity konstruktorat (akkor, amikor Robotbol szarmazo osztalyt peldanyositunk)
									// (ha direktben Robotot peldanyositunk, mas a helyzet: az itteni konstruktor hivodik meg)
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
	ServantBot(std::string name) : Robot(name), EastWorldEntity(name) {} // mostantol itt is kell EastWorldEntity konstruktor, mivel Robot konstruktora atugorja EastWorldEntity konstrualasat!!
	void whatsYourName() { //a szuloben is van ilyen fv, attol fugg, melyiket hivjuk meg, h melyik fut le
						   // name sajnos private
						   // std::cout << "Hi Master, my name is " << name << "... what can I do for you?" << std::endl;
		std::cout << "Hi, I'm a servant bot, but I forgot my name. However, I can tell you my battery level is: " << getCharge() << std::endl;
	}
};

class BehavesLikeHuman : public virtual EastWorldEntity { // nem szarmazik EastWorldEntitybol, ld. lentebb, h miert
														  // mivel az orokles virtualis, a BehavesLikeHumanbol oroklo tovabbi osztalyokban garantaltan csak 1 db EastWorldEntity lesz!
														  // ennek eleresehez BehavesLikeHuman konstruktora atugorja EastWorldEntity konstruktorat (akkor, amikor BehavesLikeHumanbol szarmazo osztalyt peldanyositunk)
														  // (ha direktben BehavesLikeHumant peldanyositunk, mas a helyzet: az itteni konstruktor hivodik meg)
public:
	BehavesLikeHuman(std::string nid) : nationalid(nid), EastWorldEntity("Balazs") {}
private:
	const std::string nationalid;
};

class FakeHuman : public Robot, BehavesLikeHuman {
	// megj: BehavesLikeHuman azert nem szarmazik EastWorldEntitybol, mert
	// akkor Roboton es BehavesLikeHumanen keresztul FakeHuman ket kulonbozo
	// EastWorldEntity-t is tartalmazna (hires diamond shape problem)
	// Ez tulmutat a targy keretein, de veszelyes mert akkor 2 name lenne pl.
public:
	// mostantol itt is kell EastWorldEntity konstruktor, mivel Robot es BehavesLikeHuman konstruktora atugorja EastWorldEntity konstrualasat!!
	FakeHuman(std::string name, std::string nid) : Robot(name), BehavesLikeHuman(nid), EastWorldEntity("Hanna") {}
};

class Human : public BehavesLikeHuman {
public:
	// mostantol itt is kell EastWorldEntity konstruktor, mivel BehavesLikeHuman konstruktora atugorja EastWorldEntity konstrualasat!!
	Human(std::string name, std::string nid) : EastWorldEntity(name), BehavesLikeHuman(nid) {}
};

#endif // !EAST_WORLD_ENTITIES_HPP
