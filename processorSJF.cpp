#include "processorSJF.h"
#include"baseProcessor.h"
#include"Schedular.h"

processorSJF::processorSJF(Schedular* s) : baseProcessor(s)
{
}

void processorSJF::NEW_to_RDY()
{
	process* ptr = get_from_new();
	RDY_SJF.enqueue(ptr, ptr->get_CT());
	set_no_processes(get_no_peocesses() + 1);
	//set_finishTime(get_finishedTime() + ptr->get_CT());
	//set_totalturnaroundtime(get_totalturnaroundtime() + ptr->get_TRT());
}

void processorSJF::RDY_to_RUN()
{

	process* ptr = RDY_SJF.dequeue();
	set_RUN(ptr);
	set_no_processes(get_no_peocesses() - 1);
	//set_finishTime(get_finishedTime() - ptr->get_CT());
	set_is_busy(true);
}

void processorSJF::RDY_to_TRM()
{
	process* ptr = RDY_SJF.dequeue();
	add2TRM(ptr);
	//set_no_processes(get_no_peocesses() - 1);
	//set_finishTime(get_finishedTime() - ptr->get_CT());
}

void processorSJF::RUN_to_BLK()
{
	if (!isbusy())
		return;

	add2BLK(RUN);
	RUN = nullptr;
}

void processorSJF::BLK_to_RDY()
{
	process* ptr = get_from_BLK();
	RDY_SJF.enqueue(ptr, ptr->get_CT());
	//set_no_processes(get_no_peocesses() + 1);
	//set_finishTime(get_finishedTime() + ptr->get_CT());
}

void processorSJF::RUN_to_RDY()
{
	if (!isbusy())
		return;

	process* ptr = RUN;
	RDY_SJF.enqueue(ptr, ptr->get_CT());
	RUN = nullptr;
	//set_no_processes(get_no_peocesses() + 1);
	//set_finishTime(get_finishedTime() + ptr->get_CT());
}

void processorSJF::monitor_RUN()
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

void processorSJF::monitor_BLK()
{
	double r = 1 + (rand() % 100);
	if (r < 10)
		BLK_to_RDY();
}

void processorSJF::print() {
	cout << RDY_SJF.getlength() << " RDY:" << " ";
	RDY_SJF.print();

}
