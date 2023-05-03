#include "processorSJF.h"
#include"baseProcessor.h"
#include"Schedular.h"

processorSJF::processorSJF(Schedular* s) : baseProcessor(s)
{
}

void processorSJF::add2RDY(process* p)
{
	RDY_SJF.enqueue(p,p->get_CT());
}

process* processorSJF::getfromRDY()
{
	return RDY_SJF.dequeue();
}

void processorSJF::add2RUN(process* p)
{
	RUN = p;
}

process* processorSJF::getfromRUN()
{
	return RUN;
}

void processorSJF::Schedular_Algo()
{

}
