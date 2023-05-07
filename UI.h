#ifndef UI_H
#define UI_H
#pragma once
#include"Schedular.h"
class Schedular;
class baseProcessor;
class UI {
	int num_display;
	Schedular* S_ptr;
public:
	UI(Schedular*);
	void display(baseProcessor**, Queue<process*>& BLK, Queue <process*>& TRM, int numDisplay );
	~UI();

};
#endif