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
	std::cout << "   ... whatsYourName for fake human casted to robot:" << std::endl;
	(dynamic_cast<Robot*>(&fh))->whatsYourName();
	std::cout << "   ... whatsYourName for fake human casted to BehavesLikeHuman:" << std::endl;
	// (dynamic_cast<BehavesLikeHuman*>(&fh))->whatsYourName();
	// hum.whatsYourName(); tovabbra is ambiguous
	//(dynamic_cast<EastWorldEntity*>(&hum))->whatsYourName(); // nem egyertelmu, mert 2 db EastWorldEntity van benne!
	std::cout << "   ... whatsYourName for human casted to BehavesLikeHuman:" << std::endl;
	(dynamic_cast<BehavesLikeHuman*>(&hum))->whatsYourName(); // nem egyertelmu, mert 2 db EastWorldEntity van benne!

	std::vector<EastWorldEntity*> EastWorldEntityCollection;
	EastWorldEntityCollection.push_back(&ewe1);
	EastWorldEntityCollection.push_back(&rob1);
	EastWorldEntityCollection.push_back(&sb1);
	EastWorldEntityCollection.push_back(dynamic_cast<Robot*>(&fh)); // h mit ir ki, attol fugg, mire kasztolom
	// EastWorldEntityCollection.push_back(dynamic_cast<BehavesLikeHuman*>(&fh));
	EastWorldEntityCollection.push_back(&hum); // ugy latszik, itt egyertelmu a helyzet

	std::cout << "introduce entities through vector" << std::endl;
	for (std::vector<EastWorldEntity*>::iterator i = EastWorldEntityCollection.begin();
		i < EastWorldEntityCollection.end(); i++) {
		(*i)->whatsYourName(); //kovetkezo oran maskepp megoldjuk!
	}

	char c;
	std::cin >> c;
	return 0;
}
