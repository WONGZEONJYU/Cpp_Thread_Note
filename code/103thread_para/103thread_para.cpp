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
	sleep_for(chrono::milliseconds(100));//延时100ms
	cout << "id: " << get_id() << "\n";
	cout << "ThreadMain parameter:" << p1 << " " << p2 << " " << str << " " << p4.name << "\n";
}

void ThreadMainPtr(Para *p)
{
	sleep_for(chrono::milliseconds(100));//延时100ms
	cout << __FUNCTION__ << " name = " << p->name << "\n";
}

void ThreadMainRef(const Para& p /*Para& p*/)
{
	sleep_for(chrono::milliseconds(100));//延时100ms
	cout << __FUNCTION__ << " name = " << p.name << "\n";
}

int main(int argc,char* argv[])
{
	{
		/*传递引用*/
		Para p;
		p.name = "test ThreadMainRef name";
		thread th(ThreadMainRef, cref(p));
		//thread th(ThreadMainRef, ref(p));
		th.join();
	}
	(void)getchar();

	{
		/*传递线程指针*/
		Para p;
		p.name = "test ThreadMainPtr name";
		thread th(ThreadMainPtr, &p);
		th.detach();
		/*错误，线程访问的p空间会提前释放*/
		/*
			避免办法（不是唯一，也一定是最好）:
			 1.做成静态局部变量或全部变量
			 2.传递堆空间
			 3.把线程对象和访问的变量放在一个类下面，让其生命周期相同
			 4.上锁
		*/
	}
	/*Para 已经释放了*/
	(void)getchar();

	{
		/*传递线程指针*/
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
		/*所有的参数做复制*/
		th = thread(ThreadMain, 101, f1, "test string para",p);
	}
	th.join();
	(void)getchar();
	return 0;
}
