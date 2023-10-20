#include "xmsgserver.h"
#include <iostream>

using namespace std;
using namespace this_thread;
using namespace chrono;
/*����ǰ�̷߳���Ϣ*/
void XMsgServer::SendMsg(const string& msg)
{
	unique_lock<mutex> lock(mux_);
	msgs_.push_back(msg);
}

/*������Ϣ���߳���ں���*/
void XMsgServer::Main()
{
	while (!is_exit()){
		
		sleep_for(milliseconds(10));
		unique_lock<mutex> lock(mux_);

		if (!msgs_.empty()){
			continue;
		}

		while (!msgs_.empty()){
			/*��Ϣ����ҵ���߼�*/
			cout << "recv : " << msgs_.front() << "\n";
			msgs_.pop_front();
		}
	}
}

