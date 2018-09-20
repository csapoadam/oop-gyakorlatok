#include "stdafx.h"
#include "avltree.h"
#include <iostream>
#include <algorithm>

AvlTree::AvlTree() {
	root = nullptr;
}

int AvlTree::subtreeHeight(Node* node) {
	if (node == nullptr) {
		return -1;
	}
	else {
		return node->maxDistanceToLeaf;
	}
}

Node* AvlTree::rotateRight(Node* node) {
	Node * temp = node->left;
	node->left = node->left->right;
	temp->right = node;
	//node is now deeper than temp, so refresh node's distanceToLeaf first
	node->maxDistanceToLeaf = std::max(
		subtreeHeight(node->left),
		subtreeHeight(node->right)
	) + 1;
	temp->maxDistanceToLeaf = std::max(
		subtreeHeight(temp->left),
		subtreeHeight(temp->right)
	) + 1;
	return temp;
}

Node* AvlTree::insertToNode(int key, Node* node) {
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
		if (subtreeHeight(node->left) - subtreeHeight(node->right) == 2) {
			std::cout << "Houston, we have a problem on LEFT for node with key " << node->key << ".";
			std::cout << "Height to left and right are " << subtreeHeight(node->left) << ", " << subtreeHeight(node->right) << std::endl;
			if (key < node->left->key) {
				//left left case
				node = rotateRight(node);
			}
			else if (key > node->left->key) {
				//left right case
				//todo...
			}
		}
	}
	else if (key > node->key) {
		node->right = insertToNode(key, node->right);
		// tree balanced to begin with. Problems can occur only
		// when something is inserted to left or right
		if (subtreeHeight(node->right) - subtreeHeight(node->left) == 2) {
			std::cout << "Houston, we have a problem on RIGHT for node with key " << node->key << ".";
			std::cout << "Height to right and left are " << subtreeHeight(node->right) << ", " << subtreeHeight(node->left) << std::endl;
			if (key < node->right->key) {
				//right left case
				//todo
			}
			else if (key > node->right->key) {
				//left right case
				//todo...
			}
		}
	}
	node->maxDistanceToLeaf = std::max(
		subtreeHeight(node->left),
		subtreeHeight(node->right)
	) + 1;
	return node;
}

void AvlTree::insert(int keyToInsert) {
	// new keys can be inserted only onto a
	// specific node (= start with root)
	// always need to return node because it has
	// just been created when this function runs
	std::cout << "inserting key = " << keyToInsert << std::endl;
	root = insertToNode(keyToInsert, root);
}

// todo: remove and clear as well (using heap!)

void AvlTree::printKeyForNode(Node* node) {
	if (node == nullptr) {
		return;
	}
	printKeyForNode(node->left);
	if (firstNodeWasPrinted) {
		std::cout << ", " << node->key;
	}
	else {
		std::cout << node->key;
		firstNodeWasPrinted = true;
	}
	printKeyForNode(node->right);
}

void AvlTree::printTreeAsList() {
	firstNodeWasPrinted = false;
	printKeyForNode(root);
	std::cout << std::endl;
}