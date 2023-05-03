#pragma once
#include"node.h"
#include<iostream>
#include"ListADT.h"
#include "process.h"
using namespace std;

class List :public ListADT <process*>
{
private:
	node<process*>* head;
	node<process*>* tail;
public:
	List()
	{
		head = nullptr;
	}

	bool is_empty()
	{
		return(head == nullptr);
	}

	void insert(process* item)
	{
		node<process*>* curr = head;
		node<process*>* newnode = new node<process*>(item);
		if (!curr) {
			head = newnode;
			tail = head;
			return;
		}
		curr = tail;
		curr->setnext(newnode);
		tail = newnode;

	}
	process* remove_id(int id)
	{
		if (is_empty()) {
			cout << "The list is empty " << endl;
			return nullptr;
		}
		else {

			node<process*>* curr;
			node<process*>* prv = nullptr;
			curr = head;
			while (curr != nullptr && curr->getitem()->get_PID() != id) {
				prv = curr;
				curr = curr->getnext();
			}
			if (curr == head) {
				head = curr->getnext();
				return curr->getitem();
			}
			if (curr) {
				prv->setnext(curr->getnext());
				return curr->getitem();
			}
			return nullptr;
		}
		return nullptr;

	}

	process* remove() {
		if (is_empty()) {
			return NULL;
		}
		else {

			node<process*>* temp = head;
			head = head->getnext();
			return temp->getitem();
		}

	}
	void print()
	{
		if (!head)
		{
			cout << "Unfortunately,it's empty";
			return;
		}

		node<process*>* temp = head;
		while (temp != NULL)
		{
			cout << temp->getitem()->get_PID();
			temp = temp->getnext();
			if (temp)
				cout << ", ";
		}
		cout << endl;
	}
	process* peek() {
		if (!head)
		{
			return nullptr;
		}
		return head->getitem();
	}
	int getlength() {
		int count = 0;
		node<process*>* temp;
		temp = head;
		while (temp != NULL) {
			count++;
			temp = temp->getnext();
		}
		return count;
	}
};