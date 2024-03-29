#include"Processors.h"
#include"Schedular.h"

processorSJF::processorSJF(Schedular* s) : baseProcessor(s)
{
}

void processorSJF::add2RDY(process* p)
{
	RDY_SJF.enqueue(p, p->get_CT());
	finish_time += p->get_CT() - p->get_CT_EX();
}

process* processorSJF::getfromRDY()
{
	process* ptr = RDY_SJF.dequeue();
	finish_time -= ptr->get_CT() - ptr->get_CT_EX();
	return ptr;
}

void processorSJF::RDY2RUN()
{
	RUN = RDY_SJF.dequeue();
	S_ptr->inc_RUN_count(1);
	if (RUN->is_first_time()) {
		RUN->set_RT(S_ptr->get_timestep());
		RUN->set_first_time(false);
	}
}

process* processorSJF::getfromRUN()
{
	return RUN;
}

void processorSJF::Schedular_Algo()
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
			if (!RUN && !RDY_SJF.is_empty()) {
				RDY2RUN();
			}
			if (!RUN && RDY_SJF.is_empty()) {
				total_idle_time++;
			}
			if (RUN) {
				total_busy_time++;
				while (RUN->peek_IO_R() == RUN->get_CT_EX())
				{

					finish_time -= RUN->get_CT() - RUN->get_CT_EX();
					S_ptr->inc_RUN_count(-1);
					S_ptr->add2BLK(RUN);
					RUN = nullptr;
					if (!RDY_SJF.is_empty()) {
						RDY2RUN();
					}
					else {
						break;
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
						if (!RDY_SJF.is_empty()) {
							RDY2RUN();
						}
						else {
							break;
						}
					}
				}
				if (RUN) {
					RUN->inc_CT_EX();
					finish_time--;
				}
			}
		}
	}
}

void processorSJF::processor_overheat()
{
	overheatc++;
	is_overheated = true;
	finish_time = 0;
	if (RUN) {
		S_ptr->inc_RUN_count(-1);
		S_ptr->add2RDY(RUN);
		RUN = nullptr;
	}
	while (!RDY_SJF.is_empty()) {
		S_ptr->add2RDY(RDY_SJF.dequeue());
	}
}

process* processorSJF::peek_RDY()
{
	return RDY_SJF.peek();
}

void processorSJF::add2_RDY_begining(process* ptr)
{
}

void processorSJF::print()
{
	RDY_SJF.print();
}
