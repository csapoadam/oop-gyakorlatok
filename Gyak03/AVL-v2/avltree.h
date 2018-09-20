#ifndef AVLTREE_H
#define AVLTREE_H

#include "node.h"

// in order for binary trees to be efficient, they better be balanced
// AVL trees: no node in tree such that depth of left and right
// subtrees different by more than 1
struct AvlTree
{
	Node* root;
	AvlTree();
	int subtreeHeight(Node* node);
	Node* rotateRight(Node* node);
	Node* insertToNode(int key, Node* node);
	void insert(int keyToInsert);
	// todo: remove and clear as well (using heap!)
	void print(Node* node);
};

#endif