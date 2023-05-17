#include"Processors.h"
#include"Schedular.h"

int processorRR::rtf = 0;

processorRR::processorRR(Schedular* s) : baseProcessor(s)
{
	time_slice = s->get_RR_slice();
	time_Running = 0;
}

void processorRR::add2RDY(process* p)
{
	finish_time += p->get_CT() - p->get_CT_EX();
	RDY_RR.enqueue(p);
}

process* processorRR::getfromRDY()
{
	process* ptr = RDY_RR.dequeue();
	finish_time -= ptr->get_CT() - ptr->get_CT_EX();
	return ptr;
}

void processorRR::RDY2RUN()
{
	RUN = RDY_RR.dequeue();
	S_ptr->inc_RUN_count(1);
	if (RUN->is_first_time()) {
		RUN->set_RT(S_ptr->get_timestep());
		RUN->set_first_time(false);
	}
}

process* processorRR::getfromRUN()
{
	return RUN;
}

void processorRR::Schedular_Algo()
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
			if (!RUN && !RDY_RR.is_empty()) {
				RDY2RUN();
			}
			if (!RUN && RDY_RR.is_empty()) {
				total_idle_time++;
			}
			if (RUN) {
				total_busy_time++;
				if (RUN)
				{
					if (time_Running == time_slice)
					{
						finish_time -= RUN->get_CT() - RUN->get_CT_EX();
						add2RDY(RUN);
						RUN = nullptr;
						S_ptr->inc_RUN_count(-1);
						time_Running = 0;
						if (!RDY_RR.is_empty())
						{
							RDY2RUN();
						}

					}
				}
				while (rtf != -1 && RUN->get_rem_CT() < rtf) {
					finish_time -= RUN->get_CT() - RUN->get_CT_EX();
					S_ptr->inc_RUN_count(-1);
					time_Running = 0;
					S_ptr->migrate_RR2SJF(RUN);
					RUN = nullptr;
					if (!RDY_RR.is_empty())
					{
						RDY2RUN();
					}
					else {
						break;
					}
				}
				if (RUN)
				{
					while (RUN->peek_IO_R() == RUN->get_CT_EX())
					{
						finish_time -= RUN->get_CT() - RUN->get_CT_EX();
						S_ptr->inc_RUN_count(-1);
						time_Running = 0;
						S_ptr->add2BLK(RUN);
						RUN = nullptr;
						if (!RDY_RR.is_empty()) {
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
						time_Running = 0;
						S_ptr->add2TRM(RUN);
						RUN = nullptr;
						if (!RDY_RR.is_empty()) {
							RDY2RUN();
						}
						else {
							break;
						}
					}
				}

				if (RUN) {
					if (time_Running < time_slice)
					{
						RUN->inc_CT_EX(); time_Running++;
						finish_time--;
					}
				}
			}
		}
	}
}

void processorRR::processor_overheat()
{
	overheatc++;
	is_overheated = true;
	finish_time = 0;
	time_Running = 0;
	if (RUN) {
		S_ptr->add2RDY(RUN);
		S_ptr->inc_RUN_count(-1);
		RUN = nullptr;
	}
	while (!RDY_RR.is_empty()) {
		S_ptr->add2RDY(RDY_RR.dequeue());
	}
}


void processorRR::set_static(int x)
{
	rtf = x;
}

process* processorRR::peek_RDY()
{
	return RDY_RR.peek();
}

void processorRR::add2_RDY_begining(process* ptr)
{
}

void processorRR::print()
{
	RDY_RR.print();
}



