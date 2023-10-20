#include <thread>
#include <iostream>
#include <string>

/*Linux -lpthread*/

using namespace std;
using namespace chrono;
using namespace this_thread;

class TestLambda
{
public:
	void Start() {
		thread th([this]() {
			cout << "name = " << name << "\n";
			});
		th.join();
	}
	string name{"test lambda"};
};

int main(int argc, char* argv[])
{
	thread th([](int i) {
		cout << __FUNCTION__ << i << "\n";
		},123);
	th.join();

	TestLambda test;
	test.Start();
	(void)getchar();
	return 0;
}

