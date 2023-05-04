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
	}
	if (RUN) {
		if (RUN->peek_IO_R()==RUN->get_CT_EX())
		{
			//go to BLK

		}
		if (RUN->get_CT_EX() == RUN->get_CT())
		{
			// go to TRM
		}
		RUN->inc_CT_EX();
		
	}
}
