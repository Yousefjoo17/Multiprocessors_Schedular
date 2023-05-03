#pragma once
#include"QueueFCFS.h"
#include"process.h"
#include<iostream>
#include"Schedular.h"
 class  baseProcessor {

protected:
	Schedular *S_ptr; //a pointer to schedualr
	int PID;
	process* RUN;  //RUN state
	int num_processes; //existing in RDY list
	int finish_time; //the time required to finish all processes in the RDY state
	int total_busy_time;  //total time the processor is running
	int total_idle_time;   //total time the processor isn't running
	int total_turnaround_time;
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
   // virtual void Schedular_Algo() = 0;

};


 class processorFCFS : public baseProcessor
 {

	 QueueFCFS RDY_FCFS; //RDY list for FCFS processor
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
