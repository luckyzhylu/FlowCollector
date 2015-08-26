#ifndef _CA_AUDIT_DATA_STRUCT_HEAD_
#define _CA_AUDIT_DATA_STRUCT_HEAD_
#include "comm_type.h"

#define     MAX_MAC_LEN            6     //MACΪ6���ֽ�

typedef  struct _audit_event{
    //u_int64_t    id;                     //�¼�id��
    int64_t    session_id;             //�Ựid��
    u_int64_t    generate_time;
    //u_int32_t    generate_ms_time;
    //int64_t	 generate_req_u_time;	//������������΢��ʱ��
    //int32_t      transport_protocol_id;  //TCP: 6; UDP: 17
    int32_t      protocol_id;            //Ӧ��Э��ID
    //int32_t      level;
    //u_int32_t    engine_ip;
    //u_int32_t    server_ip;
    //u_int32_t    client_ip;
    //u_int16_t    server_port;
    //u_int16_t    redirect_port;          //�ض���˿�
    //u_int16_t    client_port; 
    //u_int8_t     server_mac[MAX_MAC_LEN];
    //u_int8_t     client_mac[MAX_MAC_LEN];
    int32_t      direction;              //0: request; 1: response
    //int32_t      response_time;          //��Ӧʱ�䣬��λΪ΢��
    //int32_t      error_code;             //������.��Telnet��û�д������Э��,�������Ϊ0
    int32_t      bizaccount_len;
    int8_t       data[0];
}__attribute__ ((packed))audit_event;

typedef struct _audit_event_db{
    //int32_t      record_rows;         //��¼������
    int32_t      sql_len;             //sql��䳤��
    //int32_t      client_host_len;     //Դ����������
    //int32_t      server_host_len;     //Ŀ������������
    //int32_t      library_len;         //���ӷ�ʽ������ODBC��JDBC
    //int32_t      client_software_len; //�ͻ������������
    //int32_t      client_user_len;     //�ͻ��˲���ϵͳ�û���
    //int32_t      instance_name_len;   //ʵ��������
    int32_t      db_name_len;         //���ݿ�������
    int32_t      table_name_len;      //��������
    //int32_t      object_name_len;     //����������
    int32_t      cmd;                 //����
    int32_t      subcmd_len;          //�������
    //int32_t      template_id;         //ģ��id
    //int32_t      template_len;        //SQLģ�峤��
    //int32_t      append_num;          //ֵ�Ը���
    //int32_t	 response_num;
    //int32_t      reserved[3];         //�����ֽ�
    int8_t     data[0];             //���еĳ���ֵ��ָ��
}__attribute__ ((packed))audit_event_db;

typedef struct _audit_event_db_append{
    int32_t      table_name_len;      //��������
    int32_t      cmd;                 //����
    int32_t      subcmd_len;          //�������
    int32_t      col_name_len;        //��������
    int32_t      col_value_len;       //��ֵ����
    int32_t	   col_comparison_len;	//�ȽϷ��ų���
    int32_t      col_valuetype;       //��ֵ����
    int32_t      col_postype;         //��λ�����͡�0:����; 1���Ӿ�
    int32_t      reserved[4];         //�����ֽ�
    int8_t     data[0];             //���еĳ���ֵ��ָ��
}audit_event_db_append;

typedef struct _audit_event_db_response{
    int32_t	res_value_len;
    u_int8_t	data[0];
}audit_event_db_response;

typedef struct _audit_event_mail{
    int32_t      sender_len;          //�����˳���
    int32_t      recipients_len;      //�����˳���
    int32_t      subject_len;         //���ⳤ��
    int32_t      content_len;         //���ĳ���
    int32_t      attachments_name_len;//�������Ƴ���, ��ǰ֧��5������, 5�����ƺ���һ��
    int32_t      attachments_len;     //�������ݳ���, ��ǰ֧��5������, 5�����ݺ���һ��
    int32_t      reserved[4];         //�����ֽ�
    int8_t     data[0];             //������, �ռ���, ����, ���� ������������ָ��, �����������
}audit_event_mail;

