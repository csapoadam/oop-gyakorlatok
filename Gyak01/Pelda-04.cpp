// Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>
#include<vector>
#include<algorithm>

void printVector(std::vector<int> v) {
	for (std::vector<int>::const_iterator i = v.begin(); i != v.end(); i++) {
		std::cout << *i << " ";
	}
	std::cout << std::endl;
}

int main()
{
	std::vector<int> vec;
	vec.push_back(5);
	vec.push_back(3);
	vec.push_back(88);
	vec.push_back(7);
	vec.push_back(2);
	vec.push_back(1);
	vec.push_back(1);
	vec.push_back(9);

	printVector(vec);
	std::sort(vec.begin(), vec.end());
	printVector(vec);
	
	char c;
	std::cin >> c;
    return 0;
}