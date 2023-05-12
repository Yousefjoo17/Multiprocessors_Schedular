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
class BT
{
	NodeT<T>* root;
	BT() {
		root = NULL;
	}
	NodeT<T>* insert(NodeT<T>* troot, T item)
	{
		NodeT<T>* newnode = new NodeT<T>{ item };
		if (troot == NULL) {
			troot = newnode;
		}
		else if (troot->left==nullptr) {
			troot->left = insert(troot->left, item);
		}
		else if ( troot->right==nullptr) {
			troot->right = insert(troot->right, item);
		}
		else {
			// put in left for default if I fill it before
			troot->left = insert(troot->left, item);
		}
		return troot;
	}
	//essential
	void insert(T item) {
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

};


