#include "xmsgserver.h"
#include <iostream>

using namespace std;
using namespace this_thread;
using namespace chrono;
/*给当前线程发消息*/
void XMsgServer::SendMsg(const string& msg)
{
	unique_lock<mutex> lock(mux_);
	msgs_.push_back(msg);
}

/*处理消息的线程入口函数*/
void XMsgServer::Main()
{
	while (!is_exit()){
		
		sleep_for(milliseconds(10));
		unique_lock<mutex> lock(mux_);

		if (!msgs_.empty()){
			continue;
		}

		while (!msgs_.empty()){
			/*消息处理业务逻辑*/
			cout << "recv : " << msgs_.front() << "\n";
			msgs_.pop_front();
		}
	}
}

