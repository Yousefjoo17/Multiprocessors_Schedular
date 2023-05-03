#include "processorRR.h"
#include"baseProcessor.h"
#include"Schedular.h"

processorRR::processorRR(Schedular* s) : baseProcessor(s)
{
	time_slice = s->get_RR_slice();
	time_Running = 0;
}

void processorRR::NEW_to_RDY()
{

	process* ptr = get_from_new();
	RDY_RR.enqueue(ptr);
	set_no_processes(get_no_peocesses() + 1);
	//set_finishTime(get_finishedTime() + ptr->get_CT());
	//set_totalturnaroundtime(get_totalturnaroundtime() + ptr->get_TRT());

}

void processorRR::RDY_to_RUN()
{

	process* ptr = RDY_RR.dequeue();
	set_RUN(ptr);
	set_no_processes(get_no_peocesses() - 1);
	//set_finishTime(get_finishedTime() - ptr->get_CT());
	//set_totalturnaroundtime(get_totalturnaroundtime() + ptr->get_TRT());
	set_is_busy(true);
	
}
void processorRR::RDY_to_TRM()
{
	process* ptr = RDY_RR.dequeue();
	add2TRM(ptr);
	set_no_processes(get_no_peocesses() - 1);
	//set_finishTime(get_finishedTime() - ptr->get_CT());
	//set_totalturnaroundtime(get_totalturnaroundtime() + ptr->get_TRT());
}

void processorRR::RUN_to_BLK()
{
	if (!isbusy())
		return;
	if (time_Running >= time_slice)

		add2BLK(RUN);
	RUN = nullptr;
}

void processorRR::BLK_to_RDY()
{
	process* ptr = get_from_BLK();
	RDY_RR.enqueue(ptr);
	set_no_processes(get_no_peocesses() + 1);
	//set_finishTime(get_finishedTime() + ptr->get_CT());
	//set_totalturnaroundtime(get_totalturnaroundtime() + ptr->get_TRT());

}

void processorRR::RUN_to_RDY()
{
	if (!isbusy())
		return;

	process* ptr = RUN;
	RDY_RR.enqueue(ptr);
	RUN = nullptr;
	set_no_processes(get_no_peocesses() + 1);
	set_finishTime(get_finishedTime() + ptr->get_CT());
}

void processorRR::monitor_RUN()
{
	if (!isbusy())
		return;

	double r = 1 + (rand() % 100);
	if (r <= 15 && r <= 1)
		RUN_to_BLK();

	else if (r >= 20 && r <= 30)
		RUN_to_RDY();

	else if (r >= 50 && r <= 60)
		RUN_to_TRM();
}

void processorRR::monitor_BLK()
{
	double r = 1 + (rand() % 100);
	if (r < 10)
		BLK_to_RDY();
}

void processorRR::print() {

	RDY_RR.print();
}

