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
	std::cout << sumWithBias(x, x);
	char c;
	std::cin >> c;
    return 0;
}
