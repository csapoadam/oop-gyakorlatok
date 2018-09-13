// Gyak02-binarysearchtrees.cpp

#include "stdafx.h"
#include<iostream>

struct Node
{
	int key;
	Node* left;
	Node* right;
};

struct BinarySearchTree
{
	Node* root;
	BinarySearchTree() {
		root = nullptr;
	}
	Node* insertToNode(int key, Node* node) {
		// simplest case: tree still empty OR
		// node's parent still has no child in this place (left or right)
		if (node == nullptr) {
			node = new Node;
			node->key = key;
			node->left = nullptr;
			node->right = nullptr;
		} //otherwise insert to left or right 
		else if (key < node->key) {
			//insert to left
			node->left = insertToNode(key, node->left);
		}
		else if (key > node->key) {
			node->right = insertToNode(key, node->right);
		}
		return node;
	}

	void insert(int keyToInsert) {
		// new keys can be inserted only onto a
		// specific node (= start with root)
		// always need to return node because it has
		// just been created when this function runs
		root = insertToNode(keyToInsert, root);
	}

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
	BinarySearchTree mytree;
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