typedef struct _audit_event_http{
    int32_t      method_len;          //����ģʽ����
    int32_t      url_len;             //url����
    //int32_t      cookie_len;          //cookie����
    //int32_t      host_len;            //host����
    //int32_t      refer_len;           //refer����
    int32_t      post_len;            //post���ݳ���. ֻ��¼��������, ����¼ҳ������
    int32_t      content_len;         //��ҳ��������
    //int32_t      req_content_type_len;//�������ҳ��������
    //int32_t      res_content_type_len;//��Ӧ����ҳ��������
    int8_t     data[0];             //����ģʽ. url,cookie,post����ָ��, �����������
}__attribute__ ((packed))audit_event_http;

typedef struct _audit_event_http_append{
    int32_t      http_key_len;            
    int32_t      http_value_len; 
    int32_t    	reserved[4];
    int8_t    data[0];
}audit_event_http_append;

typedef struct _audit_event_file{
    int32_t      command;             //����
    int32_t      type;                //0:�ļ�; 1:Ŀ¼
	int32_t 	 command_echo_len;
	int32_t      src_object_len;      //�ļ���/Ŀ¼����
    int32_t      dst_object_len;      //���ļ���/Ŀ¼����
    int32_t      mount_point_len;     //sunrpc���ص㳤��
    int32_t      local_path_len;	  //�ļ�·������
    int32_t      reserved[4];         //�����ֽ�
    int8_t     data[0];             //�ļ���, Ŀ¼��, ���ļ���, sunrpc���ص�����ָ��, �����������
}audit_event_file;


typedef struct _audit_event_cmdline{
    int32_t      input_cmd_len;       //�������������
    int32_t         input_data_len;   //��������������󳤶�
    int32_t      reserved[4];         //�����ֽ�
    int8_t     data[0];             //��������ָ��, �����������
}audit_event_cmdline;

typedef struct _audit_event_radius{
    u_int32_t    user_ip;                     //��֤�û�IP
    u_int32_t    nas_ip;                      //NAS������IP
    u_int8_t     user_mac[MAX_MAC_LEN];       //��֤�û�MAC
    u_int8_t     reserved_byte[8-MAX_MAC_LEN];//�����ֶε�Patch
    int32_t      nas_identifier_len;          //��ʶ�����ȣ���󳤶�Ϊ256
    int32_t      acct_status_type;            //1��ʾ����,2��ʾ����,7��ʼ�Ʒ�,8�����Ʒѡ�����3�������������˵������ϱ�����¼�
    int32_t      reserved[4];                 //�����ֽ�
    int8_t     data[0];                     //��������ָ��, �����������
}audit_event_radius;

typedef struct _audit_event_rdp{
    int32_t      client_host_len;
    int32_t      server_host_len;
    int32_t      domain_len;
    int32_t      program_len;
    int32_t      directory_len;
    int32_t      input_data_len;
    int32_t      reserved[4];         //�����ֽ�
    int8_t     data[0];             //��������ָ��, �����������
}audit_event_rdp;

typedef struct _audit_event_vnc{
    int32_t      input_data_len;
    int32_t      reserved[4];         //�����ֽ�
    int8_t     data[0];             //��������ָ��, �����������
}audit_event_vnc;

typedef struct _audit_event_other{
    int32_t      data_len;
    int32_t      reserved[4];         //�����ֽ�
    int8_t     data[0];             //��������ָ��, �����������
}audit_event_other;

