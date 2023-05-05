#include "processorFCFS.h"
#include<iostream>
#include"baseProcessor.h"
using namespace std;
Queue<int> q;
Queue<int> processorFCFS::SigKill = q;
int processorFCFS::next_kill = 0;
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

void processorFCFS::RDY2RUN()
{
	RUN = RDY_FCFS.dequeue();
	if (RUN->is_first_time()) {
		RUN->set_RT(S_ptr->get_timestep());
		RUN->set_first_time(false);
	}
}

void processorFCFS::set_sig(Queue<int>& q)
{
	SigKill = q;
	next_kill = SigKill.dequeue();
}

void processorFCFS::Schedular_Algo()
{
	if (!RUN &&!RDY_FCFS.is_empty()){
		RDY2RUN();
	}
	if(!RUN && RDY_FCFS.is_empty()) {
		total_idle_time++;
	}
	if (RUN) {
		total_busy_time++;
		if (RUN->peek_IO_R()==RUN->get_CT_EX())
		{

			finish_time -= RUN->get_CT();
			//go to BLK
			if (!RDY_FCFS.is_empty()) {
				RDY2RUN();
			}
		}
		if (RUN->get_CT_EX() == RUN->get_CT())
		{	
			RUN->set_TT(S_ptr->get_timestep());
			total_turnaround_time += RUN->get_TRT();
			finish_time -= RUN->get_CT();
			S_ptr->add2TRM(RUN);
			if(!RDY_FCFS.is_empty()) {
				RDY2RUN();
			}
		}
		if (RUN) {
			RUN->inc_CT_EX();
		}
	}
}

void processorFCFS::KillSig()
{
	int curr = S_ptr->get_timestep();
	if (curr != next_kill)
		return;
	int id = SigKill.peek();
	if (RUN->get_PID() == id) 
	{
		// calll move to TRM;
		id = SigKill.dequeue();
		next_kill = SigKill.dequeue();
	}
	process* ptr= RDY_FCFS.remove_id(id);
	if(ptr)
	{	
		//call move to TRM;
		id = SigKill.dequeue();
		next_kill = SigKill.dequeue();
	}
}

