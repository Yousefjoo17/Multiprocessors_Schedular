#include "Schedular.h"

Schedular::Schedular(string file) {
	//Processors = nullptr;
	time_step = 0;
	BLK_count = 0;
	TRM_count = 0;
	RUN_count = 0;
	processors_counter = 0;
	Running_time = 0;
	total_RT = 0;
	total_TRT = 0;
	total_WT = 0;
	string filename = file;
	InOut io;
	io.readfile(filename, NEW, SigKill, NF, NS, NR, RR_slice, RTF, MaxW, STL, FP, total_processes);
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
	TRM.enqueue(p);
}

void Schedular::simulate()
{
		string filename = "input_file";
		InOut io;
		io.readfile(filename, NEW, SigKill, NF, NS, NR, RR_slice, RTF, MaxW, STL, FP, total_processes);
		//UI user_interface(this);
		processorFCFS::set_sig(SigKill);
		processorRR::set_rtf(RTF);
		for (int i = 0; i < NF; i++) {
			Processors[i] = new processorFCFS(this);
		}
		for (int i = NF; i < NS + NF; i++) {
			Processors[i] = new processorSJF(this);
		}
		for (int i = NF + NS; i < NR + NS + NS; i++) {
			Processors[i] = new processorRR(this);
		}
}

/*********************************************************************************/
// setters 

void Schedular::set_processors_counter()
{
	if (processors_counter == total_processes)
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

void Schedular::set_RUN_count(int runc) {
	RUN_count = runc;
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
void migrate_RR_SJF() {



}

void Schedular::P_Completion(process*p)
{
	if(p->get_CT_EX() ==p->get_CT())
	TRM.enqueue(p);	
}

int Schedular::ShortestQueue()
{
	int min = 0;
	for (int i = 0; i < get_processors_counter(); i++) {
		min = Processors[i]->get_finishedTime(); // set the first proccessor in array is the shortest 
		if (min > Processors[i]->get_finishedTime()) {
			min = i; // get the place of the processor that has tha shortest queue
		}
	}
	return min;
}
int Schedular::ShortestQueue(int start, int finish)
{
	int min = 0;
	for (int i = start; i < finish; i++) {
		min = Processors[i]->get_finishedTime(); // set the first proccessor in array is the shortest 
		if (min > Processors[i]->get_finishedTime()) {
			min = i; // get the place of the processor that has tha shortest queue
		}
	}
	return min;
}
bool Schedular::BLK2RUN(process* pr) {
	if (BLK.is_empty()) { return false; }
	Processors[ShortestQueue()]->set_Run_pointer(pr);

}