typedef struct _session_info{
    u_int64_t    id;                  //�¼�id�����ɹ��������hII6.0.8.2��־���ṹ���.doc��
    time_t       begin_time;
    time_t       end_time;
    u_int32_t    alive_time;          //���ʱ��
    int32_t      transport_protocol_id;
    int32_t      protocol_id;         //Ӧ��Э��ID
    u_int32_t    engine_ip;
    u_int32_t    server_ip;
    u_int32_t    client_ip;
    u_int16_t    server_port;
    u_int16_t    redirect_port;       //�ض���˿�
    u_int16_t    client_port;
    u_int8_t     server_mac[MAX_MAC_LEN];
    u_int8_t     client_mac[MAX_MAC_LEN];
    u_int64_t    up_packets;
    u_int64_t    down_packets;
    u_int64_t    up_bits;
    u_int64_t    down_bits;
    u_int32_t     audit_event_count;  //�Ự�ϱ��¼���
    int32_t      policy_id;
    int32_t      direction;           //�Ự���ӷ���. 0: request; 1: response. ���汾��������.
    int32_t      have_data;
    int32_t      protocol_name_len;   //Ӧ��Э������
    int32_t      bizaccount_len;
    int32_t	  auth_account_len;
    int32_t	  packet_count;
    int32_t	realtime_session_type;  //0:not display realtime_session;1:display realtime_session
    int32_t      reserved[2];         //�����ֽ�
    int8_t     data[0];
}session_info;

typedef struct _session_data{
    time_t       generate_time;
    time_t	  start_time;
    u_int64_t    id;
    int32_t      protocol_id;
    int32_t      seq;
    int32_t      packet_count;        //�Ự�����ڰ��������ݰ���
    int32_t      data_length;
    int32_t      readable_data_length;
    int32_t      reserved[2];         //�����ֽ�
    int8_t     data[0];             //�Ự���ݵ�ָ��
}session_data;

typedef struct _file_data{
    u_int64_t      event_id;             //�¼�id
    u_int64_t      session_id;           //�Ựid
    int32_t      protocol_id;          //�ļ�Э��id
    int32_t      filename_length;      //�ļ�������
    int32_t      data_length;          //�ļ����ݳ���
    int32_t      reserved[4];          //�����ֽ�
    int8_t     data[0];             //���ݵ�ָ��
}file_data;

typedef struct _audit_ipmac{
    u_int64_t    id;                     //�¼�id�����ɹ��������hII6.0.8.2��־���ṹ���.doc��
    u_int64_t    session_id;             //�Ựid�����ɹ��������hII6.0.8.2��־���ṹ���.doc��
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
    u_int8_t     policy_mac[MAX_MAC_LEN];//���������õ�MAC
    u_int8_t     patch[2];
    u_int32_t    policy_ip;              //���������õ�IP
    int32_t      policy_id;
    int32_t      direction;              //0: request; 1: response
    int32_t      block;
    int32_t      protocol_name_len;      //Ӧ��Э������
    int32_t      reserved[4];            //�����ֽ�
    int8_t       data[0];
} audit_ipmac;
typedef struct _audit_event_dns{
	int32_t query_or_response;				// 0:query	��1:response 
	int32_t operate_code;			// ��ѯ������:0 ��׼��ѯ(query)/1�����ѯ(iquery)/2������״̬��ѯ(staus)/3-15����
	int32_t authority_answer;				// Ȩ���ش� :���response. 0:��Ȩ��1:Ȩ��
	int32_t response_code;			//��Ӧ����.���response.  0:û����/1:��ʽ����/2:����������/3:���ƴ���/4:��������֧ʹ/5:�������ܾ�/6:����
	int32_t query_domain_name_len;		//������data�зֽ��query_domain_name
	int32_t response_domain_name_len;	//������data�зֽ��response_domain_name
	int32_t response_addr_ip_string_len;//������data�зֽ��response_addr_ip_string
	/*
	u_int8_t	query_domain_name[256]; 		//Ŀǰֻ����һ��query�����(������ʽ��Ϊ:68.224.98.202.in-addr.arpa/119.75.218.771/www.baidu.com.=�����ַ�����ʽ)
	u_int8_t	response_domain_name[256*3+8];	//������������==�ö��������һ��,"/"���ָ�//Ŀǰ��ֻ�����3�����������
	u_int8_t	response_addr_ip_string[64];	//dns ���ص�answers��address�еĸ���ip(����ͬһ���������ж��ip�����)
	*/
	int8_t	data[0];				//����:dns����Ҫ�Ļ�������Ҫ������??

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
