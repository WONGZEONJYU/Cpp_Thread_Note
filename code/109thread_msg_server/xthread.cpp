#include "xthread.h"
using namespace std;
/*�����߳�*/
void XThread::Start()
{
	is_exit_ = false;
	th_ = thread(&XThread::Main,this);
}

/*�����߳��˳���־ ���ȴ�*/
void XThread::Stop()
{
	is_exit_ = true;
	Wait();
}

/*�ȴ��߳��˳���������*/
void XThread::Wait()
{
	if (th_.joinable()){
		th_.join();
	}
}

/*�߳��Ƿ��˳�*/
bool XThread::is_exit() const
{
	return is_exit_;
}

XThread::operator bool() const
{
	return is_exit_;
}

