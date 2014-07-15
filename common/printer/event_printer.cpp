#include "event_printer.h"

#include <time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

void Printer::NetflowPrint(void* pEvt, ostream & rOs)
{
	char buf[64];
	struct tm t;
	struct in_addr in;

	netflow_base_t *rcEvt = (netflow_base_t *)pEvt;

	rOs << "session_id:" << (long long int)rcEvt->session_id << endl;
	in.s_addr = rcEvt->src_ip;
	rOs << "src_ip:" << inet_ntoa(in) << endl;
	in.s_addr = rcEvt->dst_ip;
	rOs << "dst_ip:" << inet_ntoa(in) << endl;
	rOs << "src_port:" << (unsigned short)rcEvt->src_port << endl;
	rOs << "dst_port:" << (unsigned short)rcEvt->dst_port << endl;
	rOs << "transport_protocol:" << (int)rcEvt->transport_protocol << endl;
	localtime_r(&rcEvt->start_time, &t);
	strftime(buf, sizeof(buf), "%Y%m%d %H:%M:%S", &t);
	rOs << "start_time:" << buf << endl;
	localtime_r(&rcEvt->end_time, &t);
	strftime(buf, sizeof(buf), "%Y%m%d %H:%M:%S", &t);
	rOs << "end_time:" << buf << endl;
	rOs << "high_proto_id:" << (int)rcEvt->high_proto_id << endl;
	rOs << "up_package_count:" << (unsigned long long int)rcEvt->up_package_count << endl;
	rOs << "up_byte_count:" << (unsigned long long int)rcEvt->up_byte_count << endl;
	rOs << "down_package_count:" << (unsigned long long int)rcEvt->down_package_count << endl;
	rOs << "down_byte_count:" << (unsigned long long int)rcEvt->down_byte_count << endl;
	rOs << "level:" << (int)rcEvt->level << endl;
	rOs << "record_cap:" << (int)rcEvt->record_cap << endl;
	rOs << "list_of_id:" << (long long int)rcEvt->list_of_id << endl;
	rOs << "audit_event_count:" << (int)rcEvt->audit_event_count << endl;
	rOs << "src_dev_id:" << (long long int)rcEvt->src_dev_id << endl;
	rOs << "src_domain_id:" << (long long int)rcEvt->src_domain_id << endl;
	rOs << "dst_dev_id:" << (long long int)rcEvt->dst_dev_id << endl;
	rOs << "dst_domain_id:" << (long long int)rcEvt->dst_domain_id << endl;
}

void Printer::MonitorPrint(const netflow_monitor_event & rcEvet, ostream & rOs)
{
}
