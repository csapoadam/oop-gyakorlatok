#include "stdafx.h"
#include<iostream>
#include "myheader1.h"
#include "myheader2.h" // now we are including myheader2 twice!


int main()
{	
	std::cout << "x erteke: " << x << std::endl;
	char c;
	std::cin >> c;
    return 0;
}
