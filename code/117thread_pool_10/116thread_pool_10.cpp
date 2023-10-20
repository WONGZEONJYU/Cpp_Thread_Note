#include <iostream>
#include <thread>
#include <string>
#include <chrono>
#include "xthread_pool.h"
using namespace std;
using namespace this_thread;
using namespace chrono;

class MyTask:public XTask
{
public:
	int Run() override {
		cout << "================================================" << '\n';
		cout << get_id() << " Mytask " << name << '\n';
		cout << "================================================" << '\n';
		return 0;
	}

	string name {};
};

int main(int argc, char* argv[])
{
	XThreadPool pool;
	pool.Init(16);
	pool.Start();

	MyTask task1;
	task1.name = "test name 001";
	pool.AddTask(&task1);
	_CRT_UNUSED(getchar());
	return 0;
}

