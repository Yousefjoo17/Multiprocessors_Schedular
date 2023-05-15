#pragma once
#include"Queue.h"
#include"processorFCFS.h"
#include"process.h"
#include"InOut.h"
#include"baseProcessor.h"
#include <string>

class baseProcessor;
class InOut;

class Schedular {

public:
	baseProcessor** Processors; // array of pointers to arrays (0,NF-1) -> FCFS | (NF,NF+NS-1) -> SJF | (NF+NS,NF+NS+NR-1) -> RR | (NF+NS+NR,NF+NS+NR+NE-1) -> EDF
	Queue<process*> NEW; //queue of NEW stage
	Queue<process*> BLK; // queue of Block stage
	Queue<process*> TRM;  //Queue of TRM stage
	int processors_counter;
	int RR_slice; //RR time slice
	int NF; // number of FCFS processors
	int NS; // number of SJF processors 
	int NR; // number of RR processors
	int NE; // number of EDF processors
	int total_processes; // total number of processes 
	int RTF;
	int MaxW;
	int STL;
	int FP; // the fork probability
	int Overheatn; //number of overheat time steps
	int total_WT; // total waiting time
	int total_RT; // total response time 
	int total_TRT;// total Turnaround time 
	Queue<int> SigKill;// queue of signal kill
	int BLK_count;
	int TRM_count;
	int RUN_count;
	int time_step;
	int Running_time;
	int RTF_Processes;
	int MaxW_Processes;
	int BeforeDeadline;



public:
	Schedular(string);
	void add2NEW(process*);
	process* getfromNEW();
	void add2BLK(process*);
	process* getfromBLK();
	bool BLK2RUN(process*);
	void add2RDY(process* p);
	void add2TRM(process*);
	void simulate();
	void migrate_RR2SJF(process*);
	void migrate_FCFS2RR(process*);
	void work_stealing();
	void forking_tree_algo(process* );








	/********************************************************/
	// setters 
	void set_processors_counter();
	void set_RR_slice(int r);
	void set_NF(int n);
	void set_NS(int s);
	void set_NR(int nr);
	void set_total_processes(int tp);
	void set_RTF(int rtf);
	void set_MaxW(int mw);
	void set_STL(int stl);
	void set_total_WT(int twt);
	void set_total_RT(int trtt);
	void set_total_TRT(int trttt);
	void set_BLK_count(int blkc);
	void set_RUN_count(int runc);

	// getters
	int get_processors_counter();
	int get_RR_slice();
	int get_NF();
	int get_NS();
	int get_NR();
	int get_NE();
	int get_total_processes();
	int get_RTF();
	int get_MaxW();
	int get_STL();
	int get_total_WT();
	int get_total_RT();
	int get_total_TRT();
	int get_BLK_count();
	int get_RUN_count();
	int get_timestep();

	/*********************************/
	void NEW_RDY();
	void P_Completion(process*);
	int ShortestQueue();
	int ShortestQueue(int,int);

};
