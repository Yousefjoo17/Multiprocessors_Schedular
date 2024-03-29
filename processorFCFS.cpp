#include<iostream>
#include"Processors.h"
using namespace std;
Queue<int> q;
Queue<int> processorFCFS::SigKill = q;
int processorFCFS::next_kill = 0;
int processorFCFS::max_w = 0;

processorFCFS::processorFCFS(Schedular* ptr) :baseProcessor(ptr)
{
}

void processorFCFS::add2RDY(process* p)
{
	finish_time += p->get_CT() - p->get_CT_EX();
	RDY_FCFS.enqueue(p);
}

process* processorFCFS::getfromRDY()
{
	process* ptr = RDY_FCFS.dequeue();
	finish_time -= ptr->get_CT() - ptr->get_CT_EX();
	return ptr;
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
	S_ptr->inc_RUN_count(1);
	if (RUN->is_first_time()) {
		RUN->set_RT(S_ptr->get_timestep());
		RUN->set_first_time(false);
	}
}

void processorFCFS::set_static(Queue<int>& q, int w)
{
	SigKill = q;
	next_kill = SigKill.dequeue();
	max_w = w;

}

void processorFCFS::Schedular_Algo()
{
	if (is_overheated) {
		if (overheatc < overheatn) {
			overheatc++;
			return;
		}
		overheatc = 0;
		is_overheated = false;
		return;
	}
	if (!is_overheated) {
		srand(time(NULL));
		int r = 1 + (rand() % 100);
		if (r < 2) {
			processor_overheat();
		}
		else {
			if (!RUN && !RDY_FCFS.is_empty()) {
				RDY2RUN();
			}
			if (!RUN && RDY_FCFS.is_empty()) {
				total_idle_time++;
			}
			if (RUN) {
				total_busy_time++;
				while (max_w != -1 && !RUN->get_Is_Child() && RUN->get_curr_WT(S_ptr->get_timestep()) > max_w) {
					finish_time -= RUN->get_CT() - RUN->get_CT_EX();
					S_ptr->inc_RUN_count(-1);
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

					while (RUN->peek_IO_R() == RUN->get_CT_EX())
					{

						finish_time -= RUN->get_CT() - RUN->get_CT_EX();
						S_ptr->inc_RUN_count(-1);
						S_ptr->add2BLK(RUN);
						RUN = nullptr;
						if (!RDY_FCFS.is_empty()) {
							RDY2RUN();
						}
						else {
							break;
						}
					}
				}
				if (RUN) {
					while (RUN->get_CT_EX() == RUN->get_CT())
					{
						RUN->set_TT(S_ptr->get_timestep());
						finish_time -= RUN->get_CT() - RUN->get_CT_EX();
						S_ptr->inc_RUN_count(-1);
						S_ptr->add2TRM(RUN);
						RUN = nullptr;
						if (!RDY_FCFS.is_empty()) {
							RDY2RUN();
						}
						else {
							break;
						}
					}
				}
				//forking
				if (RUN) {
					S_ptr->forking_tree_algo(RUN);
				}
				if (RUN) {
					RUN->inc_CT_EX();
					finish_time--;
				}


			}
		}
	}
}

void processorFCFS::KillSig()
{
	if (!SigKill.is_empty()) {
		int curr = S_ptr->get_timestep();
		if (next_kill < curr) {
			next_kill = SigKill.dequeue();
			next_kill = SigKill.dequeue();

		}
		if (curr != next_kill)
			return;
		int id = SigKill.peek();
		if (RUN && RUN->get_PID() == id)
		{
			finish_time -= RUN->get_CT() - RUN->get_CT_EX();
			S_ptr->inc_RUN_count(-1);
			RUN->set_TT(S_ptr->get_timestep());
			S_ptr->add2TRM(RUN);
			RUN = nullptr;
			S_ptr->inc_kill_count();
			id = SigKill.dequeue();
			if (!SigKill.is_empty())
				next_kill = SigKill.dequeue();
		}
		process* ptr = RDY_FCFS.remove_id(id);
		if (ptr)
		{
			finish_time -= ptr->get_CT() - ptr->get_CT_EX();
			ptr->set_TT(S_ptr->get_timestep());
			S_ptr->add2TRM(ptr);
			S_ptr->inc_kill_count();
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

void processorFCFS::add2_RDY_begining(process* ptr)
{
	RDY_FCFS.add2thebegining(ptr);
}

void processorFCFS::processor_overheat()
{
	overheatc++;
	is_overheated = true;
	finish_time = 0;
	if (RUN) {
		S_ptr->add2RDY(RUN);
		S_ptr->inc_RUN_count(-1);
		RUN = nullptr;
	}
	while (!RDY_FCFS.is_empty()) {
		S_ptr->add2RDY(RDY_FCFS.dequeue());
	}
}
void processorFCFS::print()
{
	RDY_FCFS.print();
}
bool processorFCFS::remove_child(int id) {
	if (!RUN) {
		return false;

	}
	if (RUN->get_PID() == id) {
		finish_time -= RUN->get_CT() - RUN->get_CT_EX();
		S_ptr->inc_RUN_count(-1);
		RUN->set_TT(S_ptr->get_timestep());
		RUN = nullptr;
		return true;
	}
	process* ptr = RDY_FCFS.remove_id(id);
	if (!ptr) {
		return false;
	}
	else {
		finish_time -= ptr->get_CT() - ptr->get_CT_EX();
		ptr->set_TT(S_ptr->get_timestep());
		return true;
	}
}

