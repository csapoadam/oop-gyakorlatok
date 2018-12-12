// ConsoleApplication4.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>
#include "myheader1.h"
#include "myheader2.h" // now we are including myheader2 twice!
#include "arithmetics.h"

extern int bias;

int sumWithBias(int a, int b) {
	return a + b + bias;
}

int main()
{
	std::cout << "x erteke: " << x << std::endl;
	std::cout << sum(x, x) << std::endl;
	std::cout << sumWithBias(x, x) << std::endl;

	// DoubleValue* dv1 = new DoubleValue; mivel van legalabb 1 konstruktor, ez mar nem jo
	DoubleValue* dv1 = new DoubleValue(6, 5);
	std::cout << "sum and prod are: " << dv1->sum() << " and " << dv1->prod() << std::endl;

	DoubleValue dv2(*dv1); // copy constructor implemented incorrectly by default
	dv2.resetA(5);
	std::cout << "sum and prod are: " << dv1->sum() << " and " << dv1->prod() << std::endl;
	std::cout << "sum and prod are: " << dv2.sum() << " and " << dv2.prod() << std::endl; // same pointers, both are overwritten!

	std::cout << "Test copy assignment" << std::endl;
	DoubleValue dv3(7, 6);
	std::cout << "sum and prod are: " << dv3.sum() << " and " << dv3.prod() << std::endl;
	// Erdekesseg: a kovetkezo sornal 2x lefut a destruktor. Miert?
	// Meghivjuk a copy assignmentet. Letrehoz egy tmp nevu DoubleValue-t. A vegen az torlodik
	// Masreszt a copy assignmentben van egy swap. Az felhasznalja a move assignmentet, amiben szinten megszunik a 'masik' nevu valtozo.
	dv3 = dv2;
	std::cout << "sum and prod are: " << dv3.sum() << " and " << dv3.prod() << std::endl;
	dv3.resetA(7);
	std::cout << "sum and prod are: " << dv2.sum() << " and " << dv2.prod() << std::endl; // whoops!
	std::cout << "sum and prod are: " << dv3.sum() << " and " << dv3.prod() << std::endl; // whoops

	// test move assignment
	std::cout << "sum and prod are: " << dv2.sum() << " and " << dv2.prod() << std::endl; // whoops!
	std::cout << "sum and prod are: " << dv3.sum() << " and " << dv3.prod() << std::endl; // whoops
	DoubleValue dv4(std::move(dv3)); // std::move jobb oldali referenciat ad vissza!
	std::cout << "sum and prod are: " << dv4.sum() << " and " << dv4.prod() << std::endl; // whoops!
	// std::cout << "sum and prod are: " << dv3.sum() << " and " << dv3.prod() << std::endl; // whoops
	// az elozo sor exception-t dob, mivel d3 mar nem letezik!!

	delete dv1; // whoops! always delete. Forgot this earlier.

	char c;
	std::cin >> c;
    return 0;
}
