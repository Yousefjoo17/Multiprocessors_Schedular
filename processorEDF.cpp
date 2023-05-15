#include"baseProcessor.h"
#include"Schedular.h"

processorEDF::processorEDF(Schedular* s) : baseProcessor(s)
{
}

void processorEDF::add2RDY(process* p)
{
	finish_time += p->get_CT();
	if (RUN) {
		if (p->get_deadline() < RUN->get_deadline()) {
			RDY_EDF.enqueue(RUN, RUN->get_deadline());
			RUN = p;
			if (RUN->is_first_time()) {
				RUN->set_RT(S_ptr->get_timestep());
				RUN->set_first_time(false);
			}
		}
		else{
			RDY_EDF.enqueue(p, p->get_deadline());
		}
	}
	else {
		RDY_EDF.enqueue(p, p->get_deadline());
	}

}

process* processorEDF::getfromRDY()
{
	process* ptr = RDY_EDF.dequeue();
	finish_time -= ptr->get_CT();
	return ptr;
}

void processorEDF::RDY2RUN()
{
	RUN = RDY_EDF.dequeue();
	S_ptr->inc_RUN_count(1);
	if (RUN->is_first_time()) {
		RUN->set_RT(S_ptr->get_timestep());
		RUN->set_first_time(false);
	}
}

process* processorEDF::getfromRUN()
{
	return RUN;
}

void processorEDF::Schedular_Algo()
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
			if (!RUN && !RDY_EDF.is_empty()) {
				RDY2RUN();
			}
			if (!RUN && RDY_EDF.is_empty()) {
				total_idle_time++;
			}
			if (RUN) {
				total_busy_time++;
				if (RUN->peek_IO_R() == RUN->get_CT_EX())
				{
					finish_time  -= RUN->get_CT();
					S_ptr->inc_RUN_count(-1);
					S_ptr->add2BLK(RUN);
					RUN = nullptr;
					if (!RDY_EDF.is_empty()) {
						RDY2RUN();
					}
				}
				if (RUN)
				{
					if (RUN->get_CT_EX() == RUN->get_CT())
					{
						RUN->set_TT(S_ptr->get_timestep());
						total_turnaround_time += RUN->get_TRT();
						finish_time -= RUN->get_CT();
						S_ptr->inc_RUN_count(-1);
						S_ptr->add2TRM(RUN);

						if (!RDY_EDF.is_empty()) {
							RDY2RUN();
						}
					}
				}
				if (RUN) {
					RUN->inc_CT_EX();
				}
			}
		}
	}
}

void processorEDF::processor_overheat()
{
	overheatc++;
	is_overheated = true;
	finish_time = 0;
	if (RUN) {
		S_ptr->add2RDY(RUN);
		S_ptr->inc_RUN_count(-1);
		RUN = nullptr;
	}
	while (!RDY_EDF.is_empty()) {
		S_ptr->add2RDY(RDY_EDF.dequeue());
	}
}

process* processorEDF::peek_RDY()
{
	return RDY_EDF.peek();
}

void processorEDF::add2_RDY_begining(process* ptr)
{
}

void processorEDF::print()
{
	RDY_EDF.print();
}
