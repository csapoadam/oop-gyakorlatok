#ifndef AVLTREE_H
#define AVLTREE_H

#include "node.h"

// in order for binary trees to be efficient, they better be balanced
// AVL trees: no node in tree such that depth of left and right
// subtrees different by more than 1
class AvlTree
{
private:
	Node* root;
	int subtreeHeight(Node* node);
	Node* rotateRight(Node* node);
	Node* insertToNode(int key, Node* node);
	// todo: remove and clear as well (using heap!)
	void printKeyForNode(Node* node);
public:
	AvlTree();
	void insert(int keyToInsert);
	void printTreeAsList();
};

#endif
