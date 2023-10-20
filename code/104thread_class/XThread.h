#ifndef XTHREAD_
#define XTHREAD_

#include <thread>

class XThread
{
	virtual void Main() = 0;
public:
	virtual void Start();
	virtual void Stop();
	virtual void Wait();
	bool is_exit() const;

private:
	std::thread th_{};
	bool is_exit_{};
};

#endif 
