#ifndef _TCP_SOCKET_H_
#define _TCP_SOCKET_H_

#include "comm_type.h"

typedef struct _tcp_peer {
	u32 server_ip;			// 服务器IP地址
	u32 server_port;		// 服务器开放端口
	int fd;			// 客户端打开的文件句柄
} tcp_peer;

#define MAX_BUF_SIZE 102400 // (100k)

/** 
 * 使用tcp连接服务器
 *
 * @param peer
 * @param host_ip 服务器IP地址(主机序)
 * @param port 服务器的开放端口
 * 
 * @return 成功返回tcp_peer结构,失败返回NULL
 */
int tcp_connect(tcp_peer *peer, u32 host_ip, ushort port);

/** 
 * 客户端设置发送数据的选项
 * 
 * @param peer 
 */
void tcp_set_option(tcp_peer *peer);


/** 
 * 发送数据
 * 
 * @param peer 
 * @param data 数据头指针
 * @param data_len 数据长度
 * 
 * @return 成功返回发送数据的长度,失败返回-1
 */
int tcp_send(tcp_peer *peer, char *data, int data_len);

/** 
 * 客户端关闭tcp连接
 * 
 * @param peer 
 */
void tcp_close(tcp_peer *peer);


#endif /* _TCP_SOCKET_H_ */
