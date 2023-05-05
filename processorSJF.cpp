#include "processorSJF.h"
#include"baseProcessor.h"
#include"Schedular.h"

processorSJF::processorSJF(Schedular* s) : baseProcessor(s)
{
}

void processorSJF::add2RDY(process* p)
{
	RDY_SJF.enqueue(p,p->get_CT());
	finish_time += p->get_CT();
}

process* processorSJF::getfromRDY()
{
	return RDY_SJF.dequeue();
}

void processorSJF::RDY2RUN()
{
	RUN = RDY_SJF.dequeue();
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
	if (!RUN&&!RDY_SJF.is_empty()){
		RDY2RUN();
	}
	if(!RUN&&RDY_SJF.is_empty()) {
		total_idle_time++;
	}
	if (RUN) {
		total_busy_time++;
		if (RUN->peek_IO_R()==RUN->get_CT_EX())
		{

			finish_time -= RUN->get_CT();
			//go to BLK
			if (!RDY_SJF.is_empty()) {
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
				S_ptr->add2TRM(RUN);

				if (!RDY_SJF.is_empty()) {
					RDY2RUN();
				}
			}
		}
		if (RUN) {
			RUN->inc_CT_EX();
		}
	}

}
