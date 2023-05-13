#include"UI.h"


using namespace std;

UI::UI( Schedular* scheduler) {
	S_ptr = scheduler;
	do{ cout << "Enter 1 for Interactive Mode , 2 for Step-by-step Mode or 3 for Silent Mode: ";
	cin >> display_mode;
	} while (display_mode < 1 || display_mode>3 );
}
void UI::display( baseProcessor** processors_arr, Queue<process*>& BLK, Queue <process*>& TRM) {
	if (display_mode==3) {
		cout << "Silent Mode................    Simulation Starts"<<endl;
			cout<<"Simulation ends, Output file created";
	}
	
	if (display_mode == 1 || display_mode == 2) {
		cout << "Current Timestep:" << S_ptr->get_timestep();
		cout << endl;//* the curent Timestep
		baseProcessor** Processors = processors_arr;
		int NF = S_ptr->get_NF();
		int NS = S_ptr->get_NS();
		int NR = S_ptr->get_NR();
		int NE = S_ptr->get_NE();

		cout << "------------       RDY processes  ----------------" << endl;
		for (int i = 0; i < NF; i++) {
			cout << "processor " << i + 1 << "[FCFS]"; Processors[i]->print(); cout << endl;
		}
		for (int i = NF; i < NS + NF; i++) {
			cout << "processor " << i+ 1 << " [SJF ]"; Processors[i]->print(); cout << endl; 
		}
		for (int i = NF + NS; i < NR + NS + NF; i++) { 
			cout << "processor " << i + 1 << " [RR  ]"; Processors[i]->print(); cout << endl; 
		}
		for (int i = NF + NS + NR; i < NR + NS + NF + NE; i++) { 
			cout << "processor " << i + 1 << " [EDF ]"; Processors[i]->print(); cout << endl; 
		}
		cout << endl;
		/////////////////////////////////////////////////////////////////////////
		cout << "------------       BLK processes  ----------------" << endl;
		int BLKC = S_ptr->get_BLK_count();
		cout << BLKC << " BLK: ";
		BLK.print();
		cout << endl;
		////////////////////////////////////////////////////////////////////////////////
		cout << "------------       RUN processes  ----------------" << endl;
		int RUNC = S_ptr->get_RUN_count();
		cout << RUNC << " RUN: ";//the array is required
		for (int i = 0; i < NF + NS + NR + NE; i++) {
			if (Processors[i]->get_RUN()) {
				cout << Processors[i]->get_RUN() << "(P" << i+1 << ")";
				if (i < (NR + NS + NF + NE - 1)) { cout << ", "; }
			}
		}
		cout << endl;

		//////////////////////////////////////////////////////////////////////////////////////////////
		cout << "------------       TRM processes  ----------------" << endl;
		int TRMC = S_ptr->get_total_TRT();
		cout << TRMC << " TRM: ";
		TRM.print();
		cout << endl << endl;
		if (display_mode == 1)
			system("pause");
		else
			Sleep(1000);
	}

}
//end of func of display
UI::~UI(){};