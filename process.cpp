#include "process.h"
#include<iostream>
using namespace std;

process::process(int a, int p, int c, int n, Queue<int>& queue) {
	AT = a;
	PID = p;
	CT = c;
	IO_total = n;
	IO = queue;
	Child = nullptr;
	Is_Child = false;
	CT_EX = 0;

}
process::process(bool x, process*& parent, int current_t, int p) {
	AT = current_t;
	PID = p;
	CT = parent->get_CT() - parent->get_CT_EX();
	IO_total = 0;
	IO_current = 0;
	Child = nullptr;
	Is_Child = x;
	CT_EX = 0;
	parent->set_Child(this);

}
int process::get_PID() {
	return PID;
}
int process::get_AT() {
	return AT;
}
int process::get_RT() {
	return RT;
}
int process::get_CT() {
	return CT;
}
int process::get_CT_EX() {
	return CT_EX;
}
int process::get_TT() {
	return TT;
}
int process::get_TRT() {
	return TT - AT;
}
int process::get_WT() {
	return TRT - CT;
}
int process::get_IO_R() {
	return IO.dequeue();
}
int process::get_IO_D() {
	return IO.dequeue();
}

int process::get_n_total() {
	return IO_total;
}
int process::get_n_current() {
	return IO_current;
}
process* process::get_Child() {
	return Child;
}
bool process::get_Is_Child() {
	return Is_Child;
}

void process::inc_CT_EX()
{
	CT_EX++;
}

void process::set_RT(int x) {
	RT = x - AT;
}
void process::set_CT_EX(int x) {
	CT_EX = x;
}
void process::set_TT(int x) {
	TT = x;
}

void process::set_n_current(int x) {
	IO_current = x;
}
void process::set_Child(process* x) {
	Child = x;
}
void process::set_Is_Child(bool x) {
	Is_Child = x;
}

process::~process()
{
}
