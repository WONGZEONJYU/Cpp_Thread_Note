#include "xvideo_task.h"
#include <sstream>

using namespace std;
using namespace this_thread;

int XVideoTask::Run() 
{
	/*	ffmpeg.exe -y -i test.mp4 -s 640x480 600.mp4 >log.txt 2>&1*/
	stringstream ss;

	ss << "ffmpeg.exe -y -i " << in_path << " ";

	if ((width > 0) && (height > 0)){
		ss << " -s " << width << "x" << height << " ";
	}
	
	ss << out_path;
	ss << " >" << get_id() << ".txt 2>&1";
	cout << ss.str().c_str() << '\n';
	return system(ss.str().c_str());
}
