// Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

int main()
{
	std::cout << "size of a char is " << sizeof(char) << std::endl;
	std::cout << "size of an int is " << sizeof(int) << std::endl;
	std::cout << "size of a long is " << sizeof(long) << std::endl;
	std::cout << "size of a double is " << sizeof(double) << std::endl;

	int a = 20000;
	char b = a;
	if (a != b) {
		std::cout << "implicit narrowing" << std::endl;
	}
	else {
		std::cout << "wooow!! we have big characters" << std::endl;
	}

	const double cm_per_in = 2.54;
	int val;
	char unit;
	while (std::cin >> val >> unit) {
		if (unit == 'i') {
			std::cout << val << "in =" << val * cm_per_in << "cm" << std::endl;
		}
		else if (unit == 'c') {
			std::cout << val << "cm =" << val / cm_per_in << "in" << std::endl;
		}
		else {
			return 0;
		}
	}
}
