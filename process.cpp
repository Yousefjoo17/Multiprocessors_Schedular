#include "process.h"
#include<iostream>
using namespace std;

process::process(int a, int p, int c,int d, int n, Queue<int>& queue) {
	AT = a;
	PID = p;
	CT = c;
	deadline = d;
	IO_total = n;
	IO = queue;
	right_child = nullptr;
	left_child = nullptr;
	Is_Child = false;
	CT_EX = 0;
	Is_First_Time = true;
	total_IO_D = 0;
}
process::process(bool x, process*& parent, int current_t, int p) {
	AT = current_t;
	PID = p;
	CT = parent->get_CT() - parent->get_CT_EX();
	deadline = parent->get_deadline();
	IO_total = 0;
	right_child = nullptr;
	left_child = nullptr;
	Is_Child = x;
	CT_EX = 0;
	Is_First_Time = true;
	total_IO_D = 0;

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

int process::peek_IO_R()
{
	if (!IO.is_empty())
		return IO.peek();
	else
		return -1;
}

int process::get_IO_R() {
	return IO.dequeue();
}
int process::get_IO_D() {
	int x = IO.dequeue();
	total_IO_D += x;
	return x;
}

int process::get_n_total() {
	return IO_total;
}
int process::get_rem_CT()
{
	return CT-CT_EX;
}
int process::get_curr_WT(int t)
{
	return t-AT-CT_EX;
}
int process::get_toatal_IO_D()
{
	return total_IO_D;
}
int process::get_deadline()
{
	return deadline;
}
bool process::is_first_time()
{
	return Is_First_Time;
}
process* process::get_Child() {
	return Child;
}
process* process::get_rightChild() {
	return right_child;
}
process* process::get_leftChild() {
	return left_child;
}


bool process::get_Is_Child() {
	return Is_Child;
}

void process::inc_CT_EX()
{
	CT_EX++;
}

void process::set_first_time(bool x)
{
	Is_First_Time = x;
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

void process::set_Child(process* x) {
	Child = x;
}
void process::set_leftchild(process* x) {
	left_child = x;
}
void process::set_rightchild(process* x) {
	right_child = x;
}
void process::set_Is_Child(bool x) {
	Is_Child = x;
}

process::~process()
{
}
