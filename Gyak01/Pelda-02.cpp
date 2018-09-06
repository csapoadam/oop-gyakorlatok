// Defines the entry point for the console application.
//
#include "stdafx.h"
#include <iostream>

void unknown(int* p, int num) {
	int* q = &num;
	*p = *q + 2;
	num = 4;
}

void htf(int* p, int q, int* num) {
	*p = q + *num;
	*num = q;
	num = p;
	p = &q;
	unknown(num, *p);
}

int main()
{
	int* q;
	int trouble[3];
	trouble[0] = 9;
	q = &trouble[1];
	*q = 3;
	trouble[2] = 22;
	htf(q, trouble[0], &trouble[2]);
	std::cout << *q << std::endl;
	std::cout << trouble[0] << std::endl;
	std::cout << trouble[1] << std::endl;
	std::cout << trouble[2] << std::endl;
	int c;
	std::cin >> c;
}
