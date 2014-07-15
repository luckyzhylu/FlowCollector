#ifndef _AA_EVENT_PRINTER_H_
#define _AA_EVENT_PRINTER_H_

#include "vito_comm_struct.h"
#include "audit_data_struct.h"
#include <iostream>

using namespace std;

class Printer
{
public:
	static void NetflowPrint(void* rcEvt, ostream& rOs = cout);
	static void AuditPrint(void* rcEvt, ostream& rOs = cout);
	static void MonitorPrint(const netflow_monitor_event& rcEvet, ostream& rOs = cout);
};



#endif /* _EVENT_PRINTER_H_ */
