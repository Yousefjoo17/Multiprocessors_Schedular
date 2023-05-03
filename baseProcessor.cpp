#include "baseProcessor.h"
#include<iostream>
#include"Schedular.h"
using namespace std;

int baseProcessor::num_processors = 0;

baseProcessor::baseProcessor(Schedular*ptr)
{
	//srand(p->get_time()); //not sure
	S_ptr = ptr;
	PID = ++num_processors;
	RUN = nullptr;
	num_processes = 0;
	finish_time = 0;
	total_busy_time = 0;
	total_busy_time = 0;
	total_turnaround_time = 0;
	is_busy = false;
	set_pload();
	set_putil();
}


void baseProcessor::set_busy_Idle()
{
	if (num_processes == 0 && !RUN)
		is_busy = false;
	else
		is_busy = true;
}
void baseProcessor::set_pload()
{
	if (total_turnaround_time)
		pload = total_busy_time / total_turnaround_time;
	else
		pload = 0;
}
void baseProcessor::set_putil()
{
	if (total_busy_time + total_idle_time)
		putil = total_busy_time / (total_busy_time + total_idle_time);
	else
		putil = 0;
}



