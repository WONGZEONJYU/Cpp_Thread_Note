#include <thread>
#include <iostream>
#include <future>
#include <string>

using namespace std;
using namespace chrono;
using namespace this_thread;

void TestFuture(promise<string> p)
{
    cout << "begin TestFuture\n";
    sleep_for(seconds(3));
    cout << "begin set value\n";
    p.set_value("TestFuture value\n");
    sleep_for(seconds(3));
    cout << "end TestFuture\n";
}

int main(int argc, char* argv[])
{
    promise<string> p;/*�첽��������洢*/

    auto future{ p.get_future() };/*������ȡ�߳��첽ֵ��ȡ*/

    thread th(TestFuture, move(p));

    cout << "begin future.get()\n" ;
    cout << "future get() = " << future.get();
    cout << "end future.get()\n";
    th.join();

    (void)getchar();
    return 0;
}
