#include "Conf.h"
#include "Node.h"
#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;
using namespace XmlConf;

int main(int argc, char *argv[])
{
	CConf conf;

	conf.LoadXmlFile("watchdog.xml");
	return 0;
}
