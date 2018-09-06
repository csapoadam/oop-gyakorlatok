// Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

int main()
{
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

