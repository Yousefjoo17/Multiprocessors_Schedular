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

	void NEW_to_RDY();

	void RDY_to_RUN();

	void RDY_to_TRM();
	void RUN_to_BLK();
	void BLK_to_RDY();

	void RUN_to_RDY();
	void monitor_RUN();

	void monitor_BLK();

	/*processorAlgo()
	{
		update_processor_time();
		monitor_RUN();
		monitor_BLK();
		if (isbusy())
			return;
		else
		{
			NEW_to_RDY();
		}
	}*/

	void print();
};
#endif