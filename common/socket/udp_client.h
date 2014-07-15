#ifndef _UDP_CLIENT_H_
#define _UDP_CLIENT_H_

#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

using namespace std;


class CUdpClient
{
public:
	CUdpClient();
	bool Init(char *serverIp, int serverPort);
	bool Send(char *pBuf, int buf_len);
	virtual ~CUdpClient();
private:
	int m_sockfd;
	string m_serverIp;
	int m_serverPort;
	struct sockaddr_in m_sockAddr;
};


#endif /* _UDP_CLIENT_H_ */
