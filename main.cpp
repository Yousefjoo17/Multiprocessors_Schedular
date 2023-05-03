#include <iostream>
#include"process.h"
#include"QueueFCFS.h"
#include"Schedular.h"
using namespace std;

int main() {


	Queue<int> q1; Queue<int> q2; Queue<int> q3; Queue<int> q4;
	q1.enqueue(1); q1.enqueue(7);
	q2.enqueue(3); q2.enqueue(17); q2.enqueue(12); q2.enqueue(12);
	q3.enqueue(17); q3.enqueue(15); q3.enqueue(20); q3.enqueue(5);
	process* p1 = new process(3, 1, 200, 1, q1);
	process* p2 = new process(3, 2, 65, 2, q2);
	process* p3 = new process(5, 3, 34, 2, q3);
	QueueFCFS f;
	f.enqueue(p1);	f.enqueue(p2);	f.enqueue(p3);

	Schedular s("input_file");
	s.add2NEW(p1);
	s.add2NEW(p2);
	s.add2NEW(p3);
	cout << s.getfromNEW()->get_PID();
	cout << s.getfromNEW()->get_PID();
	cout << s.getfromNEW()->get_PID();

	/***************************************/
}
