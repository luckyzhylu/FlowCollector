#ifndef _CA_AUDIT_DATA_STRUCT_HEAD_
#define _CA_AUDIT_DATA_STRUCT_HEAD_
#include "comm_type.h"

#define     MAX_MAC_LEN            6     //MAC为6个字节

typedef  struct _audit_event{
    //u_int64_t    id;                     //事件id。
    int64_t    session_id;             //会话id。
    u_int64_t    generate_time;
    //u_int32_t    generate_ms_time;
    //int64_t	 generate_req_u_time;	//新增加请求方向微秒时间
    //int32_t      transport_protocol_id;  //TCP: 6; UDP: 17
    int32_t      protocol_id;            //应用协议ID
    //int32_t      level;
    //u_int32_t    engine_ip;
    //u_int32_t    server_ip;
    //u_int32_t    client_ip;
    //u_int16_t    server_port;
    //u_int16_t    redirect_port;          //重定向端口
    //u_int16_t    client_port; 
    //u_int8_t     server_mac[MAX_MAC_LEN];
    //u_int8_t     client_mac[MAX_MAC_LEN];
    int32_t      direction;              //0: request; 1: response
    //int32_t      response_time;          //响应时间，单位为微秒
    //int32_t      error_code;             //错误码.像Telnet等没有错误码的协议,错误码恒为0
    int32_t      bizaccount_len;
    int8_t       data[0];
}__attribute__ ((packed))audit_event;

typedef struct _audit_event_db{
    //int32_t      record_rows;         //记录集行数
    int32_t      sql_len;             //sql语句长度
    //int32_t      client_host_len;     //源主机名长度
    //int32_t      server_host_len;     //目的主机名长度
    //int32_t      library_len;         //连接方式。例如ODBC或JDBC
    //int32_t      client_software_len; //客户端软件名长度
    //int32_t      client_user_len;     //客户端操作系统用户名
    //int32_t      instance_name_len;   //实例名长度
    int32_t      db_name_len;         //数据库名长度
    int32_t      table_name_len;      //表名长度
    //int32_t      object_name_len;     //对象名长度
    int32_t      cmd;                 //命令
    int32_t      subcmd_len;          //子命令长度
    //int32_t      template_id;         //模板id
    //int32_t      template_len;        //SQL模板长度
    //int32_t      append_num;          //值对个数
    //int32_t	 response_num;
    //int32_t      reserved[3];         //保留字节
    int8_t     data[0];             //所有的长度值的指针
}__attribute__ ((packed))audit_event_db;

typedef struct _audit_event_db_append{
    int32_t      table_name_len;      //表名长度
    int32_t      cmd;                 //命令
    int32_t      subcmd_len;          //子命令长度
    int32_t      col_name_len;        //列名长度
    int32_t      col_value_len;       //列值长度
    int32_t	   col_comparison_len;	//比较符号长度
    int32_t      col_valuetype;       //列值类型
    int32_t      col_postype;         //列位置类型。0:主句; 1：子句
    int32_t      reserved[4];         //保留字节
    int8_t     data[0];             //所有的长度值的指针
}audit_event_db_append;

typedef struct _audit_event_db_response{
    int32_t	res_value_len;
    u_int8_t	data[0];
}audit_event_db_response;

typedef struct _audit_event_mail{
    int32_t      sender_len;          //发件人长度
    int32_t      recipients_len;      //接受人长度
    int32_t      subject_len;         //主题长度
    int32_t      content_len;         //正文长度
    int32_t      attachments_name_len;//附件名称长度, 当前支持5个附件, 5个名称合在一起
    int32_t      attachments_len;     //附件内容长度, 当前支持5个附件, 5个内容合在一起
    int32_t      reserved[4];         //保留字节
    int8_t     data[0];             //发件人, 收件人, 正文, 附件 附件内容数据指针, 数据连续存放
}audit_event_mail;

