#include "XThread.h"

void XThread::Start()
{
	is_exit_ = false;
	th_ = std::move(std::thread(&XThread::Main, this));
}

void XThread::Stop()
{
	is_exit_ = true;
	Wait();
}

void XThread::Wait() 
{
	if (th_.joinable()) {
		th_.join();
	}
}

bool XThread::is_exit() const {
	return is_exit_;
}
