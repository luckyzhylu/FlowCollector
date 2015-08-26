#ifndef _TCP_SOCKET_H_
#define _TCP_SOCKET_H_

#include "comm_type.h"

typedef struct _tcp_peer {
	u32 server_ip;			// ������IP��ַ
	u32 server_port;		// ���������Ŷ˿�
	int fd;			// �ͻ��˴򿪵��ļ����
} tcp_peer;

#define MAX_BUF_SIZE 102400 // (100k)

/** 
 * ʹ��tcp���ӷ�����
 *
 * @param peer
 * @param host_ip ������IP��ַ(������)
 * @param port �������Ŀ��Ŷ˿�
 * 
 * @return �ɹ�����tcp_peer�ṹ,ʧ�ܷ���NULL
 */
int tcp_connect(tcp_peer *peer, u32 host_ip, ushort port);

/** 
 * �ͻ������÷������ݵ�ѡ��
 * 
 * @param peer 
 */
void tcp_set_option(tcp_peer *peer);


/** 
 * ��������
 * 
 * @param peer 
 * @param data ����ͷָ��
 * @param data_len ���ݳ���
 * 
 * @return �ɹ����ط������ݵĳ���,ʧ�ܷ���-1
 */
int tcp_send(tcp_peer *peer, char *data, int data_len);

/** 
 * �ͻ��˹ر�tcp����
 * 
 * @param peer 
 */
void tcp_close(tcp_peer *peer);


#endif /* _TCP_SOCKET_H_ */
