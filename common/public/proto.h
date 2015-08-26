#ifndef _PROTO_H
#define _PROTO_H
#include <sys/types.h>
#include "proto.h"

#define PROTO_NUM	128	//modified from 256 by ww
enum {
	PROTO_ID_UN_ETHER = -2,	/* for proto_flow, add by Chen Yu */
	PROTO_ID_UN_IP = -1,	/* for proto_flow, add by Chen Yu */

	PROTO_ID_NULL = 0,
	PROTO_ID_ETHER = 1,
	PROTO_ID_ARP,
	PROTO_ID_IP,
	PROTO_ID_UDP,
	PROTO_ID_TCP,		//5
	PROTO_ID_ICMP,
	PROTO_ID_IGMP,
	PROTO_ID_EGP,
	PROTO_ID_HTTP,
	PROTO_ID_TELNET,	//10
	
	PROTO_ID_FTP,
	PROTO_ID_SUNRPC,
	PROTO_ID_DNS,
	PROTO_ID_WHOIS,
	PROTO_ID_SMTP,		//15
	PROTO_ID_POP3,
	PROTO_ID_NETBIOS_NS,
	PROTO_ID_NETBIOS_SSN,
	PROTO_ID_NETBIOS_DGM,
	PROTO_ID_NNTP,		//20
	
	PROTO_ID_IRC,
	PROTO_ID_NFS,
	PROTO_ID_PMAP,
	PROTO_ID_AUTH,
	PROTO_ID_CHARGEN,	//25
	PROTO_ID_SNMP,
	PROTO_ID_RIP,
	PROTO_ID_IMAP,
	PROTO_ID_TFTP,
	PROTO_ID_MSRPC,		//30
	
	PROTO_ID_FINGER,
	PROTO_ID_RLOGIN,
	PROTO_ID_NTALK,
	PROTO_ID_ECHO,
	PROTO_ID_TDS,		//35
	PROTO_ID_TNS,
	PROTO_ID_MSPROXY,
	PROTO_ID_PCT,
	PROTO_ID_DB2,
	PROTO_ID_INFORMIX,	//40
	
	PROTO_ID_X11,
	PROTO_ID_XDMCP,
	PROTO_ID_RDP,
	PROTO_ID_UNKNOWN,
	PROTO_ID_DAS,		//45
	PROTO_ID_RADIUS,
	PROTO_ID_PCNFSD,
	PROTO_ID_MYSQL,
	PROTO_ID_POSTGRESQL,
	PROTO_ID_TERADATA,	//50
	
	PROTO_ID_CACHE,
	PROTO_ID_KINGBASE,	//52
	PROTO_ID_DM,		//53
	PROTO_ID_SSH,		//54
	PROTO_ID_SCP,		//55
	PROTO_ID_SFTP,		//56
	PROTO_ID_SYBASE,	//57
	PROTO_ID_GBASE,
	PROTO_ID_VNC,		//59
	PROTO_ID_HTTPS,
	
	PROTO_ID_SHENTONG,
	PROTO_ID_BORDER
};

enum {
	GRP_ID_DB = 0,
	GRP_ID_MAIL = 1,
	GRP_ID_HTTP = 2,
	GRP_ID_FILE = 3,
	GRP_ID_CMDLINE = 4,
	GRP_ID_RADIUS = 5,
	GRP_ID_RDP = 6,
	GRP_ID_VNC = 7,
	GRP_ID_DNS = 8,
	GRP_ID_OTHRER = 9,
	GRP_ID_MAX = GRP_ID_OTHRER + 1
};

unsigned char proto_name2grpid(char *name);
unsigned char proto_id2grpid(unsigned char proto_id);
void proto_id2grpname(unsigned char prot_id, char *grpname, int size);

unsigned char proto_id2grpid(unsigned char proto_id);
unsigned char proto_name2id(char *name);
void proto_id2name(unsigned char id, char *name, int len);

#endif				//_PROTO_H
