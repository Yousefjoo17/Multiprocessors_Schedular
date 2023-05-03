#ifndef INOUT_H
#define INOUT_H
#pragma once
#include "Queue.h"
#include "process.h"
#include <iostream>
#include <fstream> 
#include <string>
using namespace std;
class InOut {
	int arrtime, id, cputime, numio, io_r, io_d;
	process* p;

public:



	InOut();
	void readfile(string filename, Queue<process*>& NEW, Queue<int>& SignalKill, int& NF, int& NS, int& NR, int& RR_slice, int& RTF, int& MaxW, int& STL, int& FP, int& total_processes);

};
#endif