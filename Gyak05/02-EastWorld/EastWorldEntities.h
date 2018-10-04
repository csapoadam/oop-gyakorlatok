#ifndef EAST_WORLD_ENTITIES_HPP
#define EAST_WORLD_ENTITIES_HPP

#include <iostream>
#include <string>

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
		batteryCharge = 10;
	}
	void recharge(int charge) {};
private:
	static const int maximumCharge = 100;
	int batteryCharge; // if zero, needs to recharge!
};


class ServantBot : public Robot {
public:
	ServantBot(std::string name) : Robot(name) {}
	void whatsYourName() { //a szuloben is van ilyen fv, attol fugg, melyiket hivjuk meg, h melyik fut le
		// name sajnos private
		// std::cout << "Hi Master, my name is " << name << "... what can I do for you?" << std::endl;
		std::cout << "Hi, I'm a servant bot, but I forgot my name." << std::endl;
	}
};

#endif // !EAST_WORLD_ENTITIES_HPP
