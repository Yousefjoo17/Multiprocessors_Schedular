#ifndef PROCESSORSJF_H
#define PROCESSORSJF_H
#pragma once
#include"priorityQueue.h"
#include"baseProcessor.h"
class baseProcessor;
class Schedular;



class processorSJF :public baseProcessor
{
	priorityQueue<process*> RDY_SJF;

public:
	processorSJF(Schedular* s);
	void add2RDY(process*);
	process* getfromRDY();
	void add2RUN(process*);
	process* getfromRUN();
	virtual void Schedular_Algo();
};
#endif