#include "udp_client.h"
#include <cstring>

CUdpClient::CUdpClient()
	:m_sockfd(-1),
	 m_serverIp(""),
	 m_serverPort(0)
{
	memset(&m_sockAddr, 0, sizeof(struct sockaddr_in));
}

bool CUdpClient::Init(char *serverIp, int serverPort)
{
	in_addr_t in_addr = inet_addr(serverIp);
	if (in_addr == INADDR_NONE) {
		goto err;
	}
	if (serverIp <= 0) {
		goto err;
	}
	m_serverIp = string(serverIp);
	m_serverPort = serverPort;

	m_sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (m_sockfd < 0){
		goto err;
	}

	m_sockAddr.sin_family = AF_INET;
	m_sockAddr.sin_addr.s_addr = in_addr;
	m_sockAddr.sin_port = htons(m_serverPort);

	return true;
err:
	return false;
}

bool CUdpClient::Send(char * pBuf, int buf_len)
{
	int sendLen = sendto(m_sockfd, pBuf, buf_len, 0,
			     (const sockaddr*)&m_sockAddr, sizeof(struct sockaddr_in));
	if (sendLen != buf_len) {
		return false;
	}

	return true;
}

CUdpClient::~CUdpClient()
{
	if (m_sockfd != -1) {
		close(m_sockfd);
	}
}
