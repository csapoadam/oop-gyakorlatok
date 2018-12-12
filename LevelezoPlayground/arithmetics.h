#pragma once
// #ifndef arithm_h
// #define arithm_h

#include <iostream>

int sum(int, int);
int prod(int, int);

class DoubleValue {
	int* a;
	int* b;
public:
	DoubleValue(int a, int b) {
		this->a = new int{ a };
		this->b = new int{ b };
	}
	~DoubleValue() {
		std::cout << "Double value destructor called" << std::endl;
		delete this->a;
		delete this->b;
	}

	DoubleValue(const DoubleValue& masik) {
		this->a = new int{ *(masik.a) };
		this->b = new int{ *(masik.b) };
	}

	DoubleValue(DoubleValue&& masik) {
		this->a = masik.a;
		this->b = masik.b;
		masik.a = nullptr;
		masik.b = nullptr;
	}

	// 2. lepes: copy assignment
	DoubleValue& operator=(DoubleValue& masik) {
		// if copy assignment fails, left-hand side variable will be left in an inconsistent state!
		DoubleValue tmp(masik); // so first we create a totally new temporary object. If this fails, no problem
		std::swap(*this, tmp); // then we swap the two
		return *this; // however, swap doesn't work without move assignment! (bc std::swap uses move semantics!)
	}

	// 1. lepes: move assignment (mivel copy assignment helyesen megvalositva szinten felhasznalja ezt!)
	// move jelentese: a jobb oldalra mar nem lesz szuksegunk!
	DoubleValue& operator=(DoubleValue&& masik) {
		delete a; // a es be felul lesz irva, ezert eloszor toroljuk a mem.teruletet, amire hivatkozik!
		delete b;
		a = new int{ *(masik.a) };
		b = new int{ *(masik.b) };
		masik.a = nullptr; // masikra mar nem lesz szuksegunk! kinullazzuk, mivel a vegen a destruktor le fog ra futni!!
		masik.b = nullptr;
		return *this;
	}

	int sum() const { // const mert nem valtoztatja az osztaly allapotat
		return *a + *b;
	}

	int prod() const {
		return *a * *b;
	}

	void resetA(int val) {
		delete a;
		a = new int{ val };
	}
};

// #endif // !arithm_h