typedef struct _audit_event_http{
    int32_t      method_len;          //访问模式长度
    int32_t      url_len;             //url长度
    //int32_t      cookie_len;          //cookie长度
    //int32_t      host_len;            //host长度
    //int32_t      refer_len;           //refer长度
    int32_t      post_len;            //post数据长度. 只记录请求数据, 不记录页面数据
    int32_t      content_len;         //网页数据内容
    //int32_t      req_content_type_len;//请求包网页数据类型
    //int32_t      res_content_type_len;//响应包网页数据类型
    int8_t     data[0];             //访问模式. url,cookie,post数据指针, 数据连续存放
}__attribute__ ((packed))audit_event_http;

typedef struct _audit_event_http_append{
    int32_t      http_key_len;            
    int32_t      http_value_len; 
    int32_t    	reserved[4];
    int8_t    data[0];
}audit_event_http_append;

typedef struct _audit_event_file{
    int32_t      command;             //命令
    int32_t      type;                //0:文件; 1:目录
	int32_t 	 command_echo_len;
	int32_t      src_object_len;      //文件名/目录长度
    int32_t      dst_object_len;      //新文件名/目录长度
    int32_t      mount_point_len;     //sunrpc挂载点长度
    int32_t      local_path_len;	  //文件路径长度
    int32_t      reserved[4];         //保留字节
    int8_t     data[0];             //文件名, 目录名, 新文件名, sunrpc挂载点数据指针, 数据连续存放
}audit_event_file;


typedef struct _audit_event_cmdline{
    int32_t      input_cmd_len;       //输入数据命令长度
    int32_t         input_data_len;   //输入数据命令对象长度
    int32_t      reserved[4];         //保留字节
    int8_t     data[0];             //输入数据指针, 数据连续存放
}audit_event_cmdline;

typedef struct _audit_event_radius{
    u_int32_t    user_ip;                     //认证用户IP
    u_int32_t    nas_ip;                      //NAS服务器IP
    u_int8_t     user_mac[MAX_MAC_LEN];       //认证用户MAC
    u_int8_t     reserved_byte[8-MAX_MAC_LEN];//上面字段的Patch
    int32_t      nas_identifier_len;          //标识符长度，最大长度为256
    int32_t      acct_status_type;            //1表示上线,2表示下线,7开始计费,8结束计费。还有3保留，但被过滤掉，不上报审计事件
    int32_t      reserved[4];                 //保留字节
    int8_t     data[0];                     //输入数据指针, 数据连续存放
}audit_event_radius;

typedef struct _audit_event_rdp{
    int32_t      client_host_len;
    int32_t      server_host_len;
    int32_t      domain_len;
    int32_t      program_len;
    int32_t      directory_len;
    int32_t      input_data_len;
    int32_t      reserved[4];         //保留字节
    int8_t     data[0];             //输入数据指针, 数据连续存放
}audit_event_rdp;

typedef struct _audit_event_vnc{
    int32_t      input_data_len;
    int32_t      reserved[4];         //保留字节
    int8_t     data[0];             //输入数据指针, 数据连续存放
}audit_event_vnc;

typedef struct _audit_event_other{
    int32_t      data_len;
    int32_t      reserved[4];         //保留字节
    int8_t     data[0];             //输入数据指针, 数据连续存放
}audit_event_other;

typedef struct _session_info{
    u_int64_t    id;                  //事件id。生成规则见《天玥II6.0.8.2日志库表结构设计.doc》
    time_t       begin_time;
    time_t       end_time;
    u_int32_t    alive_time;          //存活时间
    int32_t      transport_protocol_id;
    int32_t      protocol_id;         //应用协议ID
    u_int32_t    engine_ip;
    u_int32_t    server_ip;
    u_int32_t    client_ip;
    u_int16_t    server_port;
    u_int16_t    redirect_port;       //重定向端口
    u_int16_t    client_port;
    u_int8_t     server_mac[MAX_MAC_LEN];
    u_int8_t     client_mac[MAX_MAC_LEN];
    u_int64_t    up_packets;
    u_int64_t    down_packets;
    u_int64_t    up_bits;
    u_int64_t    down_bits;
    u_int32_t     audit_event_count;  //会话上报事件数
    int32_t      policy_id;
    int32_t      direction;           //会话连接方向. 0: request; 1: response. 本版本都是正向.
    int32_t      have_data;
    int32_t      protocol_name_len;   //应用协议名称
    int32_t      bizaccount_len;
    int32_t	  auth_account_len;
    int32_t	  packet_count;
    int32_t	realtime_session_type;  //0:not display realtime_session;1:display realtime_session
    int32_t      reserved[2];         //保留字节
    int8_t     data[0];
}session_info;

