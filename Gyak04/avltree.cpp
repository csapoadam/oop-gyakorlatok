#include "stdafx.h"
#include "avltree.h"
#include <iostream>
#include <algorithm>
#include <string>

AvlTree::AvlTree() {
	root = nullptr;
}

AvlTree::~AvlTree() {
	//az osszes new-val letrehozott pointerre kell egy delete!
	removeSubtree(root); //csinaljunk segedfv-t, mert ugyis rekurzivan meg kell hivni
}

void AvlTree::removeSubtree(Node* node) {
	if (node) {
		if (node->left) {
			removeSubtree(node->left);
		}
		if (node->right) {
			removeSubtree(node->right);
		}
		delete node;
	}
}

AvlTree::AvlTree(const AvlTree& tree) {
	// elobb megnezzuk, egytalalan van e valami a rootban
	// ha pl most hoztuk letre tree-t is, akkor a fenti constructor nullptr-re allitja a root-ot!!
	if (tree.root) { // root privat valtozo - miert
		//ferunk hozza itt a tree rootjahoz? most nem a tree objektum fv-eben vagyunk!!
		//valasz: mert az AvlTree scope-jaban vagyunk - csak ez szamit! (AvlTree::)
		root = cloneSubtree(tree.root);
	}
	else {
		root = tree.root; //vagy siman nullptr
	}
}

Node* AvlTree::cloneSubtree(Node* node) {
	Node* leftnode = nullptr; //4. sor
	Node* rightnode = nullptr; //5. sor
	//persze ezek csak akkor nullptr-ek, ha node bal es jobb gyermeke is az
	if (node->left) { //6. sor +
		leftnode = cloneSubtree(node->left);
	}
	if (node->right) {
		rightnode = cloneSubtree(node->right);
	}

	//1. sor, ami biztosan kell:
	Node* newnode = new Node(node->key, node->maxDistanceToLeaf);
	//mivel a structban minden public, key lekerdezheto
	//viszont: ilyen konstruktor meg nem letezik, csinalni kell!
	//3. sorok, amik kellenek: left es right beallitasa:
	newnode->left = leftnode;
	newnode->right = rightnode;
	return newnode; // 2. sor, ami biztosan kell
}

int AvlTree::subtreeHeight(Node* node) {
	if (node == nullptr) {
		return -1;
	}
	else {
		return node->maxDistanceToLeaf;
	}
}

Node* AvlTree::rotateLeft(Node* node) {
	Node* temp = node->right;
	node->right = node->right->left;
	temp->left = node;
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
		node = new Node(key, 0); //ha definialva van legalabb 1 konstructor, muszaj hasznalni
		// (default konstruktor nem letezik, de mar van helyette masik)
		node->left = nullptr;
		node->right = nullptr;
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
				node->left = rotateLeft(node->left);
				node = rotateRight(node);
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
				node->right = rotateRight(node->right);
				node = rotateLeft(node);
			}
			else if (key > node->right->key) {
				//right right case
				node = rotateLeft(node);
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

std::vector<Node*> AvlTree::getLayer(Node* topnode, int layer) {
	std::vector<Node*> layernodes;
	layernodes.push_back(topnode);
	for (int i = 0; i < layer; i++) {
		//first copy layernodes
		//then clear it to be able to iterate thru it
		//and insert new layer at the same time
		std::vector<Node*> tmp(layernodes);
		layernodes.clear();
		for (std::vector<Node*>::iterator iter = tmp.begin();
			iter != tmp.end();
			iter++) {
			Node* currentNode = *iter;
			if (currentNode) {
				layernodes.push_back(currentNode->left);
				layernodes.push_back(currentNode->right);
			}
			else {
				layernodes.push_back(nullptr);
				layernodes.push_back(nullptr);
			}
		}
	}
	return layernodes;
}

void AvlTree::printLayer(Node* topnode, int layer, int subtreeHeight) {
	// note: this is not very efficient, as the same layers are traversed
	// over and over again
	// would be better to keep previous layer and get the next
	std::vector<Node*> layernodes = getLayer(topnode, layer);
	int indent = std::pow(2, (subtreeHeight - layer)) - 2;
	int spacing = std::pow(2, (subtreeHeight - layer + 1));

	std::string indentStr = "";
	for (int i = 0; i < indent; i++) {
		indentStr = indentStr.append(" ");
	}
	std::cout << indentStr;

	std::string spacingStr = "";
	for (int i = 0; i < spacing; i++) {
		spacingStr = spacingStr.append(" ");
	}

	for (std::vector<Node*>::iterator i = layernodes.begin();
		i != layernodes.end();
		i++) {
		if (*i) {
			std::cout << (*i)->key;
			int newspacing = spacing - (*i)->numDigits();
			newspacing = newspacing < 1 ? 1 : newspacing;
			for (int j = 0; j < newspacing; j++) {
				std::cout << " ";
			}
		}
		else {
			std::cout << spacingStr;
		}
	}
	std::cout << std::endl;
}

void AvlTree::printSubtree(Node* node) {
	int heightOfSubtree = subtreeHeight(node);
	for (int i = 0; i < heightOfSubtree + 1; i++) {
		printLayer(node, i, heightOfSubtree);
	}
}

void AvlTree::printTree() {
	printSubtree(root);
}
