#pragma once
#include"node.h"
#include"QueueADT.h"
#include"iostream"
using namespace std;
template<typename T>

class Queue : public QueueADT<T>  //first in first out
{
protected:
	node<T>* front;
	node<T>* back;
public:
	Queue()
	{
		front = NULL;
		back = NULL;
	}
	bool is_empty()
	{
		if (!front && !back)
			return true;
		return false;
	}

	void enqueue(T value)
	{
		node<T>* ptr = new node<T>(value, nullptr);
		if (is_empty())
		{
			front = ptr;
			back = ptr;
		}
		else
		{
			back->setnext(ptr);
			back = ptr;
		}
	}

	T dequeue()
	{

		if (is_empty())
			return 0;



		node<T>* ptr = front;
		T my_item = front->getitem();

		if (front == back)
		{
			front = NULL;
			back = NULL;
			delete ptr;
			return my_item;
		}
		else {
			front = front->getnext();
			delete ptr;
			return my_item;
		}
	}

	T peek()
	{
		if (is_empty())
			return 0;

		return front->getitem();
	}

	void print()
	{
		if (!front && !back)
		{
			cout << "it's empty";
			return;
		}

		node<T>* temp = front;

		while (temp != NULL)
		{
			cout << temp->getitem() ;
			temp = temp->getnext();
			if (temp)
				cout << ", ";
		}
		cout << endl;
	}
	int getlength() {
		int count = 0;
		node<T>* temp;
		temp = front;
		while (temp != NULL) {
			count++;
			temp = temp->getnext();
		}
		return count;
	}
};
