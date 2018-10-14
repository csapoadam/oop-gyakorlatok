// EastWorldProject.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "EastWorldEntities.h"
#include <iostream>
#include <vector>
#include <ctime>

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
	EW::Human hum2("Igazi Ember 2", "252525PS");

	rob1.whatsYourName();
	sb1.whatsYourName();
	fh.whatsYourName();
	hum.whatsYourName();
	hum2.whatsYourName();

	rob1.tick();
	rob1.whatsYourName();

	// std::vector<EW::EastWorldEntity*> EastWorldEntityCollection;
	char probachar = '5';
	EW::EastWorldSociety<char> soc(probachar); // nem fordul le, mivel char tipusnak nincs push_back, iterator stb. tagja!

	soc.addEntity(&rob1);
	soc.addEntity(&sb1);
	soc.addEntity(&fh);
	soc.addEntity(&hum);
	soc.addEntity(&hum2);

	char c;
	for (int i = 0; i < 100; i++) {
		soc.tickEntities();
		std::cin >> c;
	}

	std::cin >> c;
	return 0;
}
