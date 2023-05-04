#include "processorRR.h"
#include"baseProcessor.h"
#include"Schedular.h"

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

//void processorRR::add2RUN(process* p)
//{
	//RUN = p;
//}

process* processorRR::getfromRUN()
{
	return RUN;
}

/*void processorFCFS::Schedular_Algo()
{

}*/

