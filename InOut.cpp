#include "InOut.h"

InOut::InOut(Schedular* schedular)
{
	S_ptr = schedular;
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

void InOut::writefile(Queue<process*>& TRM, baseProcessor**)
{
	ofstream file("output_file.txt");
	file << "PID \t AT \t CT \t IO_D \t WT \t TRT" << endl;
	process* curr;
	for (int i = 0; i < S_ptr->get_total_processes(); i++) {
		curr = TRM.dequeue();
		file << curr->get_TT() << "\t";
		file << curr->get_PID() << "\t";
		file << curr->get_AT() << "\t";
		file << curr->get_CT() << "\t";
		//file << curr->get_() << "\t"; total IO_D;
		file << curr->get_WT() << "\t";
		file << curr->get_RT() << "\t";
		file << curr->get_TRT() << "\t";
		file << endl;
	}
	file << "Processes: " << S_ptr->get_total_processes()<<endl;


	/*file << "Avg WT = " << S_ptr->get_avg_TT(); add these functions
	file << ",\t Avg RT = " << S_ptr->get_avg_RT(); 
	file << ",\t Avg TRT = " << S_ptr->get_avg_TRT()  << endl;
	file << "Migration %:\t RTF= " << S_ptr->get_per_RTF();      ADD FUNCTIONS!
	file << "%,\t MaxW= " << S_ptr->get_per_MaxW() << "%" << endl;
	file << "Work Steal%: " << S_ptr->get_per_steal() << "%" << endl;
	file << "Forked Process%: " << S_ptr->get_per_forked() << "%" << endl;
	file << "Killed Process %: " << S_ptr->get_per_killed() << "%" << endl;*/
	file << endl;

	int num_processors= S_ptr->get_NF() + S_ptr->get_NR() + S_ptr->get_NS();
	file << "Processors: " << num_processors;
	file << " [" << S_ptr->get_NF() << " FCFS, ";
	file << S_ptr->get_NS() << " SJF, ";
	file << S_ptr->get_NR() << " RR]" << endl;


	file << "Processors Load" << endl;
	for (int i = 0; i < num_processors; i++)
	{
		
	}
	
	float avg_util;
	
	
	file.close();
}
