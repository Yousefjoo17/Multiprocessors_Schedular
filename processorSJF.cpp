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

/*void processorSJF::add2RUN(process* p)
{
	RUN = p;
}*/

process* processorSJF::getfromRUN()
{
	return RUN;
}

void processorSJF::Schedular_Algo()
{
	if (!RUN&&!RDY_SJF.is_empty()){
		RUN = RDY_SJF.dequeue();
		RUN->set_RT(S_ptr->get_timestep());
	}
	if(!RUN&&RDY_SJF.is_empty()) {
		total_idle_time++;
	}
	if (RUN) {
		total_busy_time++;
		if (RUN->peek_IO_R()==RUN->get_CT_EX())
		{
			//go to BLK
			if (!RDY_SJF.is_empty()) {
				RUN = RDY_SJF.dequeue();
				RUN->set_RT(S_ptr->get_timestep());
			}
		}
		if (RUN->get_CT_EX() == RUN->get_CT())
		{	
			RUN->set_TT(S_ptr->get_timestep());
			total_turnaround_time += RUN->get_TRT();
			// go to TRM
			
			if(!RDY_SJF.is_empty()) {
				RUN = RDY_SJF.dequeue();
				RUN->set_RT(S_ptr->get_timestep());

			}
		}

		RUN->inc_CT_EX();
	
	}

}
