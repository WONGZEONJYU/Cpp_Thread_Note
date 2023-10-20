#include <iostream>
#include "xmsgserver.h"
#include <sstream>

using namespace std;
using namespace this_thread;

int main(int argc, char* argv[])
{
	XMsgServer server;
	server.Start();

	for (int i {}; i < 10; i++) {
		stringstream ss;
		ss << "msg : " << i + 1;
		server.SendMsg(ss.str());
		sleep_for(chrono::milliseconds(500));
	}

	server.Stop();
	cout << "Server stoped!\n";
	(void)getchar();
	return 0;
}
