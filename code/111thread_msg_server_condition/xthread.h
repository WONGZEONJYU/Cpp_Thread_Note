#ifndef XTHREAD_H
#define XTHREAD_H

#include <thread>

class XThread
{
public:
	virtual void Start();/*�����߳�*/
	virtual void Stop();/*�����߳��˳���־ ���ȴ�*/
	virtual void Wait();/*�ȴ��߳��˳���������*/
	bool is_exit() const;/*�߳��Ƿ��˳�*/
	explicit operator bool() const;

protected:
	bool is_exit_ {};

private:
	virtual void Main() = 0;/*�߳���ں���*/
	
	std::thread th_;
};

#endif // XTHREAD_H
