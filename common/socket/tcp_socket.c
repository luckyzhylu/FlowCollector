#include "tcp_socket.h"
#include "vito_log.h"

#include <stdio.h>
#include <strings.h>
#include <unistd.h>
#include <assert.h>
#include <errno.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

static int tcp_connect_ext(u32 host_ip, ushort port);
static int tcp_reconnect(tcp_peer *peer);

int tcp_connect(tcp_peer *peer, u32 host_ip, ushort port)
{
	int fd;

	fd = tcp_connect_ext(host_ip, port);
	if (fd >= 0) {
		peer->server_ip = host_ip;
		peer->server_port = port;
		peer->fd = fd;

		tcp_set_option(peer);

		return 0;
	}

	return -1;
}

int tcp_connect_ext(u32 host_ip, ushort port)
{
	int ret;
	struct sockaddr_in server_addr;

	int tmp_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (tmp_fd < 0) {
		fatallog("New socket error.");
		goto err;
	}

	bzero(&server_addr, sizeof(struct sockaddr_in));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htonl(host_ip);
	server_addr.sin_port = htons(port);

	ret = connect(tmp_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));
	debuglog("connect to %s:%d %s, fd(%d).", inet_ntoa(server_addr.sin_addr), 
		 port,
		 ret == 0 ? "OK" : "FAIL",
		 tmp_fd);

	if (ret == 0) {
		return tmp_fd;
	}
err:
	if (tmp_fd >= 0) {
		close(tmp_fd);
	}
	return -1;
}

void tcp_set_option(tcp_peer *peer)
{
	struct linger lig;
	int tcp_buf_size = MAX_BUF_SIZE;
	struct timeval tval;

	lig.l_onoff = 1;
	lig.l_linger = 0;

	assert(peer);
	setsockopt(peer->fd, SOL_SOCKET, SO_LINGER, (int8_t *)&lig, sizeof(struct linger));
	setsockopt(peer->fd, SOL_SOCKET, SO_SNDBUF, (int8_t *)&tcp_buf_size, sizeof(tcp_buf_size));

	tval.tv_sec = 10;
	tval.tv_usec = 0;
	setsockopt(peer->fd, SOL_SOCKET, SO_SNDTIMEO, (void*)&tval, sizeof(tval));
}

int tcp_send(tcp_peer *peer, char *data, int data_len)
{
	int total_len = 0;
	int send_len;
	int len = 0;

	for (send_len = 0; send_len < data_len; send_len += len) {
		len = send(peer->fd, data + send_len, data_len - send_len, MSG_NOSIGNAL);
		if (len < 0) {
			if ((EAGAIN == errno) || (EINTR == errno)){
				fatallog("[COMM] send error. send again.");
				continue;
			}

			fatallog("Send data[%d/%d] error: send ret= %d.", send_len, data_len, len);
			tcp_reconnect(peer);
			goto err;
		}
		total_len += len;
	}

	if (total_len != data_len) {
		assert(0);
	}


	return total_len;
err:
	return -1;
}

int tcp_reconnect(tcp_peer *peer)
{
	tcp_close(peer);
	return tcp_connect(peer, peer->server_ip, peer->server_port);
}

void tcp_close(tcp_peer *peer)
{
	if (peer->fd >= 0) {
		close(peer->fd);
		peer->fd = -1;
	}
}
