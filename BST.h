#pragma once
#include <iostream>
#include"process.h"
using namespace std;
template<typename T>
class NodeT {
public:
	T data;
	NodeT<T>* left;
	NodeT<T>* right;

	NodeT(T value) {
		data = value;
		left = right = NULL;
	}
};
template<typename T>
class BST
{
	NodeT<T>* root;
	BST() {
		root = NULL;
	}
	NodeT<T>* insert(NodeT<T>* troot, T item)
	{
		if (troot == NULL) {
			NodeT<T>* newnode = new Node{ item };
			troot = newnode;
		}
		else if (item < troot->data) {
			troot->left = insert(troot->left, item);
		}
		else if (item > troot->data) {
			troot->right = insert(troot->right, item);
		}
		return troot;
	}
	//essential
	void insert(int item) {
		root = insert(root, item);
	}

	void preorder(NodeT<T>* r) { // PLR
		if (r != NULL) {
			cout << r->data << "\t"; //process(root)
			preorder(r->left);
			preorder(r->right);
		}
		else
			return;
	}
	
	NodeT<T>* search(NodeT<T>* r, T key) {
		if (r == NULL)
			return NULL;
		if (r->data == key)
			return r;
		else if (r->data < key)
			return search(r->right, key);

		else {
			return search(r->left, key);
		}
	}
	bool search(T key) {
		root = search(root, key);
		if (root == NULL)
			return false;
		else
			return true;
	}
	//---------------------------------------------
	NodeT<T>* findmin(NodeT<T>* troot) {
		if (troot == NULL)
			return NULL;
		if (troot->left == NULL) {
			// if there is no left so the root is the smallest as the right part will be surely greater than
			return troot;
		}
		else {
			return findmin(troot->left);
		}
	}
	NodeT<T>* findmax(Node<T>* troot) {
		if (troot == NULL)
			return NULL;
		if (troot->right == NULL)
			return troot;
		else {
			return findmax(troot->right);
		}
	}
	NodeT<T>* Delete(NodeT<T>* r, T key)
	{
		if (r == NULL) // Empty Tree
			return NULL;
		if (key < r->data) // Item exists in left sub tree
			r->left = Delete(r->left, key);
		else if (key > r->data) // item exists in right sub tree
			r->right = Delete(r->right, key);
		// here I reached the target 
		else
		{
			if (r->left == NULL && r->right == NULL) // leaf node
				r = NULL;
			else if (r->left != NULL && r->right == NULL) // one child on the left
			{
				r->data = r->left->data;
				delete r->left;
				r->left = NULL;
			}
			else if (r->left == NULL && r->right != NULL) // one child on the right
			{
				r->data = r->right->data;
				delete r->right;
				r->right = NULL;
			}
			else
			{
				NodeT<T>* max = findmax(r->left);
				r->data = max->data;
				r->left = Delete(r->left, max->data);

			}

		}
		return r;
	}




};


