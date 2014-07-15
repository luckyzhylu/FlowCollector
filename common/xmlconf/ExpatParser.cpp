#include "StdAfx.h"
#include <cassert>
#include <vector>
#include <fstream>
#include <utility>
#include <algorithm>
#include <cstdlib>
#include <exception>

#if WIN32
#ifdef _MSC_EXTENSIONS
#undef _MSC_EXTENSIONS
#endif
#endif

#include <expat.h>
#include "ExpatParser.h"
#include <Error.h>
#include <Public.h>
using namespace XmlConf;

#include "CodingConv.h"

static const unsigned int g_s_unfactor		= 3;
static const unsigned int g_s_cunUtf8Flag	= 3;
static const unsigned char g_s_cucUtf8Header[g_s_cunUtf8Flag] = 
{ 0xEF, 0xBB, 0xBF };

static const string g_s_csGB2312	= _T("gb2312");
static const string g_s_csUtf8		= _T("utf-8");
static const string g_s_csHeaderLeft	= _T("<?");
static const string g_s_csHeaderRight	= _T("?>");

NS_VITO_XML_CONF

class CParserStruct
{
public:
	typedef CExpatNode	CNode_t;

public:
	//CParserStruct::CParserStruct( ){};
	CParserStruct(
		CExpatParser* pExpatParser,
		CExpatNode* pRootNode) {
		m_pParser	= pExpatParser;
		m_pRoot	= pRootNode;
		m_pNodeCur	= pRootNode;
		m_nDepthPre	= 0;
		m_nDepthCur	= 0;
	}

public:
	CExpatParser*	m_pParser;
	CNode_t*	m_pRoot;
	CNode_t*	m_pNodeCur;
	int		m_nDepthPre;
	int		m_nDepthCur;

};

///----------------------------------------------------------------------------

CExpatParser::CExpatParser() : m_pRootNode(NULL)
{
}

CExpatParser::~CExpatParser()
{
	Clear();
}

bool CExpatParser::Clear()
{
	delete m_pRootNode;
	m_pRootNode = NULL;

	return true;
}

bool CExpatParser::Empty() const throw()
{
	return NULL == m_pRootNode;
}

bool CExpatParser::CheckXmlFileHeader(const string& rcsFile)
{
	std::ifstream iFile(rcsFile.c_str(), std::ios_base::binary);
	if (!iFile.is_open())
	{
		throw CError(rcsFile + _T(": Open file fail!"));
		assert(false);
	}
	std::vector<char> vecBuffer(EC_MID_BUF_SIZE);
	char* pbuffer = &(*vecBuffer.begin());
	::memset(pbuffer, 0, EC_MID_BUF_SIZE);
	iFile.read(pbuffer, EC_MID_BUF_SIZE);

	bool bIsUtf8 = false;
	const char* pHeader = pbuffer;
	if (0 == ::memcmp(pHeader, g_s_cucUtf8Header, g_s_cunUtf8Flag))
	{
		bIsUtf8 = true;
		pHeader += g_s_cunUtf8Flag;
	}

	string sHeader(pHeader);
	transform(sHeader.begin(), sHeader.end(), sHeader.begin(), ::tolower);
	string::size_type  stLeft	= sHeader.find(g_s_csHeaderLeft);
	string::size_type  stRight	= sHeader.find(g_s_csHeaderRight);

	sHeader.assign(sHeader, stLeft, stRight - stLeft);
	string::size_type nRet = sHeader.find(g_s_csUtf8);
	if (nRet != string::npos)
	{
		m_sEncoding = g_s_csUtf8;
		return true;
	}
	else if (bIsUtf8)
	{
		assert(false);
		throw CError(string(_T("Xml file format error !")));
	}

	nRet = sHeader.find(g_s_csGB2312);
	if (nRet != string::npos)
	{
		m_sEncoding = g_s_csGB2312;
		return true;
	}

	return false;
}

