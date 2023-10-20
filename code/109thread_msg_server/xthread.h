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
private:
	virtual void Main() = 0;/*�߳���ں���*/
	bool is_exit_ {};
	std::thread th_;
};

#endif // XTHREAD_H
