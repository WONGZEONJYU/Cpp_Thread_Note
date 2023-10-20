#ifndef XTHREAD_H
#define XTHREAD_H

#include <thread>

class XThread
{
public:
	virtual void Start();/*启动线程*/
	virtual void Stop();/*设置线程退出标志 并等待*/
	virtual void Wait();/*等待线程退出（阻塞）*/
	bool is_exit() const;/*线程是否退出*/
	explicit operator bool() const;

protected:
	bool is_exit_ {};

private:
	virtual void Main() = 0;/*线程入口函数*/
	
	std::thread th_;
};

#endif // XTHREAD_H
