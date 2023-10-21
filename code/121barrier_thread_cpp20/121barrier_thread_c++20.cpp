#include <iostream>
#include <thread>
#include <barrier>

using namespace std;
using namespace this_thread;
using namespace chrono;

void TestBar(const int i,barrier<>* bar)
{
	sleep_for(seconds(i));
	cout << i << " begin wait \n";
	bar->wait(bar->arrive());
	/*�ڴ���-1 ,�����ȴ� , �ڴ�ֵΪ0����*/
	//bar->arrive_and_wait();
	cout << i << " end wait \n";
}

int main(int argc, char* argv[])
{
	constexpr int count{ 3 };

	barrier bar(count);

	for (int i{}; i < count; i++){
		thread th{ TestBar ,i,&bar };
		th.detach();
	}

	_CRT_UNUSED(getchar());
	return 0;
}

