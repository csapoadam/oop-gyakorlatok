#pragma once
// #ifndef arithm_h
// #define arithm_h

#include <iostream>
#include <string>

int sum(int, int);
int prod(int, int);


template <typename T>
class ValuePrinter {
private:
	T val;
public:
	ValuePrinter(T v) { // template osztaly minden fv-et a h fajlban kell implementalni!
		val = v; // azert, mert amikor peldanyositjuk, be kell helyettesiteni a tipust mindenhova, de a fordito egyszerre csak egy cpp fajlt lat!
	}
	void print();
};

template <typename T>
void ValuePrinter<T>::print() {
	std::cout << "value is " << val << std::endl;
}

template <>
class ValuePrinter<char> {
private:
	char val;
public:
	ValuePrinter(char v) { // template osztaly minden fv-et a h fajlban kell implementalni!
		val = v; // azert, mert amikor peldanyositjuk, be kell helyettesiteni a tipust mindenhova, de a fordito egyszerre csak egy cpp fajlt lat!
	}
	void print() {
		std::cout << "character value is " << val << std::endl;
	}
};

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
	virtual void print() const = 0;
	virtual int sum() const { return 0; }
};

class DoubleValue : public ValueType { // Double Value egyfajta ValueType
	int* a;
	int* b;
public:
	DoubleValue(std::string name, int a, int b);
	virtual ~DoubleValue(); // if parent is polymorphic, must be virtual!!
	DoubleValue(const DoubleValue& masik);
	DoubleValue(DoubleValue&& masik);
	DoubleValue& operator=(DoubleValue& masik);
	DoubleValue& operator=(DoubleValue&& masik);
	int sum() const;
	int prod() const;
	void resetA(int val);
	virtual void print() const override;
};

class TripleValue : public ValueType { // TripleValue egyfajta ValueType
	int* a;
	int* b;
	int* c;
public:
	TripleValue(std::string name, int a, int b, int c);
	virtual ~TripleValue(); // if parent is polymorphic, must be virtual!
	TripleValue(const TripleValue& masik) = delete; // No funny business!
	TripleValue(TripleValue&& masik) = delete;
	TripleValue& operator=(TripleValue& masik) = delete;
	TripleValue& operator=(TripleValue&& masik) = delete;
	int sum() const { return *a + *b + *c; }
	int prod() const { return *a * *b * *c; }
	virtual void print() const override;
	void resetC(int cval) {
		*c = cval;
	}
};

// #endif // !arithm_h
