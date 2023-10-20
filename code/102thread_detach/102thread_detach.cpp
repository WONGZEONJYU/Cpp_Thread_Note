#include <iostream>
#include <thread>

//Linux -lpthread linux����Ҫ����-lpthread�߳̿�

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

    //���̴߳�������
    {
        //thread th(ThreadMain);/*����thread�������٣����̻߳�������*/
    }

    {
        /*��ʹ��detach()֮��th������Ҫ�ٹ���*/
        thread th(ThreadMain);
        th.detach();/*���߳������̷߳��룬���߳������߳��޹� == �ػ��߳�*/

        /*�ӣ����߳��˳������̲߳�һ���˳�*/

        /*
            ���߳��˳������̾ͻ�ȥ������غ���������Դ���գ�
            �����ʱ�����̷߳�����ȫ�ֱ���������ռ䣬������
            �ͻᷢ�ͳ����쳣����
        */
    }

    {
        /**/
         thread th(ThreadMain);
         sleep_for(chrono::seconds(1));/*1000ms = 1s*/
         is_exit = true;
         cout << "Wait for the child thread to exit\n";
         th.join();/*���߳��������ȴ����߳��˳�*/
         cout << "child thread is exit\n";
    }

    (void)getchar();

    return 0;
}

