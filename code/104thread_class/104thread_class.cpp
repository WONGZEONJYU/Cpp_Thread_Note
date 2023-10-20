#include <iostream>
#include <string>
#include "XThread.h"

/*Linux -lpthread*/

using namespace std;
using namespace chrono;
using namespace this_thread;

class MyThread
{
public:
	/*入口线程函数*/
	void Main() {
		cout << "MyThread " << __FUNCTION__ << 
			name << " : " << age << "\n";
	}
	string name{};
	int age{ 100 };
};

class TestXThread :public XThread
{
public:
	void Main() override {

		cout <<  __FUNCTION__ << " begin\n";

		while (!is_exit()){
			this_thread::sleep_for(chrono::milliseconds(100));
			cout << "." << flush;
		}

		cout << "\n" << __FUNCTION__ << " end\n";
	}
	string name;
};

int main(int argc, char* argv[])
{
	TestXThread test_th;
	test_th.name = "TestXThread name";
	test_th.Start(); 
	sleep_for(chrono::seconds(3));
	test_th.Stop();
	(void)getchar();

#if 0
	MyThread myth;
	myth.name = "Test name 001";
	myth.age = 20;
	thread th(&MyThread::Main, &myth);
	th.join();
	(void)getchar();
#endif // 0

	return 0;
}
