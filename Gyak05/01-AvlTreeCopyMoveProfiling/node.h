#ifndef NODE_H
#define NODE_H

#include <string>

struct Node
{
	int key;
	Node* left;
	Node* right;
	int maxDistanceToLeaf; // keep track of height of node in tree

	Node(int k, int d) : key(k), maxDistanceToLeaf(d) {
	}

	int numDigits() {
		std::string s = std::to_string(key);
		return s.length();
	}
};

#endif
