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

	processorRR(Schedular* s);
	void NEW_to_RDY();
	
	void RDY_to_RUN();

	void RDY_to_TRM();
	void RUN_to_BLK();
	void BLK_to_RDY();
	void RUN_to_RDY();

	void monitor_RUN();

	void monitor_BLK();


	void print();
		

};
#endif