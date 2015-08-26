#include <stdio.h>
#include <string.h>
#include "proto.h"

static int global_init_flag = 0;
static char global_grp_id[PROTO_NUM];

const char *proto_names[] = {
	"NULL",			//0
        "ETHER",
        "ARP",
        "IP",
        "UDP",
        "TCP",			//5
        "ICMP",
        "IGMP",
        "EGP",
        "HTTP",
        "TELNET",		//10
        "FTP",
        "SUNRPC",
        "DNS",
        "WHOIS",
        "SMTP",			//15
        "POP3",
        "NETBIOS-NS",
        "NETBIOS-SSN",
        "NETBIOS-DGM",
        "NNTP",			//20
        "IRC",
        "NFS",
        "PMAP",
        "AUTH",
        "CHARGEN",		//25
        "SNMP",
        "RIP",
        "IMAP",
        "TFTP",
        "MSRPC",		//30
        "FINGER",
        "RLOGIN",
        "NTALK",
        "ECHO",
        "TDS",			//35
        "TNS",
        "MSPROXY",
        "PCT",
        "DB2",
        "INFORMIX",		//40
	"X11",
	"XDMCP",
        "RDP",
        "UNKNOWN",
        "DAS",			//45
        "RADIUS",
        "PCNFSD",
        "MYSQL",
        "POSTGRESQL",
	"TERADATA",		//50
	"CACHE",
	"KINGBASE",		//52
	"DM",
	"SSH",
	"SCP",
	"SFTP",
	"SYBASE",
	"GBASE",
	"VNC",			//59
	"HTTPS",
	"SHENTONG",
	"IEC104",
	NULL
};

void proto_id2name(unsigned char id, char *name, int len)
{
	if (id < PROTO_ID_BORDER) {
		strncpy(name, proto_names[id], strlen(proto_names[id]));
	} else {
		strncpy(name, "UNKNOWN", 7);
	}

}

unsigned char proto_name2id(char *name)
{
	unsigned char id = 0;

	for (id = 0; id < PROTO_ID_BORDER; id++) {
		if (!strcasecmp(name, proto_names[id])) {
			break;
		}
	}

	return id;
}

