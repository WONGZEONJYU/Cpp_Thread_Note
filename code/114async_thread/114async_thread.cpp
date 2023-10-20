#include <iostream>
#include <thread>
#include <future>
#include <string>

using namespace std;
using namespace chrono;
using namespace this_thread;

string TestAsync(const int index)
{
	cout << index << " begin in " << __FUNCTION__ << " " << get_id() << '\n';
	sleep_for(seconds(2));

	string s { __FUNCTION__ };
	s += " string return";
	return s;
}

int main(int argc, char* argv[])
{
	/*创建异步线程*/

	cout << "main thread id : " << get_id() << '\n';/*如果两个id相同，表示在同一个线程中*/

	/*不创建线程调用异步任务*/
	auto future{ async(launch::deferred, TestAsync,100) };
	sleep_for(milliseconds(100));
	cout << "begin future get\n";
	cout << "future get = " << future.get() << '\n'; /*同样通过future获取返回结果*/
	cout << "end future get\n";

	/*创建异步线程*/
	cout << "===========================asynchronous thread============================\n";
	auto future2{ async(TestAsync,101) };/*默认行为是创建线程，有可能不创建，取决于系统*/
	//auto future2 {async(launch::async,TestAsync,100)}; /*带上launch::async参数代表必须创建线程*/
	sleep_for(milliseconds(100));
	cout << "begin future2 get\n";
	cout << "future2 get = " << future2.get() << '\n'; /*同样通过future获取返回结果*/
	cout << "end future2 get\n";

	(void)getchar();
	return 0;
}

