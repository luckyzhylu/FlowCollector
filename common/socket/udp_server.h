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
	char *m_pRecvBuf;		// �������ݻ���ĵ�ַ
	int m_maxBufSize;		// �������ݻ���Ĵ�С
	int m_sockfd;			   // �����ŵľ��
	string m_srcIpstring;		   // �������ݵ�ԴIP
	int m_listenPort;		   // �����Ķ˿�
	int m_timeout;			   // �����ĳ�ʱ
	vector<unsigned int> m_listenedIp; // Ҫ������IP�б�
	map<int, unsigned int> m_connectedFd; // �Ѿ��������ӵľ��
};

#endif /* _UDP_SERVER_H_ */
