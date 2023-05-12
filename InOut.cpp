#include "InOut.h"
using namespace std;

#include"Schedular.h"
#include"baseProcessor.h"



InOut::InOut(Schedular* ptr)
{
	S_ptr = ptr;
	numio = 0;
}

void InOut::readfile(string filename, Queue<process*>& NEW, Queue<int>& SignalKill, int& NF, int& NS, int& NR, int& RR_slice, int& RTF, int& MaxW, int& STL, int& FP, int& total_processes)
{
	ifstream file(filename + ".txt");
	if (!file.is_open())
		cout << "wrong file name!";
	char temp = ' '; // temp chat to ger rid of braces and commas
	file >> NF >> NS >> NR >> RR_slice >> RTF >> MaxW >> STL >> FP >> total_processes;
	for (int i = 0; i < total_processes; i++) {
		file >> arrtime >> id >> cputime >> numio;
		Queue<int> io;
		if (numio > 0) {
			for (int j = 0; j < numio; j++) {
				file >> temp;
				file >> io_r;
				file >> temp;
				file >> io_d;
				file >> temp;
				io.enqueue(io_r);
				io.enqueue(io_d);
				if (j != numio - 1)
					file >> temp;
			}
		}
		p = new process(arrtime, id, cputime, numio, io);
		NEW.enqueue(p);
	}
	for (int i = 0; i < 12; i++) {
		file >> temp;
	}

	while (!file.eof()) {
		file >> cputime >> id;
		SignalKill.enqueue(cputime);
		SignalKill.enqueue(id);
	}

	file.close();

}

void InOut::writefile(string filename, Queue<process*>& TRM, baseProcessor** procossors)
{
	ofstream file(filename + ".txt");
	file << "PID \t AT \t CT \t IO_D \t WT \t TRT" << endl;
	process* curr;
	for (int i = 0; i < S_ptr->get_total_processes(); i++) {
		curr = TRM.dequeue();
		file << curr->get_TT() << "\t";
		file << curr->get_PID() << "\t";
		file << curr->get_AT() << "\t";
		file << curr->get_CT() << "\t";
		file << curr->get_toatal_IO_D()<< "\t";
		file << curr->get_WT() << "\t";
		file << curr->get_RT() << "\t";
		file << curr->get_TRT() << "\t";
		file << endl;
	}
	file << "Processes: " << S_ptr->get_total_processes()<<endl;

	// ADD FUNCTIONS in Schedular!
	/*file << "Avg WT = " << S_ptr->get_avg_WT();  gets average Waiting time for processes
	file << ",\t Avg RT = " << S_ptr->get_avg_RT(); gets average Response time for processes
	file << ",\t Avg TRT = " << S_ptr->get_avg_TRT()  << endl; gets Termination time for processes
	file << "Migration %:\t RTF= " << S_ptr->get_per_RTF();  gets Percentage of process migration due to RTF 
	file << "%,\t MaxW= " << S_ptr->get_per_MaxW() << "%" << endl;   gets Percentage of process migration due to MaxW
	file << "Work Steal%: " << S_ptr->get_per_steal() << "%" << endl; gets Percentage of process moved by work steal
	file << "Forked Process%: " << S_ptr->get_per_forked() << "%" << endl; gets Percentage of process fork
	file << "Killed Process %: " << S_ptr->get_per_killed() << "%" << endl;gets Percentage of process kill */
	file << endl;

	int NF = S_ptr->get_NF();
	int NR = S_ptr->get_NR();
	int NS = S_ptr->get_NS();
	int num_processors = NF + NS + NR;
	file << "Processors: " << num_processors;
	file << " [" << NF << " FCFS, ";
	file << NS << " SJF, ";
	file << NR << " RR]" << endl;

	
	file << "Processors Load" << endl;
	for (int i = 0; i < NF; i++) {
		//file << "p" << i + 1 << "=" << procossors[i]->get_processor_load();
		if (i != NF - 1)
				file<<"%,\t";
	}
	file << endl;
	for (int i = NF; i < NS + NF; i++) {
		//file << "p" << i + 1 << "=" << procossors[i]->get_processor_load();
		if (i != NF + NS - 1)
			file << "%,\t";
	}
	file << endl;

	for (int i = NF + NS; i < NR + NS + NS; i++) {
		//file << "p" << i + 1 << "=" << procossors[i]->get_processor_load();
		if (i != NF + NS + NR - 1)
			file << "%,\t";
	}
	file << endl;


	file << "Processor Utiliz" << endl;
	float avg_utiliz = 0;

	for (int i = 0; i < NF; i++) {
		//file << "p" << i + 1 << "=" << procossors[i]->get_processor_utiliz();
		//avg_utiliz += float(procossors[i]->get_processor_utiliz())/ float(num_processors);
		if (i != NF - 1)
			file << "%,\t";
	}
	file << endl;
	for (int i = NF; i < NS + NF; i++) {
		//file << "p" << i + 1 << "=" << procossors[i]->get_processor_utiliz();
		//avg_utiliz += float(procossors[i]->get_processor_utiliz()) / float(num_processors);
		if (i != NF + NS - 1)
			file << "%,\t";
	}
	file << endl;

	for (int i = NF + NS; i < NR + NS + NS; i++) {
		//file << "p" << i + 1 << "=" << procossors[i]->get_processor_utiliz();
		//avg_utiliz += float(procossors[i]->get_processor_utiliz()) / float(num_processors);
		if (i != NF + NS + NR - 1)
			file << "%,\t";
	}
	file << "Average Utiliz = " << avg_utiliz << "%";
	
	
	file.close();
}
