// Defines the entry point for the console application.
//
#include "stdafx.h"
#include <iostream>

void unknown(int* p, int num) {
	// p trouble 1. indexére mutat
	// num = 9
	int* q = &num; // q egy új pointer, ami num-ra mutat
	*p = *q + 2; // trouble = [9, 11, 9]
	num = 4;
}

void htf(int* p, int q, int* num) {
	// p a trouble 1. indexére mutat
	// q = 9
	// num a trouble 2. indexére mutat
	// trouble jelenleg [9, 3, 22]
	*p = q + *num; // p által mutatott érték 31
	// ergo trouble jelenleg [9, 31, 22]
	*num = q; // trouble jelenleg [9, 31, 9]
	num = p; // num mostantól trouble 1. indexére mutat
	p = &q; // p mostantól az itteni q változóra mutat (htf-q)
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
	htf(q, trouble[0], &trouble[2]); // trouble = [9, 11, 9]
	std::cout << *q << std::endl;
	std::cout << trouble[0] << std::endl;
	std::cout << trouble[1] << std::endl;
	std::cout << trouble[2] << std::endl;
	int c;
	std::cin >> c;
}
