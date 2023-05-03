#include "processorFCFS.h"
#include<iostream>
#include"baseProcessor.h"
using namespace std;

processorFCFS::processorFCFS(Schedular*ptr):baseProcessor(ptr)
{

}

void processorFCFS::add2RDY(process* p)
{
	RDY_FCFS.enqueue(p);
}

process* processorFCFS::getfromRDY()
{
	return RDY_FCFS.dequeue();
}

void processorFCFS::add2RUN(process* p)
{
	RUN = p;
}

process* processorFCFS::getfromRUN()
{
	return RUN;
}

void processorFCFS::Schedular_Algo()
{

}

