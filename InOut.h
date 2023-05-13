#ifndef INOUT_H
#define INOUT_H
#pragma once
#include "Queue.h"
#include "process.h"
#include "baseProcessor.h"
#include "Schedular.h"
#include <iostream>
#include <fstream> 
#include <string>
using namespace std;

class Shedular;

class baseprocessor;

class InOut {
	Schedular* S_ptr;
	int arrtime, id, cputime,deadline, numio, io_r, io_d;
	process* p;

public:



	InOut(Schedular*);
	void readfile(string filename, Queue<process*>& NEW, Queue<int>& SignalKill, int& NF, int& NS, int& NR, int& NE, int& RR_slice, int& RTF, int& MaxW, int& STL, int& FP, int& overheatn, int& total_processes);
	void writefile(string,Queue<process*>& TRM, baseProcessor** );
};
#endif