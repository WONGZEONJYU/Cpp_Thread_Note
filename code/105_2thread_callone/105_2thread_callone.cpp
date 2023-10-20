#include <thread>
#include <iostream>
#include <mutex>

using namespace std;
using namespace chrono;
using namespace this_thread;

void SystemInit()
{
	cout << "Call " << __FUNCTION__ << "\n";
}

void SystemInitOne()
{
	static std::once_flag flag;
	std::call_once(flag, SystemInit);
}

int main(int argc, char* argv[])
{
	SystemInitOne();
	SystemInitOne();

	for (int i{}; i < 3; i++){
		thread th(SystemInitOne);
		th.detach();
	}

	(void)getchar();

	return 0;
}
