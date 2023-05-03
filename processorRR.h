#ifndef PROCESSORRR_H
#define PROCESSORRR_H
#pragma once
#include"Queue.h"
#include"baseProcessor.h"
class baseProcessor;
class Schedular;

class processorRR:public baseProcessor
{
	int time_slice; 
	int time_Running; // a time for each process running to compare woth time_slice
	Queue<process*> RDY_RR;  //RDY list
    
public:

	processorRR(Schedular* p);
	void add2RDY(process*);
	process* getfromRDY();
	void add2RUN(process*);
	process* getfromRUN();
	virtual void Schedular_Algo();
		

};
#endif