#pragma once
#pragma once
template<typename T>

class priorityQueueADT
{
public:

	virtual bool is_empty() = 0;
	virtual void enqueue(T i,int k) = 0;
	virtual T dequeue() = 0;
	virtual T peek() = 0;
	virtual void print() = 0;
	virtual ~priorityQueueADT() {};
};
