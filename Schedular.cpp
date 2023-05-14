#include "Schedular.h"

Schedular::Schedular(string file) {
	time_step = 0;
	BLK_count = 0;
	TRM_count = 0;
	RUN_count = 0;
	processors_counter = 0;
	Running_time = 0;
	total_RT = 0;
	total_TRT = 0;
	total_WT = 0;
	RTF_Processes=0;
	MaxW_Processes=0;
	BeforeDeadline = 0;
	string filename = file;
	InOut io(this);
	io.readfile(filename, NEW, SigKill, NF, NS, NR, NE, RR_slice, RTF, MaxW, STL, FP, Overheatn, total_processes);
	Processors = new baseProcessor* [NF+NS+NR+NE];

}

void Schedular::add2NEW(process* p)
{
	NEW.enqueue(p);
}

process* Schedular::getfromNEW()
{
	return NEW.dequeue();
}

void Schedular::add2BLK(process* p)
{
	BLK.enqueue(p);
}

process* Schedular::getfromBLK()
{
	return BLK.dequeue();
}

void Schedular::add2TRM(process* p)
{
	if (p->get_deadline() <= time_step)
		BeforeDeadline++;
	TRM_count++;
	total_RT += p->get_RT();
	total_TRT += p->get_TRT();
	total_WT += p->get_WT();
	TRM.enqueue(p);
}

void Schedular::simulate()
{
		string filename = "input_file";
		InOut io(this);
		UI user_interface(this);
		baseProcessor::set_overheatn(Overheatn);
		processorFCFS::set_static(SigKill,MaxW);
		processorRR::set_static(RTF);
		for (int i = 0; i < NF; i++) {
			Processors[i] = new processorFCFS(this);
		}
		for (int i = NF; i < NS + NF; i++) {
			Processors[i] = new processorSJF(this);
		}
		for (int i = NF + NS; i < NR + NS + NF; i++) {
			Processors[i] = new processorRR(this);
		}
		for (int i = NF + NS + NR; i < NR + NF + NS + NE; i++) {
			Processors[i] = new processorEDF(this);
		}
	
		while (time_step<18) {
			time_step++;
			NEW_RDY();
			/*for (int i = 0; i < NR + NF + NS + NE; i++) {
				Processors[i]->Schedular_Algo();
			}*/
			loop_p();
			user_interface.display(Processors, BLK, TRM);
			
		}
		while (time_step < 45) {
			time_step++;
			NEW_RDY();
			/*for (int i = 0; i < NR + NF + NS + NE; i++) {
				Processors[i]->Schedular_Algo();
			}*/
			loop_p();
			user_interface.display(Processors, BLK, TRM);

		}
}
void Schedular::loop_p() {
	for (int i = 0; i < NR + NF + NS + NE; i++) {
		Processors[i]->Schedular_Algo();
	}
}
void Schedular::migrate_RR2SJF(process* mig_p)
{
	RTF_Processes++; //inc migration counter
	int pro = ShortestQueue(NF,NF+NS); //get the shortest rdy queue of SJF processors
	Processors[pro]->add2RDY(mig_p);  // moves the process to the RDY queue of a SJF processor

}

void Schedular::migrate_FCFS2RR(process* mig_p)
{
	MaxW_Processes++;  //inc migration counter
	int pro = ShortestQueue(NF+NS, NF+NS+NR);//get the shortest rdy queue of RR processors
	Processors[pro]->add2RDY(mig_p); // moves the process to the RDY queue of a RR processor

}

void Schedular::work_stealing()
{
	int LQF, SQF;
	int LQF_ind, SQF_ind;
	LQF_ind = 0;
	SQF_ind = 0;
	LQF = Processors[0]->get_finishedTime();
	SQF = Processors[0]->get_finishedTime();

	for (int i = 1; i < NF + NS + NR + NE; i++)
	{
		if (Processors[i]->get_finishedTime() > LQF)
		{
			LQF = Processors[i]->get_finishedTime();
			LQF_ind = i;
		}
		if (Processors[i]->get_finishedTime() < SQF)
		{
			SQF = Processors[i]->get_finishedTime();
			SQF_ind = i;
		}
		baseProcessor* ptr_LQF = Processors[LQF_ind];
		baseProcessor* ptr_SQF = Processors[SQF_ind];
		
		
		Stack<process*>s(50);
		process*ptr;
		while ((LQF - SQF) / LQF > 0.40)
		{
			while (ptr_LQF->peek_RDY()->get_Is_Child())   // FCFS Processors only
			{
				s.push(ptr_LQF->getfromRDY());
			}
			ptr_SQF->add2RDY(ptr_LQF->getfromRDY());
		}
		while (s.pop(ptr))
		{

			baseProcessor* pfcfs = Processors[LQF_ind];
			pfcfs = dynamic_cast<processorFCFS*>(Processors[LQF_ind]);
			pfcfs->add2_RDY_begining(ptr);  // FCFS Processors only 
		}
		
	}

}

