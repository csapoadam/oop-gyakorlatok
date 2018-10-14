// EastWorldProject.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "EastWorldEntities.h"
#include <iostream>
#include <vector>

// altalaban nem szeretjuk, mert ha tobb namespace-t hasznalunk akkor megintcsak name collisionok lehetnek
// using namespace EastWorld;
namespace EW = EastWorld; //namespace alias OK

int main() {
	// absztrakt osztaly nem peldanyosithato!!
	//EW::EastWorldEntity ewe1("Who Am I"); // igy nem kell mindehol kiirni, hogy EastWorld::valami
	// std::cout << ewe1.name << std::endl; name private, vagyis nem hozzaferheto kivulrol
	EW::Robot rob1("Robi");
	EW::ServantBot sb1("Hello Bello");
	// sb1.getCharge(); protected, ezert inaccessible kivulrol
	EW::FakeHuman fh("Tisztara Ember", "062255AB");
	EW::Human hum("Igazi Ember", "252525PK");

	rob1.whatsYourName();
	sb1.whatsYourName();
	fh.whatsYourName();
	hum.whatsYourName();

	rob1.tick();
	rob1.whatsYourName();

	std::vector<EW::EastWorldEntity*> EastWorldEntityCollection;
	EastWorldEntityCollection.push_back(&rob1);
	EastWorldEntityCollection.push_back(&sb1);
	EastWorldEntityCollection.push_back(&fh);
	EastWorldEntityCollection.push_back(&hum); // Human osztaly most absztrakt

	std::cout << "introduce entities through vector and ticks" << std::endl;
	char c;
	int numTicks = 100;
	for (int tick = 0; tick < numTicks; tick++) {
		for (std::vector<EW::EastWorldEntity*>::iterator i = EastWorldEntityCollection.begin();
			i < EastWorldEntityCollection.end(); i++) {
			(*i)->whatsYourName();
			(*i)->tick();
		}
		std::cout << "-----" << std::endl;
		std::cin >> c;
	}


	std::cin >> c;
	return 0;
}
