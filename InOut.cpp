#include "InOut.h"

InOut::InOut()
{
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