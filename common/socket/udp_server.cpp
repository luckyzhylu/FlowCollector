#include "udp_server.h"

#include <iostream>
#include <cassert>

CUdpSocketServer::CUdpSocketServer()
	:m_pRecvBuf(NULL),
	 m_maxBufSize(0),
	 m_sockfd(-1),
	 m_listenPort(DEFAULT_PORT),
	 m_timeout(DEFAULT_TIMEOUT)
{
	m_listenedIp.clear();
	m_connectedFd.clear();
}

bool CUdpSocketServer::Init(int listenPort, int timeout)
{
	struct sockaddr_in addrin;
	struct timeval tv;
	struct sockaddr_in *paddr = (struct sockaddr_in *)&addrin;

	if (listenPort <= 0) {
		m_listenPort = DEFAULT_PORT;
	} else {
		m_listenPort = listenPort;
	}

	addrin.sin_family = AF_INET;
	addrin.sin_addr.s_addr = htonl(INADDR_ANY);
	addrin.sin_port = htons(m_listenPort);

	if ((m_sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
		goto err;
	}

	if (bind(m_sockfd, (struct sockaddr *)paddr, sizeof(struct sockaddr)) < 0) {
		close(m_sockfd);
		goto err;
	}

	if (timeout < 0) {
		m_timeout = DEFAULT_TIMEOUT;
	} else {
		m_timeout = timeout;
	}
	tv.tv_sec = m_timeout;
	tv.tv_usec = 0;

	setsockopt(m_sockfd, SOL_SOCKET, SO_RCVTIMEO, (void*)&tv, sizeof(tv));

	if (pthread_create(&m_tid, NULL, serverMain, this) < 0) {
		goto err;
	}
	// sleep(1);

	return true;
err:
	return false;
}

void CUdpSocketServer::addListenedIp(const string & rcsIpString)
{
	in_addr_t addr = inet_addr(rcsIpString.c_str());
	if (addr != INADDR_NONE) {
		m_listenedIp.push_back(addr);
	}
}

void CUdpSocketServer::processReceivedData(char *pBuf, int buf_size)
{
	cout << "Receive " << buf_size <<" bytes from " << m_srcIpstring << endl;
}

bool CUdpSocketServer::isValidFrom(struct sockaddr *addr)
{
	struct in_addr fromAddr;
	unsigned int clientIp;

	clientIp = ((struct sockaddr_in *)addr)->sin_addr.s_addr;
	for (size_t i = 0; i < m_listenedIp.size(); i++) {
		if (clientIp == m_listenedIp[i]) {
			return true;
		}
	}

	fromAddr.s_addr = clientIp;
	cout << "from invalid Ipstring:" << inet_ntoa(fromAddr) << endl;

	return false;
}
void CUdpSocketServer::receiverThread()
{
	char addrBuf[256];

	struct sockaddr *srcAddr = (struct sockaddr *)addrBuf;

	assert(m_pRecvBuf);
	assert(m_maxBufSize > 0);
	while (true) {
		socklen_t sockLen = sizeof(struct sockaddr);
		int len = recvfrom(m_sockfd, m_pRecvBuf, m_maxBufSize, 0, srcAddr, &sockLen);
		if (len <= 0) {
			usleep(1);
			continue;
		}

		/**
		 * 如果有指定的监听IP列表时，要判断发送端的IP是否在监听列表中
		 * 不再列表中的数据不处理
		 */
		if (m_listenedIp.size() == 0 || isValidFrom(srcAddr)) {
			processReceivedData(m_pRecvBuf, len);
		}
	}
}

void *CUdpSocketServer::serverMain(void *arg)
{
	pthread_detach(pthread_self());
	CUdpSocketServer *p = (CUdpSocketServer *)arg;
	assert(p);
	p->receiverThread();
	pthread_exit(NULL);
}

CUdpSocketServer::~CUdpSocketServer()
{
	if (m_sockfd != -1) {
		close(m_sockfd);
	}
	// m_bExitThread = false;
	m_connectedFd.clear();
	m_listenedIp.clear();
}