bool CExpatParser::CheckXmlStrHeader(const string& rcsXmlStr)
{
	if (rcsXmlStr.empty())
	{
		assert(false);
		return false;
	}

	bool bIsUtf8 = false;
	const char* pHeader = rcsXmlStr.c_str();

	string sHeader(pHeader);
	transform(sHeader.begin(), sHeader.end(), sHeader.begin(), ::tolower);
	string::size_type  stLeft	= sHeader.find(g_s_csHeaderLeft);
	string::size_type  stRight	= sHeader.find(g_s_csHeaderRight);

	sHeader.assign(sHeader, stLeft, stRight - stLeft);
	string::size_type nRet = sHeader.find(g_s_csUtf8);
	if (nRet != string::npos)
	{
		m_sEncoding = g_s_csUtf8;
		return true;
	}
	else if (bIsUtf8)
	{
		assert(false);
		throw CError(string(_T("Xml file format error !")));
	}

	nRet = sHeader.find(g_s_csGB2312);
	if (nRet != string::npos)
	{
		m_sEncoding = g_s_csGB2312;
		return true;
	}

	return false;
}

bool CExpatParser::LoadXmlFile(const string& rcsFile)
{
	if (rcsFile.empty())
	{
		assert(false);
		throw CError(rcsFile + _T(": File name is empty !"));
	}
	if (NULL != m_pRootNode)
	{
		assert(false);
		Clear();
		throw CError(string(_T("NULL != m_pRootNode")));
	}
	if (!CheckXmlFileHeader(rcsFile))
	{
		assert(false);
		throw CError(rcsFile + string(_T(": Xml file header error !")));
	}

	m_pRootNode	= new CNode_t();
	::XML_Parser xmlp = ::XML_ParserCreate(_T("utf-8"));
	CParserStruct UserData(this, m_pRootNode);

	::XML_SetUserData(xmlp, static_cast<void*>(&UserData));
	::XML_SetXmlDeclHandler(xmlp, DeclHandler);
	::XML_SetElementHandler(xmlp, StartHandler, EndHandler);
	::XML_SetCommentHandler(xmlp, CommentHandler);
	::XML_SetCharacterDataHandler(xmlp, CharacterDataHandler);

	std::vector<string::value_type> vecBuffer(EC_LARGE_BUF_SIZE);
	int nBuffer = vecBuffer.size() * sizeof(string::value_type);
	std::ifstream iFile(rcsFile.c_str(), std::ios_base::binary);
	if (!iFile.is_open())
	{
		throw CError(rcsFile + _T(": Open file fail!"));
	}

	char* pbufUtf8 = NULL;
	std::vector<string::value_type> vecBufUtf8(EC_LARGE_BUF_SIZE * g_s_unfactor);
	int nBufUtf8 = vecBufUtf8.size() * sizeof(string::value_type);
	while (true)
	{
		::memset(&(*vecBuffer.begin()), 0, nBuffer);
		iFile.read(&(*vecBuffer.begin()), EC_LARGE_BUF_SIZE);
		bool bIsFinal	= iFile.eof();
		long lSize		= EC_LARGE_BUF_SIZE;
		if (bIsFinal)
		{
			lSize = iFile.gcount();
		}
		if (g_s_csGB2312 == m_sEncoding)
		{
			::memset(&(*vecBufUtf8.begin()), 0, sizeof(nBufUtf8));
			lSize = CCodingConv::GB2312_2_UTF8(&(*vecBufUtf8.begin()), 
											nBufUtf8, &(*vecBuffer.begin()));
			pbufUtf8 = &(*vecBufUtf8.begin());
		}
		else
		{
			pbufUtf8 = &(*vecBuffer.begin());
		}

		XML_Status statusCur = ::XML_Parse(xmlp, pbufUtf8, lSize, bIsFinal);
		assert (XML_STATUS_OK == statusCur);
		if (XML_STATUS_ERROR == statusCur)
		{
			const string csErr = XML_ErrorString(XML_GetErrorCode(xmlp));
			iFile.clear();
			iFile.close();
			::XML_ParserFree(xmlp);
			xmlp = NULL;
			throw CError(csErr);
		}
		if (bIsFinal)
		{
			break;
		}
	}
	iFile.clear();
	iFile.close();
	::XML_ParserFree(xmlp);
	xmlp = NULL;

	return true;
}

