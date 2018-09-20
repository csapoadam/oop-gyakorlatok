// Gyak03-avlrestru.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "avltree.h"
#include <vector>
#include <iostream>


int main()
{
	AvlTree mytree;
	std::vector<int> numbersToInsert = {
		10, 5, 15, 7, 3, 3, 2, 8, 1
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

	char c;
	std::cin >> c;
	return 0;
}

