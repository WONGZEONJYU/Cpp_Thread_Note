#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <shared_mutex>
#include "XMutex.h"

//Linux -lpthread
using namespace std;
using namespace chrono;
using namespace this_thread;

static mutex mux;

void TestMutex(const int status)
{
	XMutex lock(mux);
	
	if (1 == status){
		cout << "==1\n";
	}else {
		cout << "!=1\n";
	}
}

static mutex gmutex;

void TestLockGuard(const int i)
{
	gmutex.lock();

	{
		//lock_guard<mutex> lock(gmutex); /*�ٴ������׳��쳣*/
		lock_guard<mutex> lock(gmutex,adopt_lock);/*�����׳��쳣*/

		/*����lock_guard class���ذ�Ĺ��캯���������ٴ�����,ԭ����鿴Դ��*/
		/*��ͨ�������λ��׳��쳣���ݹ����Ͳ���*/
	}

	{
		lock_guard<mutex> lock(gmutex);
		cout << "begin thread" << i << "\n";
	}

	for (;;) {

		{
			lock_guard<mutex> lock(gmutex);
			cout << "In" << i << "\n";
		}
		sleep_for(milliseconds(500));
	}
}

static mutex mux1;
static mutex mux2;

void TestScope1()
{
	/*ģ������ ͣ100ms����һ���߳���mux2*/
	sleep_for(milliseconds(100));
	cout << __FUNCTION__<< " : " << get_id() << " begin mux1 lock\n";
	//mux1.lock();
	cout << __FUNCTION__ << " : " << get_id() << " begin mux2 lock\n";
	//mux2.lock();	/*����*/

	//lock(mux1, mux2);	/*C++11������������������Ͽ��ܳ���������API*/

	scoped_lock lock(mux1, mux2);/*C++17����*/

	cout << __FUNCTION__ << '\n';
	sleep_for(milliseconds(1000));
	//mux1.unlock();
	//mux2.unlock();
}

void TestScope2()
{
	cout << __FUNCTION__ << " : " << get_id() << " begin mux2 lock\n";
	mux2.lock();
	sleep_for(milliseconds(500));
	cout << __FUNCTION__ << " : " << get_id() << " begin mux1 lock\n";
	mux1.lock();	/*����*/
	cout << __FUNCTION__ << '\n';
	sleep_for(milliseconds(1000));
	mux1.unlock();
	mux2.unlock();
}

int main(int argc, char* argv[])
{
	/*5*/
	{
		/*������ʾ*/
		{
			thread th1(TestScope1);
			th1.detach();
		}
		{
			thread th2(TestScope2);
			th2.detach();
		}
	}

	(void)getchar();
	/*4*/
	{
		static shared_timed_mutex tmux;/*������*/
		{
			/*��ȡ�� == ������*/
			shared_lock<shared_timed_mutex> lock(tmux);/*�˹��캯������ù�����*/
			/*�˳�ջ�� �ͷŹ�����*/
			/*shared_lock�ĳ�Ա����lock()ֻ�����lock_shared()��������û�취���û�����*/
			cout << "read data\n";
			/*��ʾ�����������ͷŲ����ϻ�����*/

			/*��ε��û��������뿴�������*/
		}
		
		{
			/*д���� == ������*/
			unique_lock<shared_timed_mutex> lock(tmux);
			cout << "write data\n";
			/*
				ʹ��shared_lockҪ��unique_lock���ʹ�ã�
				��Ϊshared_lockֻ�ܵ��ú��ͷŹ���������������unique_lock��lock_guard���
			*/
		}

	}
	(void)getchar();
	/*3 unique_lock ���Խ��Դ��������*/
	/*������Ŀ����ȥѡ����һ��*/
	{
		static mutex mux_1;/*������*/
		{
			/*��ʱ������һ��������ת�����ݵ�ʱ����õ�*/
			unique_lock<mutex> lock(mux_1);
			/*unique_lock����ʱ��������˳�ջ���������unique_lock����ʱ���ͷ�����*/
			lock.unlock();/*��ʱ�ͷ�����������ټ�����unique_lock��������Ҫ����*/
			lock.lock();
			/*�ٽ�������ٴ�����������unique_lock�ĳ�Ա����ȥ���ã�����ֱ��ʹ��mutex�ĳ�Ա����*/
		}

		{
			mux_1.lock();
			unique_lock<mutex> lock(mux_1, adopt_lock);
			/*�Ѿ�ӵ���� ���������˳�ջ��������unique_lock����ʱ������*/
		}

		{
			unique_lock<mutex> lock(mux_1, defer_lock);
			/*�Ƴټ������Ӻ������ ����󲻻�ȥ����� �˳�ջ����������unique_lock����ʱ��������*/
			lock.lock();
			/*�������˳�ջ��������unique_lock����ʱ�������*/
		}

		{
			//mux_1.lock(); /*�˴�ģ�����������߳��Ѿ����*/
			unique_lock<mutex> lock(mux_1,try_to_lock);
			/*���Լ��� ������ ʧ�ܲ�ӵ���� �˳�ջ����������unique_lock����ʱ��������*/
			/*��������ɹ� �˳�ջ��������unique_lock����ʱ������*/
			if (lock.owns_lock() /*lock.operator bool()*/  /*lock*/ ) {
				cout << "owns_lock\n";
			}else {
				cout << "not owns_lock\n";
			}
		}
	}
	(void)getchar();

	/*2*/
	for (int i = 0; i < 3; i++){

		thread th(TestLockGuard, i + 1);
		th.detach();
	}
	(void)getchar();

	/*1*/
	TestMutex(1);
	TestMutex(2);
	(void)getchar();
	return 0;
}
