#include <thread>
#include <iostream>
#include <string>
#include <mutex>
#include <shared_mutex>

//Linux -lpthread
using namespace std;
using namespace chrono;
using namespace this_thread;

/*c++17*/
//static shared_mutex smux;

/*c++14*/
static shared_timed_mutex stmux;

void ThreadRead(const int x)
{
	for (;;) {
		stmux.lock_shared();/*读取锁*/
		cout << x << "Read\n";
		//sleep_for(milliseconds(500));
		sleep_for(seconds(2));
		stmux.unlock_shared();
		sleep_for(milliseconds(1));
	}
}

void ThreadWrite(const int x)
{
	for (;;) {

		stmux.lock_shared();/*读取锁*/
		/*读取数据*/
		stmux.unlock_shared();
		/*如果读取锁没有释放，互斥锁是无法获取到锁资源的*/

		stmux.lock();/*互斥锁 ，要对临界资源进行写入，其他的读线程，写线程都不能读写临界资源*/
		cout << x << "Write\n";
		//sleep_for(milliseconds(300));
		sleep_for(seconds(5));
		stmux.unlock();
		sleep_for(milliseconds(1));
	}
}

int main(int argc, char* argv[])
{
	for (int i{}; i < 3; i++){

		thread th(ThreadWrite, i + 1);
		th.detach();
	}

	for (int i{}; i < 3; i++) {

		thread th(ThreadRead, i + 1);
		th.detach();
	}

	(void)getchar();
	return 0;
}
