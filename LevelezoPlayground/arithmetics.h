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

	int sum() const { // const mert nem valtoztatja az osztaly allapotat
		return *a + *b;
	}

	int prod() const {
		return *a * *b;
	}
};

// #endif // !arithm_h
