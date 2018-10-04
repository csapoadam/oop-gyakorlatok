#include "stdafx.h"
#include "avltree.h"
#include <vector>
#include <iostream>
#include <ctime>

AvlTree& perturbTreeCopy(AvlTree& tree) {
	tree.insert(555);
	return tree;
}

AvlTree&& perturbTreeMove(AvlTree&& tree) {
	tree.insert(555);
	return std::move(tree);
}

int main()
{
	AvlTree mytree;
	std::vector<int> numbersToInsert = {
		10, 5, 15, 7, 3, 3, 2, 8, 1, 14, 16, 17, 18, 19, 20
		// adding these numbers shows we really need to implement
		// balancing in all 4 cases!!
	};

	for (std::vector<int>::const_iterator i = numbersToInsert.begin();
		i != numbersToInsert.end();
		i++) {
		mytree.insert(*i);
	}

	std::cout << "Here is the tree, hopefully in sorted order:" << std::endl;
	mytree.printTreeAsList();
	std::cout << std::endl;
	mytree.printTree();

	std::cout << "creating mytree2" << std::endl;
	AvlTree mytree2 = mytree; //also uses copy constructor! not assignment! - at least in visual studio...
	std::cout << "creating mytree3" << std::endl;
	AvlTree mytree3(mytree2);
	std::cout << "creating mytree4" << std::endl;
	AvlTree mytree4;
	std::cout << "assigning mytree2 to mytree4" << std::endl;
	mytree4 = mytree2; // mytree4 mar letezik, ezert ez assignment
	//we need copy assignment, not just copy constructor
	// ha van destruktor, DE copy assignment meg nincs, akkor
	// kilepeskor exception-t dob (read access violation), mert
	// mytree2-t elobb torli, tehat, a mytree4-nek mar nincsenek valid pointerei!
	// mytree4 = AvlTree(); //csak akkor mukodik, ha operator= const referenciat var, mert bal oldali referencia nem lehet jobb oldali ertek!
	// wow! cout-okkal latszik, hogy a copy assignmentben a swap tmp es *this felcserelesekor ha lehet move constructort hasznal

	std::cout << "creating mytree5" << std::endl;
	//AvlTree mytree5(AvlTree()); // erre VS nem hajlando...
	AvlTree mytree5(std::move(AvlTree())); //std::move jobb oldali referenciat csinal!
	//DE csak akkor megy, ha van move constructor VAGY copy constr const refet var, ami lehet jobb oldali ertek is

	mytree2.insert(66);
	mytree.printTreeAsList();
	mytree2.printTreeAsList();
	mytree3.printTreeAsList();
	mytree4.printTreeAsList();
	mytree5.printTreeAsList();

	clock_t begin, end;
	std::srand(std::clock());
	const int numiters = 100;
	const int numelems = 10000;

	AvlTree testTree;
	for (int i=0; i<numelems; i++) {
		testTree.insert(std::rand() % (100 * numelems));
	}

	std::cout << "starting to profile" << std::endl;
	begin = clock();
	for (int i = 0; i < numiters; i++) {
		AvlTree res(testTree);
		res = perturbTreeCopy(res);
	}
	end = clock();
	std::cout << "time for " << numiters << " run(s) of perturbTreeCopy() = " <<
		double(end - begin) / CLOCKS_PER_SEC << std::endl;

	begin = clock();
	for (int i = 0; i < numiters; i++) {
		AvlTree res(testTree);
		res = perturbTreeMove(std::move(res)); // u.az mint res = perturbTreeMove(AvlTree(testTree));
	}
	end = clock();
	std::cout << "time for " << numiters << " run(s) of perturbTreeMove() = " <<
		double(end - begin) / CLOCKS_PER_SEC << std::endl;
	// ha numiters = 100, akkor copy ideje 0.012 sec, move ideje pedig 0.005
	// ha numiters=1000, akkor copy ideje 0.84 sec, move ideje pedig 0.39

	// what if
	int mytreeInt = 5;
	int mytreeInt2 = mytreeInt;
	int mytreeInt3(mytreeInt2);

	mytreeInt2 = 6;
	std::cout << "mytreeInt = " << mytreeInt << std::endl;
	std::cout << "mytreeInt2 = " << mytreeInt2 << std::endl;
	std::cout << "mytreeInt3 = " << mytreeInt3 << std::endl;

	char c;
	std::cin >> c;
	return 0;
}
