#pragma once
#include"QueueFCFS.h"
#include"process.h"
#include"Queue.h"
#include"InOut.h"
#include<iostream>
#include"Schedular.h"
#include"priorityQueue.h"

using namespace std;
class Schedular;
class InOut;

class  baseProcessor {

protected:
	Schedular* S_ptr; //a pointer to schedualr
	int PID;
	process* RUN;  //RUN state
	int num_processes; //existing in RDY list
	int finish_time; //the time required to finish all processes in the RDY state
	int total_busy_time;  //total time the processor is running
	int total_idle_time;   //total time the processor isn't running
	bool is_overheated;  //is the processor overheated
	static int overheatn; // total overheat Duration
	int overheatc; // elapsed overheat time
	float pload; //processor 1oad %
	float putil;// processor utility%
	static int num_processors;// just to help me make a unique ID for each processor


public:
	baseProcessor(Schedular* p);
	int get_PID();
	virtual void add2RDY(process*) = 0;
	virtual process* getfromRDY() = 0;
	virtual void RDY2RUN() = 0;
	virtual process* getfromRUN() = 0;
	void inc_finsihtime(int);
	int get_finishedTime();
	virtual void Schedular_Algo() = 0;
	void set_Run_pointer(process* p);
	virtual process* peek_RDY() = 0;
	process* get_RUN();
	virtual void add2_RDY_begining(process* ptr) = 0;
	virtual void print() = 0;
	static void set_overheatn(int);
	virtual void processor_overheat() = 0;
	bool Is_overheated();
	void deleteRUN();
	virtual float get_processor_load();
	virtual float get_processor_utiliz();

	friend ostream& operator<<(ostream& os, const baseProcessor* p)
	{
		os << p->PID;
		return os;
	}

};


class processorFCFS : public baseProcessor
{

	QueueFCFS RDY_FCFS; //RDY list for FCFS
	static Queue<int> SigKill;
	static int next_kill; //time step of next kill
	static int max_w;
public:

	processorFCFS(Schedular* p);
	virtual void add2RDY(process*);
	virtual  process* getfromRDY();
	void add2RUN(process*);
	process* getfromRUN();
	void RDY2RUN();
	static void set_static(Queue<int>&, int);
	virtual void Schedular_Algo();
	void KillSig();
	virtual process* peek_RDY();
	void processor_overheat();
	virtual void add2_RDY_begining(process* ptr);

	//void killprocess(int id);
	//void forkprocess()
	virtual void print();

	bool remove_child(int);

};

class processorRR :public baseProcessor
{
	int time_slice;
	int time_Running; // a time for each process running to compare with time_slice
	Queue<process*> RDY_RR;  //RDY list
	static int rtf;

public:

	processorRR(Schedular* p);
	void add2RDY(process*);
	process* getfromRDY();
	void RDY2RUN();
	process* getfromRUN();
	virtual void Schedular_Algo();
	void processor_overheat();

	// virtual void Schedular_Algo();
	static void set_static(int);
	virtual process* peek_RDY();
	virtual void add2_RDY_begining(process* ptr);
	virtual void print();


};

class processorSJF :public baseProcessor
{
	priorityQueue<process*> RDY_SJF;

public:
	processorSJF(Schedular* s);
	void add2RDY(process*);
	process* getfromRDY();
	void RDY2RUN();
	process* getfromRUN();
	virtual void Schedular_Algo();
	void processor_overheat();
	virtual process* peek_RDY();
	void add2_RDY_begining(process* ptr);
	virtual void print();


};
class processorEDF :public baseProcessor
{
	priorityQueue<process*> RDY_EDF;

public:
	processorEDF(Schedular* s);
	void add2RDY(process*);
	process* getfromRDY();
	void RDY2RUN();
	process* getfromRUN();
	virtual void Schedular_Algo();
	void processor_overheat();
	virtual process* peek_RDY();
	virtual void add2_RDY_begining(process* ptr);
	virtual void print();


};