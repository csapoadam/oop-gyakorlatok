// EastWorldProject.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "EastWorldEntities.h"
#include <iostream>
#include <vector>

int main() {
	EastWorldEntity ewe1("Who Am I");
	// std::cout << ewe1.name << std::endl; name private, vagyis nem hozzaferheto kivulrol
	Robot rob1("Robi");
	ServantBot sb1("Hello Bello");
	// sb1.getCharge(); protected, ezert inaccessible kivulrol
	FakeHuman fh("Tisztara Ember", "062255AB");
	Human hum("Igazi Ember", "252525PK");

	ewe1.whatsYourName();
	rob1.whatsYourName();
	sb1.whatsYourName();
	//fh.whatsYourName();
	//hum.whatsYourName();

	std::vector<EastWorldEntity*> EastWorldEntityCollection;
	EastWorldEntityCollection.push_back(&ewe1);
	EastWorldEntityCollection.push_back(&rob1);
	EastWorldEntityCollection.push_back(&sb1);
	// EastWorldEntityCollection.push_back(&fh);
	EastWorldEntityCollection.push_back(&hum);

	std::cout << "introduce entities through vector" << std::endl;
	for (std::vector<EastWorldEntity*>::iterator i = EastWorldEntityCollection.begin();
		i < EastWorldEntityCollection.end(); i++) {
		// sajnos sb1-re is EastWorldEntity whatsYourName() metodusa hivodik meg
		// a futtatasi kornyezet ugyanis nem tudja, hogy ezek valojaban nem biztos, hogy tenylegesen EastWorldEntity-k
		// hanem mondjuk ServantBot-ok vagy FakeHuman-ok is lehetnek.
		(*i)->whatsYourName(); //kovetkezo oran maskepp megoldjuk!
	}

	char c;
	std::cin >> c;
	return 0;
}
