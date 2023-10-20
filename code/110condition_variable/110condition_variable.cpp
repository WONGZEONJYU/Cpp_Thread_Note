#include <iostream>
#include <thread>
#include <mutex>
#include <list>
#include <string>
#include <sstream>

using namespace std;
using namespace chrono;
using namespace this_thread;

static list<string> msgs_;
static mutex mux;
static condition_variable cv;

void ThreadWrite()
{
	for (int i{};;i++) {

		stringstream ss;
		ss << "Write msg : " << i << '\n';
		unique_lock<mutex> lock(mux);
		msgs_.push_back(ss.str());
		lock.unlock();/*如果不解锁，别的线程读取的时候可能造成死锁*/
		cv.notify_one();/*发送信号*/
		//cv.notify_all();
		sleep_for(seconds(1));
	}
}

void ThreadRead(const int x)
{
	for (;;) {
		unique_lock<mutex> lock(mux);
		//cv.wait(lock);/*先解锁然后阻塞等待信号*/

		cv.wait(lock, [&]{  /*返回true,不阻塞，返回false，阻塞，详细请看wait源码和相关说明*/
			//cout << __FUNCTION__ << " : " << x << " wait\n";
			return !msgs_.empty(); 
		});

		/*获取到信号，wait返回，mux锁定*/
		while (!msgs_.empty()){
			cout << __FUNCTION__ << " : " << x << " " << msgs_.front() << '\n';
			msgs_.pop_front();
		}
	}
}

int main(int argc, char* argv[])
{
	thread th(ThreadWrite);
	th.detach();

	for (int i{}; i < 3; i++) {
		thread th { ThreadRead ,i + 1 };
		th.detach();
	}
	(void)getchar();
	return 0;
}
