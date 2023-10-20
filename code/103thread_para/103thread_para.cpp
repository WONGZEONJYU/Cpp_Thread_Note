#include <thread>
#include <iostream>
#include <string>

using namespace std;
using namespace this_thread;
using namespace chrono;

class Para
{
public:
	Para() { cout << "Create Para\n"; }
	Para(const Para& obj) { cout << "Copy Para\n"; this->name = obj.name; }
	~Para() { cout << "Drop Para\n"; }
	string name;
};

void ThreadMain(int p1, float p2, string str, Para p4)
{
	sleep_for(chrono::milliseconds(100));//��ʱ100ms
	cout << "id: " << get_id() << "\n";
	cout << "ThreadMain parameter:" << p1 << " " << p2 << " " << str << " " << p4.name << "\n";
}

void ThreadMainPtr(Para *p)
{
	sleep_for(chrono::milliseconds(100));//��ʱ100ms
	cout << __FUNCTION__ << " name = " << p->name << "\n";
}

void ThreadMainRef(const Para& p /*Para& p*/)
{
	sleep_for(chrono::milliseconds(100));//��ʱ100ms
	cout << __FUNCTION__ << " name = " << p.name << "\n";
}

int main(int argc,char* argv[])
{
	{
		/*��������*/
		Para p;
		p.name = "test ThreadMainRef name";
		thread th(ThreadMainRef, cref(p));
		//thread th(ThreadMainRef, ref(p));
		th.join();
	}
	(void)getchar();

	{
		/*�����߳�ָ��*/
		Para p;
		p.name = "test ThreadMainPtr name";
		thread th(ThreadMainPtr, &p);
		th.detach();
		/*�����̷߳��ʵ�p�ռ����ǰ�ͷ�*/
		/*
			����취������Ψһ��Ҳһ������ã�:
			 1.���ɾ�̬�ֲ�������ȫ������
			 2.���ݶѿռ�
			 3.���̶߳���ͷ��ʵı�������һ�������棬��������������ͬ
			 4.����
		*/
	}
	/*Para �Ѿ��ͷ���*/
	(void)getchar();

	{
		/*�����߳�ָ��*/
		Para p;
		p.name = "test ThreadMainPtr name";
		thread th(ThreadMainPtr, &p);
		th.join();
	}

	(void)getchar();
	thread th;
	{
		float f1{ 12.1f };
		Para p;
		p.name = "test Para class";
		/*���еĲ���������*/
		th = thread(ThreadMain, 101, f1, "test string para",p);
	}
	th.join();
	(void)getchar();
	return 0;
}
