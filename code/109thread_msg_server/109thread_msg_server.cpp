#include <iostream>
#include "xmsgserver.h"
#include <sstream>

using namespace std;

int main(int argc, char* argv[])
{
	XMsgServer server;
	server.Start();

	for (int i {}; i < 10; i++) {
		stringstream ss;
		ss << "msg : " << i + 1;
		server.SendMsg(ss.str());
		this_thread::sleep_for(chrono::milliseconds(500));
	}

	server.Stop();
	(void)getchar();
	return 0;
}
