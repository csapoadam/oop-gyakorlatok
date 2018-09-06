// Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>
#include<ctime>
#include<cstdlib>


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

void quickSort(int* ptr, int length) {
	// random kivalasztunk egy elemet = pivot
	// (mivel kezdetben nem meghatarozott a sorrend, lehet a pivot a 0. elem)
	//
	// vegig megyunk a tombon, elore (i index) es visszafele (j index) egyszerre
	// ha talalunk olyan elem-part, ahol:
	// - a ketto kozul a tomb elejehez kozelebbi (i.) nagyobb, mint a pivot, es
	// - a ketto kozul a tomb hatuljahoz kozelebbi (j.) kisebb, mint a pivot
	// ... akkor felcsereljuk oket
	// (ha i mar nagyobb, mint j akkor nincs mit felcserelni)
	// Aztan a pivotot felcsereljuk az utolso elemmel, ami nala kisebb vagy vele egyenlo (= j utolso erteke, hiszen
	// j-t pont addig csokkentjuk, ameddig meg nagyobb az eppen j. elem, mint a pivot. Ha tortenetesen fel kell cserelni
	// az i. es j. erteket, j-t tovabb fogjuk csokkenteni, hiszen az i. elem definicio szerint nagyobb, mint a pivot)
	//
	// Es vegul meghivjuk u.ezt a fuggvenyt a pivot elotti es utani reszre

	int i, j, pivot_loc, temp;
	int first = 0;
	int last = length - 1;

	if (first < last) {
		pivot_loc = first;
		i = first;
		j = last;

		while (i < j) {
			while (ptr[i] <= ptr[pivot_loc] && i < last) {
				i++;
			}
			while (ptr[j] > ptr[pivot_loc]) {
				j--;
			}
			if (i < j) {
				temp = ptr[i];
				ptr[i] = ptr[j];
				ptr[j] = temp;
			}
		}

		temp = ptr[pivot_loc];
		ptr[pivot_loc] = ptr[j];
		ptr[j] = temp;
		quickSort(ptr + first, j - first);
		quickSort(ptr + j + 1, length - j - 1);
	}
}

int main()
{
	int tomb[] = { 4, 3, 2, 6, 2, 55, 8 };
	printTomb(tomb, 7);
	// bubbleSort(tomb, 7);
	// printTomb(tomb, 7);
	quickSort(tomb, 7);
	printTomb(tomb, 7);

	clock_t begin, end;
	srand(clock()); // init seed ido alapjan
	const int numiters = 10000;
	const int numelems = 500;
	// bubblesort 4.95 secs, quicksort 0.79 sec

	begin = clock();
	for (int i = 0; i < numiters; i++) {
		int tomb2[numelems];
		for (int j = 0; j < numelems; j++) {
			tomb2[j] = rand();
		}
		bubbleSort(tomb2, numelems);
	}
	end = clock();
	std::cout << "time for bubblesort = " << double(end - begin) / CLOCKS_PER_SEC << std::endl;

	begin = clock();
	for (int i = 0; i < numiters; i++) {
		int tomb2[numelems];
		for (int j = 0; j < numelems; j++) {
			tomb2[j] = rand();
		}
		quickSort(tomb2, numelems);
	}
	end = clock();
	std::cout << "time for quicksort = " << double(end - begin) / CLOCKS_PER_SEC << std::endl;

	char c;
	std::cin >> c;
    return 0;
}