bool CExpatParser::LoadXmlString(const string& rcsXml)
{
	if (rcsXml.empty())
	{
		assert(false);
		throw CError(string(_T("Xml string is empty !")));
	}
	if (NULL != m_pRootNode)
	{
		assert(false);
		Clear();
		throw CError(string(_T("NULL != m_pRootNode")));
	}
	if (!CheckXmlStrHeader(rcsXml))
	{
		assert(false);
		throw CError(string(_T("Xml string header error !")));
	}

	m_pRootNode	= new CNode_t();
	::XML_Parser xmlp = ::XML_ParserCreate(_T("utf-8"));
	CParserStruct UserData(this, m_pRootNode);

	::XML_SetUserData(xmlp, static_cast<void*>(&UserData));
	::XML_SetXmlDeclHandler(xmlp, DeclHandler);
	::XML_SetElementHandler(xmlp, StartHandler, EndHandler);
	::XML_SetCommentHandler(xmlp, CommentHandler);
	::XML_SetCharacterDataHandler(xmlp, CharacterDataHandler);

	char* pbufUtf8									= NULL;
	std::vector<string::value_type> vecBufUtf8(EC_LARGE_BUF_SIZE * g_s_unfactor);
	std::vector<string::value_type> vecBuffer(EC_LARGE_BUF_SIZE);
	int nBufUtf8 = vecBufUtf8.size() * sizeof(string::value_type);
	int nBuffer = vecBuffer.size() * sizeof(string::value_type);
	int nLength	= rcsXml.length();
	for (int i = 0 ; ; ++i)
	{
		vecBuffer.assign(nBuffer, 0);
		rcsXml.copy(&(*vecBuffer.begin()), EC_LARGE_BUF_SIZE, EC_LARGE_BUF_SIZE * i);

		bool bIsFinal = nLength < (EC_LARGE_BUF_SIZE * i) + EC_LARGE_BUF_SIZE;
		long lSize = EC_LARGE_BUF_SIZE;
		if (bIsFinal)
		{
			lSize = nLength - (i * EC_LARGE_BUF_SIZE);
		}

		if (g_s_csGB2312 == m_sEncoding)
		{
			vecBufUtf8.assign(nBufUtf8, 0);
			lSize = CCodingConv::GB2312_2_UTF8(&(*vecBufUtf8.begin()), 
											nBufUtf8, &(*vecBuffer.begin()));
			pbufUtf8 = &(*vecBufUtf8.begin());
		}
		else
		{
			pbufUtf8 = &(*vecBuffer.begin());
		}

		XML_Status statusCur = ::XML_Parse(xmlp, pbufUtf8, lSize, bIsFinal);
		assert (XML_STATUS_OK == statusCur);
		if (XML_STATUS_ERROR == statusCur)
		{
			const string csErr = XML_ErrorString(XML_GetErrorCode(xmlp));
			::XML_ParserFree(xmlp);
			xmlp = NULL;
			throw CError(csErr);
		}
		if (bIsFinal)
		{
			break;
		}
	}
	::XML_ParserFree(xmlp);
	xmlp = NULL;

	return true;
}

