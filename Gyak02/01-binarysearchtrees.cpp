// Gyak02-binarysearchtrees.cpp

#include "stdafx.h"
#include<iostream>
#include<algorithm>

struct Node
{
	int key;
	Node* left;
	Node* right;
	int maxDistanceToLeaf; // keep track of height of node in tree
};

// in order for binary trees to be efficient, they better be balanced
// AVL trees: no node in tree such that depth of left and right
// subtrees different by more than 1
struct AvlTree
{
	Node* root;
	AvlTree() {
		root = nullptr;
	}

	int nodeHeightInTree(Node* node) {
		if (node == nullptr) {
			return -1;
		} else {
			return node->maxDistanceToLeaf;
		}
	}

	Node* insertToNode(int key, Node* node) {
		// simplest case: tree still empty OR
		// node's parent still has no child in this place (left or right)
		if (node == nullptr) {
			node = new Node;
			node->key = key;
			node->left = nullptr;
			node->right = nullptr;
			node->maxDistanceToLeaf = 0;
		} //otherwise insert to left or right 
		else if (key < node->key) {
			//insert to left
			node->left = insertToNode(key, node->left);
			// tree balanced to begin with. Problems can occur only
			// when something is inserted to left or right
			if (nodeHeightInTree(node->left) - nodeHeightInTree(node->right) == 2) {
				std::cout << "Houston, we have a problem on LEFT for node with key " << node->key << std::endl;
				std::cout << "height to left is" << nodeHeightInTree(node->left) << std::endl;
				std::cout << "height to right is" << nodeHeightInTree(node->right) << std::endl;
			}
		}
		else if (key > node->key) {
			node->right = insertToNode(key, node->right);
			// tree balanced to begin with. Problems can occur only
			// when something is inserted to left or right
			if (nodeHeightInTree(node->right) - nodeHeightInTree(node->left) == 2) {
				std::cout << "Houston, we have a problem on RIGHT for node with key " << node->key << std::endl;
				std::cout << "height to left is" << nodeHeightInTree(node->left) << std::endl;
				std::cout << "height to right is" << nodeHeightInTree(node->right) << std::endl;
			}
		}
		node->maxDistanceToLeaf = std::max(
			nodeHeightInTree(node->left),
			nodeHeightInTree(node->right)
		) + 1;
		return node;
	}

	void insert(int keyToInsert) {
		// new keys can be inserted only onto a
		// specific node (= start with root)
		// always need to return node because it has
		// just been created when this function runs
		std::cout << "inserting key = " << keyToInsert << std::endl;
		root = insertToNode(keyToInsert, root);
	}

	// todo: remove and clear as well (using heap!)

	void print(Node* node) {
		if (node == nullptr) {
			return;
		}
		print(node->left);
		std::cout << node->key << ", ";
		print(node->right);
	}
};


int main()
{
	AvlTree mytree;
	mytree.insert(10);
	mytree.insert(5);
	mytree.insert(15);
	mytree.insert(7);
	mytree.insert(3);
	mytree.insert(3); //test: 2x the same?
	mytree.insert(2);
	mytree.insert(8);
	mytree.insert(1);

	std::cout << "Here is the tree, hopefully in sorted order:" << std::endl;
	mytree.print(mytree.root);
	std::cout << std::endl;

	char c;
	std::cin >> c;
    return 0;
}
