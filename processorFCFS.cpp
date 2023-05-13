#include "processorFCFS.h"
#include<iostream>
#include"baseProcessor.h"
using namespace std;
Queue<int> q;
Queue<int> processorFCFS::SigKill = q;
int processorFCFS::next_kill = 0;
int processorFCFS::max_w = 0;

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

void processorFCFS::set_static(Queue<int>& q,int w)
{
	SigKill = q;
	next_kill = SigKill.dequeue();
	max_w = w;

}

void processorFCFS::Schedular_Algo()
{
	if (!RUN && !RDY_FCFS.is_empty()) {
		RDY2RUN();
	}
	if (!RUN && RDY_FCFS.is_empty()) {
		total_idle_time++;
	}
	if (RUN) {
		total_busy_time++;
		while (!RUN->get_Is_Child() && RUN->get_curr_WT(S_ptr->get_timestep()) > max_w) {
			finish_time -= RUN->get_CT();
			S_ptr->migrate_FCFS2RR(RUN);
			RUN = nullptr;
			if (!RDY_FCFS.is_empty())
			{
				RDY2RUN();
			}
			else {
				break;
			}
		}
		if (RUN) {
			if (RUN->peek_IO_R() == RUN->get_CT_EX())
			{

				finish_time -= RUN->get_CT();
				S_ptr->add2BLK(RUN);
				RUN = nullptr;
				if (!RDY_FCFS.is_empty()) {
					RDY2RUN();
				}
			}
		}
		if (RUN) {
			if (RUN->get_CT_EX() == RUN->get_CT())
			{
				RUN->set_TT(S_ptr->get_timestep());
				total_turnaround_time += RUN->get_TRT();
				finish_time -= RUN->get_CT();
				S_ptr->add2TRM(RUN);
				RUN = nullptr;
				if (!RDY_FCFS.is_empty()) {
					RDY2RUN();
				}
			}
		}
		//forking
		if (RUN) {
			RUN->inc_CT_EX();
		}
	}
}


void processorFCFS::KillSig()
{
	if (!SigKill.is_empty()) {
		int curr = S_ptr->get_timestep();
		if (next_kill < curr && !SigKill.is_empty()) {
			next_kill = SigKill.dequeue();
			next_kill = SigKill.dequeue();

		}
		if (curr != next_kill)
			return;
		int id = SigKill.peek();
		if (RUN->get_PID() == id)
		{
			finish_time -= RUN->get_CT();
			RUN->set_TT(S_ptr->get_timestep());
			total_turnaround_time += RUN->get_TRT();
			S_ptr->add2TRM(RUN);
			id = SigKill.dequeue();
			if (!SigKill.is_empty())
				next_kill = SigKill.dequeue();
		}
		process* ptr = RDY_FCFS.remove_id(id);
		if (ptr)
		{
			finish_time -= ptr->get_CT();
			ptr->set_TT(S_ptr->get_timestep());
			total_turnaround_time += ptr->get_TRT();
			S_ptr->add2TRM(ptr);
			id = SigKill.dequeue();
			if (!SigKill.is_empty())
				next_kill = SigKill.dequeue();
		}
	}
}

process* processorFCFS::peek_RDY()
{
	return RDY_FCFS.peek();
}

void processorFCFS::print()
{
	RDY_FCFS.print();
}

