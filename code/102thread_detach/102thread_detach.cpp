#include <iostream>
#include <thread>

//Linux -lpthread linux下需要加入-lpthread线程库

using namespace std;
using namespace chrono;
using namespace this_thread;

bool is_exit{};

void ThreadMain()
{
    cout << "begin sub thread main " << this_thread::get_id() << "\n";

    for (int i{}; i < 10; i++) {

        if (is_exit){
            break;
        }
        cout << "id : " << this_thread::get_id() << " in thread :" << i << "\n";
        sleep_for(chrono::seconds(1));/*1000ms = 1s*/
        //sleep_for(1s);/*1000ms = 1s*/
    }

    cout << "end sub thread main " << this_thread::get_id() << "\n";
}

int main(int argc, char* argv[])
{
    cout << "main thread ID " << this_thread::get_id() << "\n";

    //子线程创建启动
    {
        //thread th(ThreadMain);/*出错，thread对象被销毁，子线程还在运行*/
    }

    {
        /*在使用detach()之后，th对象不需要再管理*/
        thread th(ThreadMain);
        th.detach();/*子线程与主线程分离，子线程与主线程无关 == 守护线程*/

        /*坑：主线程退出后，子线程不一定退出*/

        /*
            主线程退出，进程就会去调用相关函数进行资源回收，
            如果此时，子线程访问了全局变量，共享空间，堆区等
            就会发送程序异常崩溃
        */
    }

    {
        /**/
         thread th(ThreadMain);
         sleep_for(chrono::seconds(1));/*1000ms = 1s*/
         is_exit = true;
         cout << "Wait for the child thread to exit\n";
         th.join();/*主线程阻塞，等待子线程退出*/
         cout << "child thread is exit\n";
    }

    (void)getchar();

    return 0;
}

