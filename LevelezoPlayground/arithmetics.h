#pragma once
// #ifndef arithm_h
// #define arithm_h

#include <iostream>
#include <string>

int sum(int, int);
int prod(int, int);

class ValueType {
	std::string name;
protected:
	std::string getName() const {
		return name;
	}
public:
	ValueType(std::string name) {
		this->name = name;
	}
	void setName(std::string name) {
		this->name = name;
	}
	virtual ~ValueType() {
		std::cout << "Base class destructor" << std::endl;
	}
	virtual int sum() const { return 0; }
};

class DoubleValue : public ValueType { // Double Value egyfajta ValueType
	int* a;
	int* b;
public:
	DoubleValue(std::string name, int a, int b);
	~DoubleValue();
	DoubleValue(const DoubleValue& masik);
	DoubleValue(DoubleValue&& masik);
	DoubleValue& operator=(DoubleValue& masik);
	DoubleValue& operator=(DoubleValue&& masik);
	int sum() const;
	int prod() const;
	void resetA(int val);
	void print() const;
};

class TripleValue : public ValueType { // TripleValue egyfajta ValueType
	int* a;
	int* b;
	int* c;
public:
	TripleValue(std::string name, int a, int b, int c);
	~TripleValue();
	TripleValue(const TripleValue& masik) = delete; // No funny business!
	TripleValue(TripleValue&& masik) = delete;
	TripleValue& operator=(TripleValue& masik) = delete;
	TripleValue& operator=(TripleValue&& masik) = delete;
	int sum() const { return *a + *b + *c; }
	int prod() const { return *a * *b * *c; }
	void print() const;
};

// #endif // !arithm_h
