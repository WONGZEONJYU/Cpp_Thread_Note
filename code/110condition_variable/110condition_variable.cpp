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
		lock.unlock();/*���������������̶߳�ȡ��ʱ������������*/
		cv.notify_one();/*�����ź�*/
		//cv.notify_all();
		sleep_for(seconds(1));
	}
}

void ThreadRead(const int x)
{
	for (;;) {
		unique_lock<mutex> lock(mux);
		//cv.wait(lock);/*�Ƚ���Ȼ�������ȴ��ź�*/

		cv.wait(lock, [&]{  /*����true,������������false����������ϸ�뿴waitԴ������˵��*/
			//cout << __FUNCTION__ << " : " << x << " wait\n";
			return !msgs_.empty(); 
		});

		/*��ȡ���źţ�wait���أ�mux����*/
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
