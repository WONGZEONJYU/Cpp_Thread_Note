#include "xthread_pool.h"
#include <iostream>
using namespace std;
using namespace this_thread;

void XThreadPool::Init(const int num)
{
	unique_lock<mutex> lock(mux_);
	thread_num_ = num;
	cout << __FUNCTION__ << " : " << num << '\n';
}

void XThreadPool::Start()
{
	unique_lock<mutex> lock(mux_);

	if (thread_num_ <= 0){
		cerr << "Please Init XThreadPool\n";
		return;
	}

	if (!threads_.empty()){
		cerr << "Thread pool has start!\n";
		return;
	}

	for (int i {}; i < thread_num_; i++) {
		auto th { new thread(&XThreadPool::Run, this) };
		threads_.push_back(move(th));
	}
}

void XThreadPool::Run()
{
	cout << "begin " << __FUNCTION__ << " id : " << get_id() << '\n';
	while (true){
		auto task{ GetTask() };

		if (!task){ continue; }

		try{
			task->Run();
		}
		catch (...){
			cerr << "error\n";
		}
	}
	cout << "end " << __FUNCTION__ << " id : " << get_id() << '\n';
}

void XThreadPool::AddTask(XTask* task)
{
	unique_lock<mutex> lock(mux_);
	tasks_.push_back(task);
	lock.unlock();
	cv_.notify_one();
}

XTask* XThreadPool::GetTask()
{
	unique_lock<mutex> lock(mux_);

	if (tasks_.empty()){
		cv_.wait(lock);
	}

	if (tasks_.empty()) {
		return nullptr;
	}
	auto task{ tasks_.front() };
	tasks_.pop_front();
	return task;
}
