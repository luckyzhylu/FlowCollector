#ifndef _UDP_SERVER_H_
#define _UDP_SERVER_H_


#include <vector>
#include <map>
#include <string>
#include <cassert>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

using namespace std;


class CUdpSocketServer
{
public:
#define DEFAULT_PORT 1405
#define DEFAULT_TIMEOUT 5
public:
	CUdpSocketServer();
	bool Init(int listenPort = DEFAULT_PORT, int timeout = DEFAULT_TIMEOUT);
	void addListenedIp(const string& rcsIpString);

	void setRecvBufPointer(char *pBuf) {
		assert((m_pRecvBuf = pBuf) != NULL);
	}
	void setRecvBufSize(int max_bufsize) {
		assert((m_maxBufSize = max_bufsize) > 0);
	}
	virtual void processReceivedData(char *pData, int len);
	virtual ~CUdpSocketServer();
private:
	static void *serverMain(void *);
	void receiverThread();
	bool isValidFrom(struct sockaddr *addr);
private:
	pthread_t m_tid;
	char *m_pRecvBuf;		// 接收数据缓存的地址
	int m_maxBufSize;		// 接收数据缓存的大小
	int m_sockfd;			   // 监听着的句柄
	string m_srcIpstring;		   // 接收数据的源IP
	int m_listenPort;		   // 监听的端口
	int m_timeout;			   // 监听的超时
	vector<unsigned int> m_listenedIp; // 要监听的IP列表
	map<int, unsigned int> m_connectedFd; // 已经建立连接的句柄
};

#endif /* _UDP_SERVER_H_ */
