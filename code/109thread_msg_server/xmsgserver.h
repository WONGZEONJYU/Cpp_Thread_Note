#ifndef XMSGSERVER_H
#define XMSGSERVER_H

#include "xthread.h"
#include <string>
#include <list>
#include <mutex>

class XMsgServer:public XThread
{
public:
	/*����ǰ�̷߳���Ϣ*/
	void SendMsg(const std::string& msg);

private:
	/*������Ϣ���߳���ں���*/
	virtual void Main() override;
	/*��Ϣ���л�����*/
	std::list<std::string> msgs_;
	/*���������Ϣ����*/
	std::mutex mux_;
};

#endif // XMSGSERVER_H
