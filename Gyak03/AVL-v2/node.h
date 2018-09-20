#ifndef NODE_H
#define NODE_H

struct Node
{
	int key;
	Node* left;
	Node* right;
	int maxDistanceToLeaf; // keep track of height of node in tree
};

#endif