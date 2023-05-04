#include"UI.h"
#include<fstream>
#include<iostream>
#include"process.h"
#include"processorFCFS.h"
#include"processorRR.h"
#include"processorSJF.h"
#include"Queue.h"
#include"Schedular.h"

using namespace std;

UI::UI( Schedular* schedule) {
	the_scheduler = schedule;
}
void UI::display( baseProcessor** processors_arr, Queue<process*>& BLK, Queue <process*>& TRM, int numDisplay ) {
	/*
	cout << "Current Timestep:" << the_scheduler->get_total_processes();
	cout << endl;//* the curent Timestep
	baseProcessor** Processors = processors_arr;
	int NF = the_scheduler->get_NF();
	int NS = the_scheduler->get_NS();
	int NR = the_scheduler->get_NR();

	cout << "------------       RDY processes  ----------------" << endl;
	for (int i = 0; i < NF; i++) {
		cout << "processor " << i + 1 << "[FCFS]"; Processors[i]->print(); cout << endl;
	}
	for (int i = NF; i < NS + NF; i++) { cout << "processor " << i + NF + 1 << " [SJF ]"; Processors[i]->print(); cout << endl; }
	for (int i = NF + NS; i < NR + NS + NF; i++) { cout << "processor " << i + NF + NS + 1 << " [RR  ]"; Processors[i]->print(); cout << endl; }
	cout << endl;
	/////////////////////////////////////////////////////////////////////////
	cout << "------------       BLK processes  ----------------" << endl;
	int BLKC = the_scheduler->get_BLK_count();
	cout << BLKC << " BLK: ";
	BLK.print();
	cout << endl;
	////////////////////////////////////////////////////////////////////////////////
	cout << "------------       RUN processes  ----------------" << endl;
	int RUNC = the_scheduler->get_RUN_count();
	cout << RUNC << " RUN: ";//the array is required
	for (int i = 0; i < NF; i++) {
		if (Processors[i]->isbusy()) {
			cout << Processors[i]->get_RUN()->get_PID() << "(P" << i << ")";
			if (i < (NF - 1)) { cout << ","; }
		}
	}
	for (int i = NF; i < NS + NF; i++) {
		if (Processors[i]->isbusy()) {
			cout << Processors[i]->get_RUN()->get_PID() << "(P" << i + NF << ")";
			if (i < (NS + NF - 1)) { cout << ","; }
		}
	}
	for (int i = NF+NS; i < NF+NS+NR; i++) {
		if (Processors[i]->isbusy()) {
			cout <<Processors[i]->get_RUN()->get_PID() << "(P" << i + NF + NS << ")";
			if (i < (NR + NS + NF - 1)) { cout << ","; }
		}
	}
	cout << endl;

	//////////////////////////////////////////////////////////////////////////////////////////////
	cout << "------------       TRM processes  ----------------" << endl;
	int TRMC = the_scheduler->get_total_TRT();
	TRM.print();
	cout << "PRESS ANY KEY TO MOVE TO NEXT STEP !";
	system("pause");*/
	                                                  }
//end of func of display
UI::~UI(){};