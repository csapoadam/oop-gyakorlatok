#pragma once
// #ifndef arithm_h
// #define arithm_h

#include <iostream>
#include <string>

int sum(int, int);
int prod(int, int);

class DoubleValue {
	int* a;
	int* b;
public:
	DoubleValue(int a, int b);
	~DoubleValue();
	DoubleValue(const DoubleValue& masik);
	DoubleValue(DoubleValue&& masik);
	DoubleValue& operator=(DoubleValue& masik);
	DoubleValue& operator=(DoubleValue&& masik);
	int sum() const;
	int prod() const;
	void resetA(int val);
	void print(std::string) const;
};

// #endif // !arithm_h
