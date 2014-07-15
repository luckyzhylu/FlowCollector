#ifndef _EXPAT_PARSER_H_
#define _EXPAT_PARSER_H_

#include <expat.h>
#include <map>
#include <Public.h>
#include "ExpatNode.h"

NS_VITO_XML_CONF

class CExpatNode;
class CExpatParser
{
public:


public:
	typedef CExpatNode	CNode_t;

	enum EXPAT_CONF
	{
		EC_SMALL_BUF_SIZE = 1024 * 16, 
		EC_MID_BUF_SIZE = 1024 * 64, 
		EC_LARGE_BUF_SIZE = 1024 * 256
	};

public:
	CExpatParser();
	~CExpatParser();

	bool LoadXmlFile(const string& rcsFile);
	bool LoadXmlString(const string& rcsXml);
	bool SaveXmlFile(const string& rcsFile);
	bool SaveXmlString(string& rsXml);
	bool Clear();
	bool Empty() const throw();
	
	const CNode_t* CreateXml(const string& rcsVersion, 
								const string& rcsEncoding,
								const string& rcsRootName);
	
	inline CNode_t* GetRootNode()
	{
		return m_pRootNode;
	}

public:
	static void DeclHandler(void *pUserData, const XML_Char *pVersion,
				const XML_Char *pEncoding, int standalone);
	static void StartHandler(void* pUserData, const char* pElement, 
								const char** ppAttr);
	static void EndHandler(void* pUserData, const char* pElement);
	static void CommentHandler(void* pUserData, const XML_Char* pXmlCharData);

	static void CharacterDataHandler(void *userData, const XML_Char *s, int len);
protected:
	bool CheckXmlFileHeader(const string& rcsXmlHeader);
	bool CheckXmlStrHeader(const string& rcsXmlStr);

protected:
	CNode_t*		m_pRootNode;
	string			m_sVersion;
	string			m_sEncoding;
};

NS_END_LAYER_3

#endif // _EXPAT_PARSER_H_
