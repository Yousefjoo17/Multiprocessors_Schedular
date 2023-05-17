#ifndef UI_H
#define UI_H
#pragma once
#include"Schedular.h"
#include<iostream>
#include"process.h"
#include"Queue.h"
#include"Schedular.h"
#include<Windows.h> // FOR sleeping	
class Schedular;
class baseProcessor;
class UI {
	int display_mode;
	Schedular* S_ptr;
public:
	UI(Schedular*);
	void display(baseProcessor**, Queue<process*>& BLK, Queue <process*>& TRM);
	~UI();

};
#endif