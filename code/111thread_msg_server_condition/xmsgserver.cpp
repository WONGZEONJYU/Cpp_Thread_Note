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
	lock.unlock();
	cv_.notify_one();
}

/*处理消息的线程入口函数*/
void XMsgServer::Main()
{
	while (!is_exit()){
		
		unique_lock<mutex> lock(mux_);
#if 0
		cv_.wait(lock);
		if (msgs_.empty()){
			continue;
		}
#endif // 0

		cv_.wait(lock, [this] {
			cout << "Wait cv\n";
			if (is_exit()){
				return true;
			}
			return !msgs_.empty();
			});

		while (!msgs_.empty()){
			/*消息处理业务逻辑*/
			cout << "recv : " << msgs_.front() << "\n";
			msgs_.pop_front();
		}
	}
}

void XMsgServer::Stop()
{
	is_exit_ = true;
	cv_.notify_all();
	Wait();
}