/*********************************************************************************/
// setters 

void Schedular::set_processors_counter()
{
	if (processors_counter == total_processes)  //????
		time_step = 0;
	else
		time_step++;
}

void Schedular::set_RR_slice(int r) {
	RR_slice = r;
}

void Schedular::set_NF(int n) {
	NF = n;
}

void Schedular::set_NS(int s) {
	NS = s;
}

void Schedular::set_NR(int nr) {
	NR = nr;
}

void Schedular::set_total_processes(int tp) {
	total_processes = tp;
}

void Schedular::set_RTF(int rtf) {
	RTF = rtf;
}

void Schedular::set_MaxW(int mw) {
	MaxW = mw;
}

void Schedular::set_STL(int stl) {
	STL = stl;
}

void Schedular::set_total_WT(int twt) {
	total_WT = twt;
}

void Schedular::set_total_RT(int trtt) {
	total_RT = trtt;
}

void Schedular::set_total_TRT(int trttt) {
	total_TRT = trttt;
}

void Schedular::set_BLK_count(int blkc) {
	BLK_count = blkc;
}

void Schedular::inc_RUN_count(int runc) {
	RUN_count += runc;
}

// getters

int Schedular::get_processors_counter()
{
	return processors_counter;
}

int Schedular::get_RR_slice() {
	return RR_slice;
}

int Schedular::get_NF() {
	return NF;
}

int Schedular::get_NS() {
	return NS;
}

int Schedular::get_NR() {
	return NR;
}

int Schedular::get_NE() {
	return NE;
}

int Schedular::get_total_processes() {
	return total_processes;
}

int Schedular::get_RTF() {
	return RTF;
}

int Schedular::get_MaxW() {
	return MaxW;
}

int Schedular::get_STL() {
	return STL;
}

int Schedular::get_total_WT() {
	return total_WT;
}

int Schedular::get_total_RT() {
	return total_RT;
}

int Schedular::get_total_TRT() {
	return total_TRT;
}

int Schedular::get_BLK_count() {
	return BLK_count;
}

int Schedular::get_RUN_count() {
	return RUN_count;
}

int Schedular::get_timestep()
{
	return time_step;
}

void Schedular::NEW_RDY()
{
	// make sure that that the NEW isn't empty and also the arrival time of the first one equals to the time step
	while (!NEW.is_empty() && NEW.peek()->get_AT() == time_step) {
		int m = ShortestQueue(); // return the place of the proccesor which has the shortest queue
		Processors[m]->add2RDY(NEW.dequeue()); // move from NEW to be added in The Ready 
	}
}


void Schedular::P_Completion(process*p)
{
	if(p->get_CT_EX() ==p->get_CT())
	TRM.enqueue(p);	
}

int Schedular::ShortestQueue()
{
	int min = 0;// set the first proccessor in array is the shortest 
	for (int i = 1; i < NR + NF + NS + NE; i++) {
		if (Processors[i]->get_finishedTime() < Processors[min]->get_finishedTime() && !Processors[i]->Is_overheated()) {
				min = i; // get the place of the processor that has tha shortest queue
		}
	}
	return min;
}
int Schedular::ShortestQueue(int start, int finish)// overloaded ShortestQueue() that get as an input the range of processors to get the shortest of a certain processor type
{
	int min = start;
	for (int i = start + 1; i < finish; i++) {
		min = Processors[i]->get_finishedTime(); // set the first proccessor in array is the shortest 
		if (Processors[i]->get_finishedTime() < Processors[min]->get_finishedTime() && !Processors[i]->Is_overheated()) {
				min = i; // get the place of the processor that has tha shortest queue
		}
	}
	return min;
}
bool Schedular::BLK2RUN(process* pr) {
	if (BLK.is_empty()) { return false; }
	Processors[ShortestQueue()]->set_Run_pointer(pr);return true;
}

void Schedular::add2RDY(process* p) {
	if (p->get_Is_Child()) {
		int pro = ShortestQueue(0, NF);
		Processors[pro]->add2RDY(p);
	}
	else {
		int pro = ShortestQueue();
		Processors[pro]->add2RDY(p);
	}

}




