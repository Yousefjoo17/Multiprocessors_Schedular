#pragma once
#include"prioritynode.h"
#include"priorityQueueADT.h"
#include"iostream"

using namespace std;

template<typename T>

class priorityQueue : public priorityQueueADT<T>
{
private:
	prioritynode<T>* head;
public:

	priorityQueue<T>()
	{
		head = NULL;
	}

	bool is_empty()
	{
		return !head;
	}
	void enqueue(T i, int p)
	{
		prioritynode<T>* ptr = new prioritynode<T>(i, p);
		if (!head || p > head->getpriority())
		{
			ptr->setnext(head);
			head = ptr;
		}
		else
		{
			prioritynode <T>*currptr = head;

			while (currptr->getnext() && p < currptr->getnext()->getpriority())
				currptr = currptr->getnext();
			
			prioritynode<T>* temp=currptr->getnext();
			currptr->setnext(ptr);
			ptr->setnext(temp);
		}

	}

	T dequeue()
	{
		if (is_empty())
		{
			cout << "queue underflow";
			return 0;
		}
		prioritynode<T>* temp = head;
		T val = head->getitem();
		head = head->getnext();
		delete temp;
		return val;
	}

	T peek()
	{
		if (is_empty())
		{
			cout << "queue underflow";
			return 0;
		}
		return head->getitem();
	 }

	void print()
	{
		prioritynode <T>* currptr = head;
		while (currptr!=nullptr)
		{
			cout << currptr->getitem() ;
			currptr = currptr->getnext();
			if (currptr)
				cout << ", ";
		}

	}

};

