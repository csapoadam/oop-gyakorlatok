// EastWorldProject.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "EastWorldEntities.h"
#include <iostream>

int main() {
	EastWorldEntity ewe1("Who Am I");
	// std::cout << ewe1.name << std::endl; name private, vagyis nem hozzaferheto kivulrol
	Robot rob1("Robi");
	ServantBot sb1("Hello Bello");

	ewe1.whatsYourName();
	rob1.whatsYourName();
	sb1.whatsYourName();

	char c;
	std::cin >> c;
    return 0;
}
