#pragma once
using namespace std;
template<typename T>
class ListADT {

public:
	virtual bool is_empty() = 0;
	virtual void insert(T newentry) = 0;
	virtual T remove() = 0;
	virtual T remove_id(int) = 0;
	virtual T peek() = 0;
	virtual ~ListADT() {};
};
