#include "udp_client.h"

#include <iostream>
#include <cstring>
using namespace std;

int main(int argc, char *argv[])
{
	CUdpClient client;
	const char *p = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";

	if (client.udpClientInit((char *)"127.0.0.1", 898)) {
		cout << "udpclient init Ok!!" <<endl;
	}

	if (client.udpSend((char *)p, strlen(p))) {
		cout << "udpSend Ok!!!" <<endl;
	}

	return 0;
}
