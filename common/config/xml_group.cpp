#include "xml_group.h"

CMyXmlNode::CMyXmlNode()
{
}

CMyXmlNode::~CMyXmlNode()
{
}


xmlChar* CMyXmlNode::get_child_node(xmlDocPtr *doc, xmlNodePtr *cur, char *name)
{
	xmlNodePtr node = *cur;
	node = node->xmlChildrenNode;
	xmlChar *value = NULL;

	while (NULL != node) {
		if ((!xmlStrcmp(node->name, (const xmlChar *)name))) {
			value = xmlNodeListGetString(*doc, node->xmlChildrenNode, 1);
			goto out;
		}
		node = node->next;
	}
out:
	return value;

}

CLoadXmlGroup::CLoadXmlGroup(const string & rcsXmlFile)
{
	m_xmlFile = rcsXmlFile;
}

bool CLoadXmlGroup::loadGroupByLabel(const char *label, const char *path, CMyXmlNode& rnode)
{
	xmlNodePtr node = NULL;
	xmlDocPtr doc = xmlParseFile(m_xmlFile.c_str());
	if (doc == NULL) {
		goto err;
	}

	if (!GetNodeByPath(doc, path, &node)) {
		goto err;
	}

	node = node->xmlChildrenNode;

	while (NULL != node) {
		if ((!xmlStrcmp(node->name, (const xmlChar *)label))) {
			rnode.NodeFill(doc, node);
		}
		node = node->next;
	}
	xmlFreeDoc(doc);

	return true;
err:
	if (doc) {
		xmlFreeDoc(doc);
	}

	return false;
}

CLoadXmlGroup::~CLoadXmlGroup()
{
}

bool CLoadXmlGroup::GetNodeByPath(xmlDocPtr doc, const char *path_key, xmlNodePtr *node)
{
	xmlNodePtr cur;
	xmlNodePtr tempNode;
	const char *d = "/";
	char *p;
	char path[1024] = {0};
	int32_t min = 0;

	if (doc == NULL || NULL == path_key || NULL == node){
		goto err;
	}
	cur = xmlDocGetRootElement(doc);
	if (cur == NULL){
		goto err;
	}

	min = 1023 > strlen(path_key) ? strlen(path_key) : 1023;
	strncpy(path, path_key, min);

	p = strtok(path, d);

	while(p) {
		while (cur != NULL) {
			if (xmlStrcmp((const xmlChar *)p, cur->name) == 0) {
				break;
			}

			cur = cur->next;
		}

		if (NULL == cur) {
			goto err;
		}

		p = strtok(NULL, d);

		if (NULL == p) {
			*node = cur;
			cur = cur->next;
			while (cur) {
				tempNode = cur->next;
				xmlUnlinkNode(cur);
				xmlFreeNode(cur);
				cur = tempNode;
			}

			//memory
			(*node)->next = NULL;
			break;
		} else {
			cur = cur->xmlChildrenNode;
		}
	}

	return true;

err:
	return false;
}
