// Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>


void printTomb(int* ptr, int len) {
	std::cout << "[";
	for (int inx = 0; inx < len - 1; inx++) {
		std::cout << *(ptr + inx) << ", ";
	}
	std::cout << *(ptr + len - 1) << "]" << std::endl;
}

// sort fv., ami szamokat tartalmazo tombot sorrendez
void bubbleSort(int* ptr, int len) {
	// kulso ciklus, ami megmondja, meddig menjunk
	for (int outerlimit = len - 1; outerlimit > 0; outerlimit--) {
		//belso ciklus, ami megnezi, kell-e swappolni
		for (int comp = 0; comp < outerlimit; comp++) {
			if (ptr[comp] > ptr[comp +1]) {
				//int tmp = *(ptr + comp + 1); u.az, mint az alabbi jeloles
				int tmp = ptr[comp + 1];
				ptr[comp + 1] = ptr[comp];
				ptr[comp] = tmp;
			}
		}
	}
}

int main()
{
	int tomb[] = { 4, 3, 2, 6, 2, 55, 8 };
	printTomb(tomb, 7);
	bubbleSort(tomb, 7);
	printTomb(tomb, 7);

	char c;
	std::cin >> c;
    return 0;
}
