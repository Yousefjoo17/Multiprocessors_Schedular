#pragma once
#include"iostream"
using namespace std;

template<typename T>

class prioritynode
{
private:
	T item;
	prioritynode* next;
	int priority;
public:
	prioritynode()
	{
		setnext(NULL);
	}
	prioritynode(T i, int p)
	{
		setitem(i);
		setpriority(p);
		setnext(NULL);
	}
	void setitem(T i)
	{
		item = i;
	}
	T getitem()
	{
		return item;
	}
	void setnext(prioritynode* ptr)
	{
		next = ptr;
	}
	prioritynode* getnext()
	{
		return next;
	}

	void setpriority(int p)
	{
		priority = -1*p; // modified now after discussion bet. MS and YA 
	}
	int getpriority()
	{
		return priority;
	}

};
