// Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>
#include<vector>
#include<algorithm>
#include<string>
#include<cstdlib>
#include<ctime>

void printVector(std::vector<int> v) {
	for (std::vector<int>::const_iterator i = v.begin(); i != v.end(); i++) {
		std::cout << *i << " ";
	}
	std::cout << std::endl;
}

struct Ember {
	std::string nev;
	int eletkor;
	Ember(std::string n, int e) {
		nev = n;
		eletkor = e;
	}
	void oregit(int evek) {
		eletkor = eletkor + evek;
	}
};

void printEmberVector(std::vector<Ember> v) {
	for (std::vector<Ember>::const_iterator i = v.begin(); i != v.end(); i++) {
		std::cout << "<" << (*i).nev << ": " << (*i).eletkor << ">, ";
	}
	std::cout << std::endl;
}

bool embercomp(Ember e1, Ember e2) {
	return (e1.eletkor < e2.eletkor);
}

bool aggastyan(Ember e) {
	return (e.eletkor > 90);
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

	std::vector<Ember> embervec;
	Ember e1("Pali", 55);
	Ember e2("Zoli", 22);
	Ember e3("Anna", 33);
	embervec.push_back(e1);
	embervec.push_back(e2);
	embervec.push_back(e3);

	printEmberVector(embervec);
	std::sort(embervec.begin(), embervec.end(), embercomp);
	std::cout << "After sort:" << std::endl;
	printEmberVector(embervec);

	std::any_of(embervec.begin(), embervec.end(), aggastyan) ?
		std::cout << "Sajnos eljart felettunk az ido" << std::endl :
		std::cout << "Csak a huszeveseke a vilag" << std::endl;

	// initialize random seed
	srand(clock());
	for (std::vector<Ember>::iterator i = embervec.begin(); i != embervec.end(); i++) {
		(*i).oregit(rand());
	}

	std::cout << "after oregit" << std::endl;
	std::any_of(embervec.begin(), embervec.end(), aggastyan) ?
		std::cout << "Sajnos eljart felettunk az ido" << std::endl :
		std::cout << "Csak a huszeveseke a vilag" << std::endl;

	std::sort(embervec.begin(), embervec.end(), embercomp);
	printEmberVector(embervec);
	
	char c;
	std::cin >> c;
    return 0;
}