bool CExpatParser::SaveXmlFile(const string& rcsFile)
{
	assert(!rcsFile.empty());
	if (rcsFile.empty())
	{
		return false;
	}

	std::ofstream oFile(rcsFile.c_str(), std::ios_base::binary | std::ios_base::out );
	if (!oFile.is_open())
	{
		throw CError(rcsFile + _T(": Open file fail!"));
	}
	if ( g_s_csUtf8 == m_sEncoding )
	{
		// oFile << g_s_cucUtf8Header;
		oFile.write( ( const char* )g_s_cucUtf8Header, sizeof( g_s_cucUtf8Header ) );
	}
	string sHeader;
	if (!m_sVersion.empty() && !m_sEncoding.empty())
	{
		sHeader = string("<?xml version=\"") + m_sVersion
						+ string("\" encoding=\"")+ m_sEncoding
						+ string("\" ?>");
	}
	oFile << sHeader;

	string tTemp = GetRootNode()->ToString();
	char* pData = (char*)tTemp.data();
	if (g_s_csUtf8 == m_sEncoding)
	{
		unsigned int unLength	= tTemp.size() * sizeof(string::value_type);
		if (0 != unLength)
		{
			unsigned int unBufSize	= unLength * 4;
			std::vector<char> vecBuffer(unBufSize);
			char* pBuff = &(*vecBuffer.begin());
			::memset(pBuff, 0, unBufSize);
			int nRet = CCodingConv::GB2312_2_UTF8(pBuff, unBufSize,
							      pData, unLength);
			if (-1 == nRet)
			{
				assert(false);
				throw CError(string(_T("GB2312_2_UTF8 fail !")));
			}
			oFile << pBuff;
		}
	}
	else if (g_s_csGB2312 == m_sEncoding)
	{
		oFile << pData;
	}
	else
	{
		assert(false);
	}
	oFile.clear();
	oFile.close();

	return true;
}

bool CExpatParser::SaveXmlString(string& rsXml)
{
	string sHeader;
	if (!m_sVersion.empty() && !m_sEncoding.empty())
	{
		sHeader = string("<?xml version=\"") + m_sVersion
						+ string("\" encoding=\"")+ m_sEncoding
						+ string("\" ?>");
	}
	rsXml = sHeader;

	string tTemp	= GetRootNode()->ToString();
	char* pData		= (char*)tTemp.data();
	if (g_s_csUtf8 == m_sEncoding)
	{
		unsigned int unLength	= tTemp.size() * sizeof(string::value_type);
		if (0 != unLength)
		{
			unsigned int unBufSize	= unLength * 4;
			std::vector<char> vecBuffer(unBufSize);
			char* pBuff = &(*vecBuffer.begin());
			::memset(pBuff, 0, unBufSize);
			int nRet = CCodingConv::GB2312_2_UTF8(pBuff, unBufSize, 
												pData, unLength);
			if (-1 == nRet)
			{
				assert(false);
				throw CError(string(_T("GB2312_2_UTF8 fail !")));
			}
			rsXml += pBuff;
		}
	}
	else if (g_s_csGB2312 == m_sEncoding)
	{
		rsXml += pData;
	}
	else
	{
		assert(false);
	}

	return true;
}

const CExpatParser::CNode_t* CExpatParser::CreateXml(const string& rcsVersion,
						     const string& rcsEncoding,
						     const string& rcsRootName)
{
	if (rcsVersion.empty() || rcsRootName.empty() || rcsRootName.empty())
	{
		assert(false);
		return NULL;
	}

	// Remove root node
	delete m_pRootNode;
	m_pRootNode = NULL;
	m_sVersion = rcsVersion;
	m_sEncoding= rcsEncoding;
	// Create root node
	m_pRootNode = new CExpatNode(rcsRootName);
	if (NULL == m_pRootNode)
	{
		assert(false);
		throw CError(string(_T("Create xml fail !")));
	}
	return m_pRootNode;
}

void CExpatParser::DeclHandler(void* pUserData, const XML_Char* pVersion,
								const XML_Char* pEncoding, int standalone)
{
	CParserStruct* pParserStruct = static_cast<CParserStruct*>(pUserData);
	CExpatParser* pMy = pParserStruct->m_pParser;

	string sEncoding(pEncoding);
	transform(sEncoding.begin(), sEncoding.end(), sEncoding.begin(), ::tolower);
	if (g_s_csUtf8 != sEncoding && g_s_csGB2312 != sEncoding)
	{
		throw CError(string(_T("Xml header error !")));
	}

	pMy->m_sVersion		= pVersion;
	pMy->m_sEncoding	= sEncoding;
}

