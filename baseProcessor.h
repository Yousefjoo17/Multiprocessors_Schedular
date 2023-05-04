#pragma once
#include"QueueFCFS.h"
#include"process.h"
#include"Queue.h"
#include<iostream>
#include"Schedular.h"
#include"priorityQueue.h"

using namespace std;
class Schedular;

class  baseProcessor {

protected:
	Schedular* S_ptr; //a pointer to schedualr
	int PID;
	process* RUN;  //RUN state
	int num_processes; //existing in RDY list
	int finish_time; //the time required to finish all processes in the RDY state
	int total_busy_time;  //total time the processor is running
	int total_idle_time;   //total time the processor isn't running
	int total_turnaround_time; //
	/*total(summation) turn around time of all processes in the processor
	in ready,running,block*/
	bool is_busy;  //is the processor running a process ?
	int pload; //processor 1oad %
	int putil;// processor utility%
	static int num_processors;// just to help me make a unique ID for each processor


public:
	baseProcessor(Schedular*p);
	void set_busy_Idle();
	void set_pload();
	void set_putil();
	int get_PID();
	virtual void add2RDY(process*);
	virtual process* getfromRDY();
	virtual void RDY2RUN(process*);
	virtual process* getfromRUN();
    virtual void Schedular_Algo() = 0;
	friend ostream& operator<<(ostream& os, const baseProcessor*& p)
	{
		os << p->PID;
		return os;
	}

};


 class processorFCFS : public baseProcessor
 {

	 QueueFCFS RDY_FCFS; //RDY list for FCFS 
 public:

	 processorFCFS(Schedular*p);
	 void add2RDY(process*);
	 process* getfromRDY();
	 void add2RUN(process*);
	 process* getfromRUN();
	 virtual void Schedular_Algo();

	 //void killprocess(int id);
	 //void forkprocess()
 };

 class processorRR :public baseProcessor
 {
	 int time_slice;
	 int time_Running; // a time for each process running to compare with time_slice
	 Queue<process*> RDY_RR;  //RDY list

 public:

	 processorRR(Schedular* p);
	 void add2RDY(process*);
	 process* getfromRDY();
	 void RDY2RUN(process*);
	 process* getfromRUN();
	 virtual void Schedular_Algo();
	// virtual void Schedular_Algo();


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
 };


