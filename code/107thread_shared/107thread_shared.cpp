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
		stmux.lock_shared();/*��ȡ��*/
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

		stmux.lock_shared();/*��ȡ��*/
		/*��ȡ����*/
		stmux.unlock_shared();
		/*�����ȡ��û���ͷţ����������޷���ȡ������Դ��*/

		stmux.lock();/*������ ��Ҫ���ٽ���Դ����д�룬�����Ķ��̣߳�д�̶߳����ܶ�д�ٽ���Դ*/
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
