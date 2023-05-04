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

void processorFCFS::KillSig()
{
	int curr = S_ptr->get_timestep();
	if (curr != next_kill)
		return;
	int id = SigKill.peek();
	if (RUN->get_PID() == id) {


	}





}

