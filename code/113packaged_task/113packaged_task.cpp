#include <iostream>
#include <thread>
#include <future>
#include <string>

using namespace std;
using namespace chrono;
using namespace this_thread;

string TestPack(const int index)
{
	cout << "begin " << __FUNCTION__ << " " << index << "\n";
	sleep_for(seconds(2));
	string r {__FUNCTION__};
	r += " return\n";
	return r;
}

int main(int argc, char* argv[])
{
	packaged_task<string(const int)> task(TestPack);
	auto result { task.get_future() };
	//task(100);
	thread th(move(task), 101);

	//cout << "begin result get\n";
	//cout << "result get = " << result.get();

	for (int i {}; i < 30; i++) { /*²âÊÔ³¬Ê±*/
		if (result.wait_for(milliseconds(100)) != future_status::ready) {
			continue;
		}
	}

	if (result.wait_for(milliseconds(100)) == future_status::timeout) {
		cout << "wait result timeout\n";
	}
	else {
		cout << "begin result get\n";
		cout << "result get = " << result.get();
	}

	th.join();
	(void)getchar();
	return 0;
}

