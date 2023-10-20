#include <iostream>
#include <thread>

//Linux -lpthread linux下需要加入-lpthread线程库

using namespace std;
using namespace chrono;
using namespace this_thread;

void ThreadMain()
{
    cout << "begin sub thread main "<< this_thread::get_id() << "\n";

    for (int i{}; i < 10; i++) {
        cout << "in thread :" << i << "\n";
        this_thread::sleep_for(chrono::seconds(1));/*1000ms = 1s*/
        //this_thread::sleep_for(1s);/*1000ms = 1s*/
    }

    cout << "end sub thread main " << this_thread::get_id() << "\n";
}

int main(int argc,char* argv[])
{
    cout << "main thread ID " << this_thread::get_id() << "\n";
    //线程创建启动
    thread th(ThreadMain);

    cout << "begin wait sub thread "  << "\n";
    th.join(); /*阻塞，等待子线程退出*/
    cout << "end wait sub thread " << "\n";
    return 0;
}

