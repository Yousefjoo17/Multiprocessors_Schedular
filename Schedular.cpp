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
	ForkedProcesses = 0;
	KilledProcesses = 0;
	totalworksteal=0;
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
	BLK_count++;
	int x = p->get_IO_R();
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
	total_RT += p->get_RT();
	total_TRT += p->get_TRT();
	total_WT += p->get_WT();
	if (p->get_leftChild() || p->get_rightChild()) {
		KillChild(p); // recursively call
	}	
	TRM_count++;
	p->set_Is_TRM(true);
	TRM.enqueue(p);
}

void Schedular::simulate()
{
		string filename = "input_file";
		InOut io(this);
		UI user_interface(this);
		if (NS == 0) {
			RTF = -1;
		}
		if (NR == 0) {
			MaxW = -1;
		}
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
		while (time_step <1116) {
			time_step++;
			NEW_RDY();
			/*if (time_step % STL == 0)
				work_stealing();*/
			for (int i = 0; i < NF; i++) {
				processorFCFS* ptr = dynamic_cast<processorFCFS*>(Processors[i]);
				ptr->KillSig();
			}
			loop_p();
			update_BLK();
			user_interface.display(Processors, BLK, TRM);

		}
		while (TRM_count!=total_processes) {
			time_step++;
			NEW_RDY();
			/*if (time_step % STL == 0)
				work_stealing();*/
			for (int i = 0; i < NF; i++) {
				processorFCFS* ptr = dynamic_cast<processorFCFS*>(Processors[i]);
				ptr->KillSig();
			}
			loop_p();
			update_BLK();
			user_interface.display(Processors, BLK, TRM);

		}
		io.writefile("test", TRM, Processors);
	

	/*	while (time_step < 35) {
			time_step++;
			NEW_RDY();
			
			loop_p();
			cout << Processors[5]->Is_overheated() << " " << Processors[6]->Is_overheated() << " " << Processors[7]->Is_overheated() << " " << Processors[8]->Is_overheated() << " " << endl;
			update_BLK();
			user_interface.display(Processors, BLK, TRM);
		}*/
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
// Stealing 
void Schedular::work_stealing()
{
	int LQF, SQF, LQF_ind, SQF_ind;
	LQF_ind = SQF_ind = 0;
	LQF = Processors[0]->get_finishedTime(); // Assign the first to LQF as initilaiztion
	SQF = Processors[0]->get_finishedTime(); // Assign the first to SQF as initilaiztion
	//NF // number of FCFS processors 
	//NS // number of SJF processors 
	//NR // number of RR processors
	//NE // number of EDF processors
	for (int i = 1; i < (NF + NS + NR + NE); i++)
	{
		if (Processors[i]->get_finishedTime() > LQF)
		{
			// if processor's finish time is greater than the LQF 
			// let the LQF equals to this time
			// and get the  index of this processor 
			LQF = Processors[i]->get_finishedTime();
			LQF_ind = i;
		}
		if (Processors[i]->get_finishedTime() < SQF)
		{
			// if not then store this time in SQF 
			// and also get the index if this processor
			SQF = Processors[i]->get_finishedTime();
			SQF_ind = i;
		}
	}
		if (LQF == 0)
			return;
		baseProcessor* ptr_LQF = Processors[LQF_ind]; // assign the highest to the ptr_LQF
		baseProcessor* ptr_SQF = Processors[SQF_ind]; // assign the lowest to the ptr_SQF
		
		
		Stack<process*>s(50);// creation of Stack of processes 
		process* ptr; // pointer to process
		
		float Ratio = float(LQF - SQF) / float(LQF); // calculation of the Ratio
		while (Ratio > 0.40)
		{
			LQF = ptr_LQF->get_finishedTime();
			SQF = ptr_SQF->get_finishedTime();

			while (ptr_LQF->peek_RDY())   // FCFS Processors only // look at the the first RDY from the ptr_LQF and check whether it's child or not	
			{
				if (ptr_LQF->peek_RDY()->get_Is_Child())
					s.push(ptr_LQF->getfromRDY());  // take from the ready and push it in the stack created before
			}
			if (ptr_LQF->peek_RDY())
			{process* p = ptr_LQF->getfromRDY();
				ptr_SQF->add2RDY(p); // add in the ready of the shortest Queue the upcoming from the Longest one
				totalworksteal++;
				ptr_SQF->inc_finsihtime(p->get_CT() - p->get_CT_EX());  // increses the finsih time of the processor by the remained time 
				ptr_LQF->inc_finsihtime(p->get_CT_EX() - p->get_CT());
		}   // decrease ---  -----  --  -  --  ------- - ---  --- 
			SQF = ptr_SQF->get_finishedTime();  //reset SQF
			LQF = ptr_LQF->get_finishedTime();   //reset LQF
		}

		process* pr;
		while (s.pop(pr)) // start popping 
		{
			ptr_LQF->add2_RDY_begining(pr);
		}
		
	

}

void Schedular::update_BLK()
{
	if (BLK.is_empty())
		return;
	else if (BLK.peek()->get_IO_D_EX() < BLK.peek()->peek_IO_D())
	{
		BLK.peek()->inc_IO_D_EX();
	}
	else
	{
		process* ptr = BLK.dequeue();
		ptr->get_IO_D();
		BLK_count--;
		Processors[ShortestQueue()]->add2RDY(ptr);
	}

}

void Schedular::KillChild(process* parent )
{
	if (parent == nullptr) {
		return;
	}
	process* left = parent->get_leftChild();
	process* right = parent->get_rightChild();
	if (left) {
		if (!left->Is_TRM()) {
			bool l= false;
			for (int i = 0; i < NF; i++) {
				processorFCFS* ptr = dynamic_cast<processorFCFS*>(Processors[i]);
				l=ptr->remove_child(left->get_PID());
				if (l)
					break;
			}
			add2TRM(left);
		}
	}
	if (right) {
		if (!right->Is_TRM()) {
			bool r = false;
			for (int i = 0; i < NF; i++) {
				processorFCFS* ptr = dynamic_cast<processorFCFS*>(Processors[i]);
				r = ptr->remove_child(right->get_PID());
				if (r)
					break;
			}
			add2TRM(right);
		}
	}
	
}

void Schedular::forking_tree_algo(process* parent) {
	srand(time(nullptr));
	if (1 + (rand() % 100) <= FP)
	{
		process* left=parent->get_leftChild(); 
		process* right = parent->get_rightChild();
		if (!left) {
			left = new process(true, parent, time_step, ++total_processes); //create new child and add it to the left side
			parent->set_leftchild(left);
			int pro = ShortestQueue(0, NF);
			Processors[pro]->add2RDY(left);
			ForkedProcesses++;
			
		}
		else if (!right && left) {
			right = new process(true, parent, time_step, ++total_processes); // create new child and add to right
			parent->set_rightchild(right); // setting 
			int pro = ShortestQueue(0, NF);
			Processors[pro]->add2RDY(right);
			ForkedProcesses++;
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

int Schedular::get_TRM_count()
{
	return TRM_count;
}

int Schedular::get_timestep()
{
	return time_step;
}

int Schedular::get_avg_WT()
{
	return float(total_WT )/float(total_processes);
}

int Schedular::get_avg_RT()
{
	return float(total_RT) / float(total_processes);
}

int Schedular::get_avg_TRT()
{
	return float(total_TRT)/ float(total_processes);
}

float Schedular::get_per_RTF()
{
	float R = (float)RTF_Processes;
	float t = (float)total_processes;
	return (R/t);
}

float Schedular::get_per_steal()
{
	float tw=(float)totalworksteal;
	float t = (float)total_processes;

	return(tw/t);
}

float Schedular::get_per_MaxW()
{
	float M = (float)MaxW_Processes;
	float t = (float)total_processes;
	return (M/t);
}

float Schedular::get_per_forked()
{
	float F = (float)ForkedProcesses;
	float t = (float)total_processes;
	return (F / t);
}

float Schedular::get_per_killed()
{
	float K=(float)KilledProcesses;
	float t = (float)total_processes;
	return(K/t);
}

float Schedular::get_per_deadline()
{
	float B=(float)BeforeDeadline;
	float t = (float)total_processes;
	return (B/t);
}

void Schedular::inc_kill_count() {
	KilledProcesses++;

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