void CExpatParser::CharacterDataHandler(void *pUserData, const XML_Char *s, int len)
{
	string sValue;
	char *pBegin = NULL;
	char *pEnd = NULL;
	CParserStruct* pParserStruct = static_cast<CParserStruct*>(pUserData);
	CNode_t*&	rpNodeCur	= pParserStruct->m_pNodeCur;

	if (len <= 0) {
		return;
	}

	pBegin = (char *)s;
	for (pEnd = pBegin + len; isspace(*pEnd) && pEnd > pBegin; pEnd--); // trim left
	if (pEnd != pBegin + len) {
		pEnd++;
	}
	for (; isspace(*pBegin) && pBegin < pEnd; pBegin++); // trim right

	if (pEnd == pBegin) {
		return;
	}

	sValue = string(pBegin, pEnd);

	rpNodeCur->SetValue(sValue);
}

void CExpatParser::StartHandler(void* pUserData, const char* pElement,
				const char** ppAttr)
{
	assert(NULL != ppAttr && NULL != pElement);

	CParserStruct* pParserStruct = static_cast<CParserStruct*>(pUserData);
	CNode_t*&	rpRoot		= pParserStruct->m_pRoot;
	CNode_t*&	rpNodeCur	= pParserStruct->m_pNodeCur;
	int&		rnDepthPre	= pParserStruct->m_nDepthPre;
	int&		rnDepthCur	= pParserStruct->m_nDepthCur;

	if (rnDepthCur == rnDepthPre && rpNodeCur != rpRoot)
	{
		rpNodeCur = rpNodeCur->InsertNextSibling(pElement);
		assert (NULL != rpNodeCur);
	}
	else if (rnDepthCur > rnDepthPre)
	{
		rpNodeCur = rpNodeCur->InsertFirstChild(pElement);
		assert (NULL != rpNodeCur);
	}
	else if(rnDepthCur < rnDepthPre)
	{
		for ( ; rnDepthCur != rnDepthPre ; --rnDepthPre)
		{
			rpNodeCur = rpNodeCur->GetParent();
			assert (NULL != rpNodeCur);
		}
		rpNodeCur = rpNodeCur->InsertNextSibling(pElement);
		assert (NULL != rpNodeCur);
	}
	else
	{
		rpNodeCur->SetName(pElement);
	}

	std::vector<char> vecValue(EC_MID_BUF_SIZE);
	unsigned int unValueSize = EC_MID_BUF_SIZE * sizeof(char);
	char* pValue = &(*vecValue.begin());
	std::map<string, string> mapTemp;
	for (int i = 0 ; NULL != ppAttr[i] ; i += 2)
	{
		::memset(pValue, 0, unValueSize);
		int nRet = CCodingConv::UTF8_2_GB2312(pValue, unValueSize,
						      (char*)ppAttr[i + 1]);
		if (-1 == nRet)
		{
			throw CError(string(_T("UTF8_2_GB2312 fail !")) + string("\n")
				     + string(pValue) + string("\n")
				     + string((char*)ppAttr[i + 1]));
			assert(false);
		}
		mapTemp[ppAttr[i]] = pValue;
	}
	rpNodeCur->SetAttrMap(mapTemp);

	rnDepthPre = rnDepthCur;
	++rnDepthCur;
}

void CExpatParser::EndHandler(void* pUserData, const char* pElement)
{
	CParserStruct* pParserStruct = static_cast<CParserStruct*>(pUserData);
	int& rnDepthCur	= pParserStruct->m_nDepthCur;

	--rnDepthCur;
}

void CExpatParser::CommentHandler(void* pUserData, const XML_Char* pXmlCharData)
{
}

NS_END_LAYER_3
