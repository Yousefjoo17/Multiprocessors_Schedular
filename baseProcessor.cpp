#include "Processors.h"
#include<iostream>
#include"Schedular.h"
using namespace std;

int baseProcessor::num_processors = 0;
int baseProcessor::overheatn = 0;
baseProcessor::baseProcessor(Schedular* ptr)
{
	//srand(p->get_time()); //not sure
	S_ptr = ptr;
	PID = ++num_processors;
	RUN = nullptr;
	num_processes = 0;
	overheatc = 0;
	finish_time = 0;
	total_idle_time = 0;
	total_busy_time = 0;
	is_overheated = false;
}
void baseProcessor::set_overheatn(int x) {
	overheatn = x;
}
bool baseProcessor::Is_overheated()
{
	return is_overheated;
}
void baseProcessor::deleteRUN()
{
	RUN == nullptr;
}
float baseProcessor::get_processor_load()
{
	pload = 100 * float(total_busy_time) / float(S_ptr->get_total_TRT());

	return pload;
}
float baseProcessor::get_processor_utiliz()
{
	putil = 100 * float(total_busy_time) / float(total_busy_time + total_idle_time);
	return putil;
}
void baseProcessor::set_Run_pointer(process* p) { RUN = p; }
process* baseProcessor::get_RUN()
{
	return RUN;
}


int baseProcessor::get_PID()
{
	return PID;
}

void baseProcessor::inc_finsihtime(int i)
{
	finish_time += i;
}

int baseProcessor::get_finishedTime()
{
	return finish_time;
}

