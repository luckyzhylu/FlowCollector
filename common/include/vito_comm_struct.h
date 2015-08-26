#ifndef _VITO_COMM_STRUCT_H_
#define _VITO_COMM_STRUCT_H_

#include <sys/types.h>

#if 0
typedef unsigned char u_int8_t;
typedef unsigned short int u_int16_t;
typedef unsigned int u_int32_t;
typedef unsigned long long int u_int64_t;

typedef long long int int64_t;
typedef int int32_t;
typedef short int int16_t;
typedef char int8_t;
#endif

#define NETFLOW_MAGIC 0x1122aabb
#define NETFLOW_HEAD_VALID(head) (head->magic == NETFLOW_MAGIC ? 1 : 0)
typedef struct _netflow_head {
	int32_t magic;
	u_int32_t engine_ip;
	int32_t id;			//传输id
	int32_t num;			//事件条数
	int32_t data_length;		//data数据长度
	int32_t type;			//0：netflow_base_t;1: netflow_monitor_event
	int32_t reserved[3];		//保留字节
	int8_t data[0];		//数据内容
} netflow_head;

enum NetflowType {
	WHITE_EVENT = 0,
	BLACK_EVNET = 1,
	GRAY_EVENT = 2,
	UNDEFINED_EVENT = 3
};

enum CommEventType {
	NETFLOWEVENT = 0,
	FLOWMONITOREVENT = 1,
	NEWDEVICE,
	NEWINTERCONNECTION,
	DEVICEOPENEDPORT,
	FLOWSTAT,
	MAXCOMMEVENTTYPE
};

typedef struct _netflow_base_t {
	int64_t session_id;
	u_int32_t src_ip;
	u_int32_t dst_ip;
	u_int16_t src_port;
	u_int16_t dst_port;
	int32_t   transport_protocol;
	time_t start_time;
	time_t end_time;
	int32_t high_proto_id;
	u_int64_t up_package_count;
	u_int64_t up_byte_count;
	u_int64_t down_package_count;
	u_int64_t down_byte_count;
	int32_t level;
	int32_t record_cap;
	int64_t list_of_id;//黑白名单id
	int32_t audit_event_count;
	int64_t src_dev_id;
	int64_t src_domain_id;
	int64_t dst_dev_id;
	int64_t dst_domain_id;
} netflow_base_t;

typedef struct _netflow_monitor_event {
	int64_t device_id;
	int64_t domain_id;
	int64_t service_id;
	u_int64_t tcp_byte_count;
	u_int64_t udp_byte_count;
	u_int64_t tcp_packets_count;
	u_int64_t udp_packets_count;
} netflow_monitor_event;


#endif /* _VITO_COMM_STRUCT_H_ */
