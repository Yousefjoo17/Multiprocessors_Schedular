#include <iostream>
#include"process.h"
#include"QueueFCFS.h"
#include"Schedular.h"
#include<windows.h>

using namespace std;

int main() {
	
	priorityQueue<int> q1; Queue<int> q2; Queue<int> q3; Queue<int> q4;
	q1.enqueue(10,1); q1.enqueue(7, 2); q1.enqueue(1,4);
	srand(time(NULL));
	int r = 1 + (rand() % 100);
	cout << r;
	q2.enqueue(3); q2.enqueue(17); q2.enqueue(12); q2.enqueue(12);
	q3.enqueue(17); q3.enqueue(15); q3.enqueue(20); q3.enqueue(5);
	process* p1 = new process(3, 1, 200, 1,1, q2);
	process* p2 = new process(3, 2, 65, 2,1, q2);
	process* p3 = new process(5, 3, 34, 2,1, q3);
	QueueFCFS f;
	f.enqueue(p1);	f.enqueue(p2);	f.enqueue(p3);
	Schedular s("deadline_inp");
	s.simulate();
	baseProcessor* proc = new processorSJF(&s);
	cout << proc << endl;
	s.add2NEW(p1);
	s.add2NEW(p2);
	s.add2NEW(p3);
	cout << p1 <<endl;
	Sleep(1000);
	cout << s.getfromNEW();
	cout << s.getfromNEW();
	cout << s.getfromNEW();
	s.work_stealing();
	/***************************************/
}