typedef struct _session_data{
    time_t       generate_time;
    time_t	  start_time;
    u_int64_t    id;
    int32_t      protocol_id;
    int32_t      seq;
    int32_t      packet_count;        //会话数据内包含的数据包数
    int32_t      data_length;
    int32_t      readable_data_length;
    int32_t      reserved[2];         //保留字节
    int8_t     data[0];             //会话数据的指针
}session_data;

typedef struct _file_data{
    u_int64_t      event_id;             //事件id
    u_int64_t      session_id;           //会话id
    int32_t      protocol_id;          //文件协议id
    int32_t      filename_length;      //文件名长度
    int32_t      data_length;          //文件数据长度
    int32_t      reserved[4];          //保留字节
    int8_t     data[0];             //数据的指针
}file_data;

typedef struct _audit_ipmac{
    u_int64_t    id;                     //事件id。生成规则见《天玥II6.0.8.2日志库表结构设计.doc》
    u_int64_t    session_id;             //会话id。生成规则见《天玥II6.0.8.2日志库表结构设计.doc》
    time_t       generate_time;
    int32_t      transport_protocol_id;  //TCP: 6; UDP: 17
    int32_t      protocol_id;
    int32_t      level;
    u_int32_t    engine_ip;
    u_int32_t    server_ip;
    u_int32_t    client_ip;
    u_int16_t    server_port;
    u_int16_t    client_port;
    u_int8_t     server_mac[MAX_MAC_LEN];
    u_int8_t     client_mac[MAX_MAC_LEN];
    u_int8_t     policy_mac[MAX_MAC_LEN];//策略中配置的MAC
    u_int8_t     patch[2];
    u_int32_t    policy_ip;              //策略中配置的IP
    int32_t      policy_id;
    int32_t      direction;              //0: request; 1: response
    int32_t      block;
    int32_t      protocol_name_len;      //应用协议名称
    int32_t      reserved[4];            //保留字节
    int8_t       data[0];
} audit_ipmac;
typedef struct _audit_event_dns{
	int32_t query_or_response;				// 0:query	；1:response 
	int32_t operate_code;			// 查询的种类:0 标准查询(query)/1反向查询(iquery)/2服务器状态查询(staus)/3-15保留
	int32_t authority_answer;				// 权威回答 :针对response. 0:非权威1:权威
	int32_t response_code;			//响应代码.针对response.  0:没出错/1:格式错误/2:服务器故障/3:名称错误/4:服务器不支使/5:服务器拒绝/6:保留
	int32_t query_domain_name_len;		//用来从data中分解出query_domain_name
	int32_t response_domain_name_len;	//用来从data中分解出response_domain_name
	int32_t response_addr_ip_string_len;//用来从data中分解出response_addr_ip_string
	/*
	u_int8_t	query_domain_name[256]; 		//目前只解释一个query的情况(其中形式可为:68.224.98.202.in-addr.arpa/119.75.218.771/www.baidu.com.=都是字符串形式)
	u_int8_t	response_domain_name[256*3+8];	//域名，即别名==让多个域名放一起,"/"来分割//目前，只报最多3个域名的情况
	u_int8_t	response_addr_ip_string[64];	//dns 返回的answers的address中的各个ip(考虑同一个域名具有多个ip的情况)
	*/
	int8_t	data[0];				//疑问:dns不需要的话，这里要定义吗??

} audit_event_dns;
typedef struct _audit_event_ext {
	union {
		audit_event_http http_event;
		audit_event_cmdline cmdline_event;
		audit_event_file file_event;
		audit_event_mail mail_event;
		audit_event_db db_event;
		audit_event_vnc vnc_event;
		audit_event_rdp rdp_event;
		audit_event_radius radius_event;
		audit_event_dns dns_event;
		audit_event_other other_event;
	} ext;
} audit_event_ext;

#endif
