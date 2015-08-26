#ifndef _XML_GROUP_H_
#define _XML_GROUP_H_

#include "libxml2_derive.h"

#include <string>
#include <list>

using namespace std;


class CMyXmlNode
{
public:
	CMyXmlNode();
	virtual bool NodeFill(xmlDocPtr doc, xmlNodePtr node) {
		return true;
	}
	virtual xmlChar* get_child_node(xmlDocPtr *doc, xmlNodePtr *cur, char *name);
	~CMyXmlNode();
};

class CLoadXmlGroup
{
public:
	CLoadXmlGroup(const string& rcsXmlFile = "");
	bool loadGroupByLabel(const char *label, const char *path, CMyXmlNode& rnode);
	~CLoadXmlGroup();
private:
	bool GetNodeByPath(xmlDocPtr doc, const char *path_key, xmlNodePtr *node);
private:
	string m_xmlFile;
};
#endif /* _XML_GROUP_H_ */