void proto_grp_init()
{
/*
|-----------------------+----------------+---------------------+----------------------------------------------|
| proto_id              | group_id       | event struct        |		 table name                   |
|-----------------------+----------------+---------------------+----------------------------------------------|
| PROTO_ID_DB2		|		 | 		       |ca_log_audit_event_DB2_YYYYmmdd 	      | 
|			|		 |		       |ca_log_audit_event_DB2_append_YYYYmmdd        |
| PROTO_ID_DAS          |                |                     |ca_log_audit_event_DAS_YYYYmmdd               |
| 		        |                |                     |ca_log_audit_event_DAS_append_YYYYmmdd        |
| PROTO_ID_TNS          |                |                     |ca_log_audit_event_TNS_YYYYmmdd               |
|   		        |                |                     |ca_log_audit_event_TNS_append_YYYYmmdd        |
| PROTO_ID_TDS          |                |                     |ca_log_audit_event_TDS_YYYYmmdd               |
| 		        |                |                     |ca_log_audit_event_TDS_append_YYYYmmdd        |
| PROTO_ID_MYSQL        |                |                     |ca_log_audit_event_MYSQL_YYYYmmdd             |
| 		        |                |                     |ca_log_audit_event_MYSQL_append_YYYYmmdd      |
| PROTO_ID_POSTGRESQL   | GRP_ID_DB      | audit_event_db      |ca_log_audit_event_POSTGRESQL_YYYYmmdd        |
|   		        |                | 		       |ca_log_audit_event_POSTGRESQL_append_YYYYmmdd |
| PROTO_ID_TERADATA     |                |                     |ca_log_audit_event_TERADATA_YYYYmmdd          |
|   			|                |                     |ca_log_audit_event_TERADATA_append_YYYYmmdd   |
| PROTO_ID_CACHE        |                |                     |ca_log_audit_event_CACHE_YYYYmmdd             |
| 		        |                |                     |ca_log_audit_event_CACHE_append_YYYYmmdd      |
| PROTO_ID_KINGBASE     |                |                     |ca_log_audit_event_KINGBASE_YYYYmmdd          |
| 		        |                |                     |ca_log_audit_event_KINGBASE_append_YYYYmmdd   |
| PROTO_ID_DM           |                |                     |ca_log_audit_event_DM_YYYYmmdd                |
| 		        |                |                     |ca_log_audit_event_DM_append_YYYYmmdd         |
| PROTO_ID_SYBASE       |                |                     |ca_log_audit_event_SYBASE_YYYYmmdd            |
|    			|                |                     |ca_log_audit_event_SYBASE_append_YYYYmmdd     |
| PROTO_ID_INFORMIX     |                |                     |ca_log_audit_event_INFORMIX_YYYYmmdd          |
| 		        |                |                     |ca_log_audit_event_INFORMIX_append_YYYYmmdd   |
| PROTO_ID_GBASE        |                |                     |ca_log_audit_event_GBASE_YYYYmmdd             |
| 		        |                |                     |ca_log_audit_event_GBASE_append_YYYYmmdd      |
| PROTO_ID_SHENTONG     |                |                     |ca_log_audit_event_SHENTONG_YYYYmmdd          |
|-----------------------+----------------+---------------------+----------------------------------------------|
| PROTO_ID_TELNET:      |                |                     |ca_log_audit_event_TELNET_YYYYmmdd            |
| PROTO_ID_RLOGIN:      |                |                     |ca_log_audit_event_RLOGIN_YYYYmmdd            |
| PROTO_ID_X11:         | GRP_ID_CMDLINE | audit_event_cmdline |ca_log_audit_event_X11_YYYYmmdd               |
| PROTO_ID_XDMCP:       |                |                     |ca_log_audit_event_XDMCP_YYYYmmdd             |
| PROTO_ID_SSH:         |                |                     |ca_log_audit_event_SSH_YYYYmmdd               |
|-----------------------+----------------+---------------------+----------------------------------------------|
| PROTO_ID_FTP:         |                |                     |ca_log_audit_event_FTP_YYYYmmdd               |
| PROTO_ID_NFS:         |                |                     |ca_log_audit_event_NFS_YYYYmmdd               |
| PROTO_ID_NETBIOS_SSN: |                |                     |ca_log_audit_event_NETBIOS_SSN_YYYYmmdd       |
| PROTO_ID_PCNFSD:      | GRP_ID_FILE    | audit_event_file    |ca_log_audit_event_PCNFSD_YYYYmmdd            |
| PROTO_ID_SUNRPC:      |                |                     |ca_log_audit_event_SUNRPC_YYYYmmdd            |
| PROTO_ID_SCP:         |                |                     |ca_log_audit_event_SCP_YYYYmmdd               |
| PROTO_ID_SFTP:        |                |                     |ca_log_audit_event_SFTP_YYYYmmdd              |
| PROTO_ID_TFTP:        |                |                     |ca_log_audit_event_TFTP_YYYYmmdd              |
|-----------------------+----------------+---------------------+----------------------------------------------|
| PROTO_ID_RDP:         | GRP_ID_RDP     | audit_event_rdp     |ca_log_audit_event_RDP_YYYYmmdd               |
|-----------------------+----------------+---------------------+----------------------------------------------|
| PROTO_ID_VNC:         | GRP_ID_VNC     | audit_event_vnc     |ca_log_audit_event_VNC_YYYYmmdd               |
|-----------------------+----------------+---------------------+----------------------------------------------|
| PROTO_ID_UNKNOWN:     |                |                     |				              |
|-----------------------+----------------+---------------------+----------------------------------------------|
| PROTO_ID_HTTP:        | GRP_ID_HTTP    | audit_event_http    |ca_log_audit_event_HTTP_YYYYmmdd              |
| PROTO_ID_HTTPS:       |                |                     |ca_log_audit_event_HTTPS_YYYYmmdd             |
|-----------------------+----------------+---------------------+----------------------------------------------|
| PROTO_ID_POP3:        | GRP_ID_MAIL    | audit_event_mail    |ca_log_audit_event_POP3_YYYYmmdd              |
| PROTO_ID_SMTP:        |                |                     |ca_log_audit_event_SMTP_YYYYmmdd              |
|-----------------------+----------------+---------------------+----------------------------------------------|
| PROTO_ID_RADIUS:      | GRP_ID_RADIUS  | audit_event_radius  |ca_log_audit_event_RADIUS_YYYYmmdd            |
|-----------------------+----------------+---------------------+----------------------------------------------|
|                       |                | audit_event_other   |            				      |
|-----------------------+----------------+---------------------+----------------------------------------------|
*/
	unsigned char i;
	for (i = 0; i < PROTO_NUM; i++) {
		switch (i) {
                case PROTO_ID_DB2:
                case PROTO_ID_DAS:
                case PROTO_ID_TNS:
                case PROTO_ID_TDS:
                case PROTO_ID_MYSQL:
                case PROTO_ID_POSTGRESQL:
                case PROTO_ID_TERADATA:
                case PROTO_ID_CACHE:
                case PROTO_ID_KINGBASE:
                case PROTO_ID_DM:
                case PROTO_ID_SYBASE:
                case PROTO_ID_INFORMIX:
                case PROTO_ID_GBASE:
				case PROTO_ID_SHENTONG:
			global_grp_id[i] = GRP_ID_DB;
			break;
				case PROTO_ID_TELNET:
                case PROTO_ID_RLOGIN:
                case PROTO_ID_X11:
                case PROTO_ID_XDMCP:
                case PROTO_ID_SSH:
			global_grp_id[i] = GRP_ID_CMDLINE;
			break;
                case PROTO_ID_FTP:
                case PROTO_ID_NFS:
                case PROTO_ID_NETBIOS_SSN:
                case PROTO_ID_PCNFSD:
                case PROTO_ID_SUNRPC:
                case PROTO_ID_SCP:
                case PROTO_ID_SFTP:
                case PROTO_ID_TFTP:
			global_grp_id[i] = GRP_ID_FILE;
			break;
                case PROTO_ID_RDP:
			global_grp_id[i] = GRP_ID_RDP;
            break;
                case PROTO_ID_VNC:
            global_grp_id[i] = GRP_ID_VNC;
            break;
                case PROTO_ID_UNKNOWN:
            global_grp_id[i] = GRP_ID_OTHRER;
            break;
                case PROTO_ID_HTTP:
                case PROTO_ID_HTTPS:
            global_grp_id[i] = GRP_ID_HTTP;
            break;
                case PROTO_ID_POP3:
                case PROTO_ID_SMTP:
            global_grp_id[i] = GRP_ID_MAIL;
            break;
                case PROTO_ID_RADIUS:
			global_grp_id[i] = GRP_ID_RADIUS;
			break;
				case  PROTO_ID_DNS:
			global_grp_id[i] = GRP_ID_DNS;
			break;
		default:
			global_grp_id[i] = GRP_ID_OTHRER;
		}
	}
}

unsigned char proto_id2grpid(unsigned char proto_id)
{
	if (!global_init_flag) {
		proto_grp_init();
		global_init_flag = 1;
	}

	return global_grp_id[proto_id];
}

unsigned char proto_name2grpid(char *name)
{
	unsigned char proto_id = proto_name2id(name);

	return proto_id2grpid(proto_id);
}

void proto_id2grpname(unsigned char prot_id, char *grpname, int size)
{

}
