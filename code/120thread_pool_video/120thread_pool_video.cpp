#include <iostream>
#include <thread>
#include "xthread_pool.h"
#include "xvideo_task.h"

using namespace std;
using namespace chrono;
using namespace this_thread;

/*命令行视频转码工具*/
/*ffmpeg工具*/
/*用户输入 视频源 输出视频尺寸*/
/*在线程池中执行转码任务*/
/*转码任务调用ffmpeg*/
/*	ffmpeg -y -i test.mp4 -s 400x300 400.mp4 >log.txt 2>&1	*/

int main(int argc, char* argv[])
{
	XThreadPool pool;
	pool.Init(thread::hardware_concurrency());
	pool.Start();
	sleep_for(milliseconds(200));

	for (;;){

		sleep_for(milliseconds(200));
		cout << "\n=======================================================\n";
		auto task{ make_shared<XVideoTask>() };
		cout << "Please enter the command(v , e , l) :\n";
		string cmd;
		cin >> cmd;
		if ("e" == cmd){
			break;
		}
		else if ("l" == cmd) {
			cout << "task run count = " << pool.task_run_count() << '\n';
			continue;
		}

		cout << "video source :\n";
		cin >> task->in_path;
		cout << "video target :\n";
		cin >> task->out_path;
		cout << "output width :\n";
		cin >> task->width;
		cout << "output height :\n";
		cin >> task->height;
		pool.AddTask(task);
	}

#if 0
	auto vtask1{ make_shared<XVideoTask>() };
	vtask1->in_path = "test.mp4";
	vtask1->out_path = "640.mp4";
	vtask1->width = 640;
	vtask1->height = 480;
	pool.AddTask(vtask1);
	auto re{ vtask1->GetReturn() };
	std::cout << "vtask1->GetReturn() = " << re << "\n";
	cout << "end\n";
#endif
	_CRT_UNUSED(getchar());
	return 0;
}

