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

	DoubleValue dv1("dv1", 6, 5);
	//std::cout << "name is " << dv1.getName() << std::endl; // nem jo, mert getName() protected!!
	dv1.print();

	DoubleValue dv2(dv1);
	dv2.setName("dv2");
	dv2.resetA(5);
	std::cout << "dv2 same as dv1 except first value reset to 5" << std::endl;
	dv1.print();
	dv2.print();

	std::cout << "Test copy assignment" << std::endl;
	DoubleValue dv3("dv3", 7, 6);
	dv3.print();
	
	dv3 = dv2;
	std::cout << "after: dv3 = dv2" << std::endl;
	dv3.print();
	dv3.resetA(7);
	std::cout << "after first value of dv3 reset to 7" << std::endl;
	dv2.print();
	dv3.print();

	// test move assignment
	DoubleValue dv4(std::move(dv3)); // std::move jobb oldali referenciat ad vissza!
	dv4.setName("dv4");
	std::cout << "after DoubleValue dv4(std::move(dv3));" << std::endl;
	dv4.print();

	std::cout << "create a triple value:" << std::endl;
	TripleValue tr1("tr1", 5, 6, 7);
	tr1.print();

	/*
	ValueType vtarr[3]; // csak ha van default constructor...
	vtarr[0] = dv1;
	vtarr[1] = tr1;
	vtarr[2] = dv3;
	*/

	ValueType* vtarr[3];
	vtarr[0] = &dv1;
	vtarr[1] = &tr1;
	vtarr[2] = &dv3;

	for (int i = 0; i < 3; i++) {
		// vtarr[i].print(); // ValueType has no member print
		// vtarr[i]->print(); //ValueType has no member print
	}

	char c;
	std::cin >> c;
    return 0;
}
