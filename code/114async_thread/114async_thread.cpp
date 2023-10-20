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
	/*�����첽�߳�*/

	cout << "main thread id : " << get_id() << '\n';/*�������id��ͬ����ʾ��ͬһ���߳���*/

	/*�������̵߳����첽����*/
	auto future{ async(launch::deferred, TestAsync,100) };
	sleep_for(milliseconds(100));
	cout << "begin future get\n";
	cout << "future get = " << future.get() << '\n'; /*ͬ��ͨ��future��ȡ���ؽ��*/
	cout << "end future get\n";

	/*�����첽�߳�*/
	cout << "===========================asynchronous thread============================\n";
	auto future2{ async(TestAsync,101) };/*Ĭ����Ϊ�Ǵ����̣߳��п��ܲ�������ȡ����ϵͳ*/
	//auto future2 {async(launch::async,TestAsync,100)}; /*����launch::async����������봴���߳�*/
	sleep_for(milliseconds(100));
	cout << "begin future2 get\n";
	cout << "future2 get = " << future2.get() << '\n'; /*ͬ��ͨ��future��ȡ���ؽ��*/
	cout << "end future2 get\n";

	(void)getchar();
	return 0;
}

