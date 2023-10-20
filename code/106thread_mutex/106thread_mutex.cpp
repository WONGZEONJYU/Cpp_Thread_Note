#include <thread>
#include <iostream>
#include <string>
#include <mutex>

//Linux -lpthread
using namespace std;
using namespace chrono;
using namespace this_thread;

static mutex mux;/*��ͨ��*/

void TestThread()
{
	for (;;) {

		//mux.lock();	/*��ȡ����Դ�������ȡ���ɹ��������ȴ�*/
		if (!mux.try_lock()){	/*
									���Ի�����������ȡ�ɹ�����true,���򷵻�false��
									�����������߳�,����Ȼ���ͷ�
								*/
			cout << "." << flush;
			sleep_for(milliseconds(100));
			continue;
		}
		cout << "===============================================" << endl;
		cout << "test 001" << endl;
		cout << "test 002" << endl;
		cout << "test 003" << endl;
		cout << "===============================================" << endl;
		mux.unlock();
		sleep_for(milliseconds(1000));
	}
}

void ThreadMainMux(const int x)
{
	for (;;) {
		mux.lock();
		cout << x << "[in]\n";
		sleep_for(milliseconds(1000));
		mux.unlock();/*����ϵͳ���������ͷ������*/
		sleep_for(milliseconds(1));

		/*
			������
				�������������1���̻߳�ȡ����Դ��2��3���߳��ڵȴ���
				��1���߳��ͷ�����Դ��������2��3���߳����һ���̻߳������Դ��lock()���Ϸ��أ�
				��ʼ�����¡������ǲ���ϵͳ�����������ͷŵ��������Դ��
				����ϵͳ�����϶����ȡ���������Դ����һ��ʱ���
				Ȼ��unlock()��lock()����֮������ʱ��̺̣ܶܶ����ͻ��ٴν���
		*/

		/*
			����취��
				��unlock()֮�󣬼�һ�����ʱȥ�ò���ϵͳ�����ʱ��ȥ�ͷ��������Դ��
				���unlock()֮�����»���ҵ���߼���Ҫ�������п��ܾͲ���Ҫ�����ʱ��
				��Ҫ�Ͳ���Ҫ����û�г������⡣
		*/
	}
}
static timed_mutex tmux;/*��ʱ��*/

void ThreadMainTime(const int x)
{
	for (;;) {
		/*
			if (!mux.try_lock()) {
				sleep_for(milliseconds(500));
				continue;
			}
		*/
		/*��ʱ���൱�������try_lock()��sleep_for�����ϣ���������д���ĺô����﷨����*/
		if (!tmux.try_lock_for(milliseconds(500))){/*��ʱ��*/

			cout << x << "[try_lock_for timeout]\n";/*��Ϊ��ʱ��־�������Ų����*/
			continue;
		}
		cout << x << "[in]\n";
		sleep_for(milliseconds(2000));
		tmux.unlock();
		sleep_for(milliseconds(1));
	}
}

static recursive_mutex rmux;/*�ݹ���(������)*/
static recursive_timed_mutex rtmux;/*��ʱ�ݹ������÷��볬ʱ��һ��*/
/*�˴�û����ʾ�ݹ鳬ʱ����Ӧ��*/

void Task1()
{
	rmux.lock();
	cout << __FUNCTION__ << "[in]\n";
	rmux.unlock();
}

void Task2()
{
	rmux.lock();
	cout << __FUNCTION__ << "[in]\n";
	rmux.unlock();
}

void ThreadMainRec(const int x)
{
	for (;;) {
		rmux.lock();
		Task1();
		cout << x << "[in]\n";
		sleep_for(milliseconds(2000));
		Task2();
		rmux.unlock();
		sleep_for(milliseconds(1));/*��ϵͳ���㹻��ʱ��ȥ�ͷ�����Դ*/
	}
}

int main(int argc, char* argv[])
{
	/*5*/

	(void)getchar();
	/*4*/
	for (int i{}; i < 3; i++) {
		thread th(ThreadMainRec, i + 1);
		th.detach();
	}
	(void)getchar();

	/*3*/
	for (int i{}; i < 3; i++) {
		thread th(ThreadMainTime, i + 1);
		th.detach();
	}
	(void)getchar();

	/*2*/
	for (int i{}; i < 3; i++) {

		thread th(ThreadMainMux, i + 1 );
		th.detach();
	}
	(void)getchar();

	/*1*/
	for (int i{}; i < 10; i++){
		thread th(TestThread);
		th.detach();
	}
	(void)getchar();

	return 0;
}

