#pragma once
#include "Queue.h"
#include<iostream>
using namespace std;
class process
{
private:
	int PID; //ID of process
	int AT; //Arrival time
	int RT; //Response time :-----
	int CT; //CPU time
	int CT_EX; //Executed CPU time
	int TT; //Termination time
	int TRT; //Turnaround duration :from arrival to tremination 
	int WT; //Waiting time
	Queue<int> IO; //Queue of IO_R (request time) then IO_D (duration)
	int IO_total; //total nember if IO
	process* Child;
	process* left_child;
	process* right_child;
	bool Is_Child;
	bool Is_First_Time;
	int total_IO_D;//tototal time steps spent in IO
	int IO_D_EX;
	int deadline;
	bool is_TRM;
public:
	process(int, int, int, int, int, Queue<int>&);
	process(bool, process*&, int, int);
	//friend ostream& operator<<(ostream& os, const process*& p);
	int get_PID();
	int get_AT();
	int get_RT();
	int get_CT();
	int get_CT_EX();
	int get_TT();
	int get_TRT();
	int get_WT();
	int peek_IO_R();
	int peek_IO_D();
	int get_IO_R();
	int get_IO_D();
	int get_IO_D_EX();
	void inc_IO_D_EX();
	int get_n_total();
	int get_rem_CT();
	int get_curr_WT(int);
	int get_toatal_IO_D();
	int get_deadline();
	bool is_first_time();
	process* get_Child();
	process* get_rightChild();
	process* get_leftChild();

	bool get_Is_Child();
	void inc_CT_EX();
	void set_first_time(bool);
	void set_RT(int);
	void set_CT_EX(int);
	void set_TT(int);
	void set_n_current(int);
	void set_Child(process*);
	void set_rightchild(process*);
	void set_leftchild(process*);
	void set_Is_TRM(bool);
	bool Is_TRM();

	void set_Is_Child(bool);
	friend ostream& operator<<(ostream& os, const process* p)
	{
		os << p->PID;
		return os;
	}

	~process();


};


