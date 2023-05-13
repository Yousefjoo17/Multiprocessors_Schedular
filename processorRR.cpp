#include "processorRR.h"
#include"baseProcessor.h"
#include"Schedular.h"

int processorRR::rtf = 0;

processorRR::processorRR(Schedular* s) : baseProcessor(s)
{
	time_slice = s->get_RR_slice();
	time_Running = 0;
}

void processorRR::add2RDY(process* p)
{
	RDY_RR.enqueue(p);
}

process* processorRR::getfromRDY()
{
	return RDY_RR.dequeue();
}

void processorRR::RDY2RUN()
{
	RUN = RDY_RR.dequeue();
	if (RUN->is_first_time()) {
		RUN->set_RT(S_ptr->get_timestep());
	}
}

process* processorRR::getfromRUN()
{
	return RUN;
}

void processorRR::Schedular_Algo()
{
	if (!RUN && !RDY_RR.is_empty()) {
		RDY2RUN();

	}
	if (!RUN && RDY_RR.is_empty()) {
		total_idle_time++;
	}
	if (RUN) {
		total_busy_time++;
		while (RUN->get_rem_CT() < rtf) {
			finish_time -= RUN->get_CT();
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
			if (RUN->peek_IO_R() == RUN->get_CT_EX())
			{
				finish_time -= RUN->get_CT();
				time_Running = 0;
				// go to BLK
				if (!RDY_RR.is_empty()) {
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
				time_Running = 0;
				S_ptr->add2TRM(RUN);
				RUN = nullptr;
				if (!RDY_RR.is_empty()) {
					RDY2RUN();
				}
			}
		}

		if (RUN)
		{
			if (time_Running == time_slice)
			{
				add2RDY(RUN);
				RUN = nullptr;
				if (!RDY_RR.is_empty())
				{
					RDY2RUN();
				}

			}
		}
		if (RUN) {
			if (time_Running < time_slice)
			{
				RUN->inc_CT_EX(); time_Running++;

			}
		}
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

			
		
	