#pragma once
#include"process.h"
#include"node.h"
#include<iostream>
#include"Queue.h"
using namespace std;

class QueueFCFS :public Queue <process*>
{

public:

	process* remove_id(int id)
	{
		if (is_empty()) {
			return nullptr;
		}
		else {
			node<process*>* curr = front;
			node<process*>* prv = nullptr;
			while (curr && curr->getitem()->get_PID() != id) {
				prv = curr;
				curr = curr->getnext();
			}
			if (!curr)
			{
				return nullptr;
			}
			else if (curr == front) {
				process* ptr = curr->getitem();
				front = curr->getnext();
				delete curr;
				return ptr;
			}
			else
			{
				process* ptr = curr->getitem();
				prv->setnext(curr->getnext());
				delete curr;
				return ptr;
			}
		}
	}

	void add2thebegining(process* ptr)
	{
		node<process*>* pn = new node<process*>(ptr);

		if (!front && !back)
			front=back = pn;
		else
		{
			pn->setnext(front);
			front = pn;
		}
		delete pn; //
	}
};
