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

	DoubleValue dv1(6, 5);
	dv1.print("dv1");

	DoubleValue dv2(dv1); // copy constructor implemented incorrectly by default
	dv2.resetA(5);
	std::cout << "dv2 same as dv1 except first value reset to 5" << std::endl;
	dv1.print("dv1");
	dv2.print("dv2");

	std::cout << "Test copy assignment" << std::endl;
	DoubleValue dv3(7, 6);
	dv3.print("dv3");
	
	dv3 = dv2;
	std::cout << "after: dv3 = dv2" << std::endl;
	dv3.print("dv3");
	dv3.resetA(7);
	std::cout << "after first value of dv3 reset to 7" << std::endl;
	dv2.print("dv2");
	dv3.print("dv3");

	// test move assignment
	DoubleValue dv4(std::move(dv3)); // std::move jobb oldali referenciat ad vissza!
	std::cout << "after DoubleValue dv4(std::move(dv3));" << std::endl;
	dv4.print("dv4");

	char c;
	std::cin >> c;
    return 0;
}
