#ifndef AVLTREE_H
#define AVLTREE_H

#include "node.h"
#include <vector>

// in order for binary trees to be efficient, they better be balanced
// AVL trees: no node in tree such that depth of left and right
// subtrees different by more than 1
class AvlTree
{
private:
	Node* root;
	Node* cloneSubtree(Node*);
	int subtreeHeight(Node* node);
	Node* rotateLeft(Node* node);
	Node* rotateRight(Node* node);
	Node* insertToNode(int key, Node* node);
	// todo: remove and clear as well (using heap!)
	// ugly helper variable:
	// true if first node was printed, false otherwise
	bool firstNodeWasPrinted;
	void printKeyForNode(Node* node);
	void printSubtree(Node* node);
	void printLayer(Node* topnode, int layer, int heightOfSubtree);
	std::vector<Node*> getLayer(Node* topnode, int layer);
public:
	AvlTree();
	AvlTree(const AvlTree& tree);
	void insert(int keyToInsert);
	void printTreeAsList();
	void printTree();
};

#endif
