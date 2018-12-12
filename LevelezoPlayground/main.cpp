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


	char c;
	std::cin >> c;
    return 0;
}
