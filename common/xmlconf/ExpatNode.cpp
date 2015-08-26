#include <Error.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;

#include <cctype>

#include "ExpatNode.h"
#include <Public.h>

NS_VITO_XML_CONF

CExpatNode::CExpatNode(const string& rcsName)
	: m_pParent(NULL),
	  m_pFirstChild(NULL),
	  m_pNextSibling(NULL)
{
	m_sName.assign(rcsName.begin(), rcsName.end());
}

CExpatNode::~CExpatNode()
{
	DestoryNode();
}


bool CExpatNode::DestoryNode()
{
	CExpatNode* pCurTemp	= m_pFirstChild;
	CExpatNode* pNextTemp	= NULL;
	while (NULL != pCurTemp)
	{
		pNextTemp = pCurTemp->GetNextSibling();
		delete pCurTemp;
		pCurTemp = pNextTemp;
	}
	m_pParent		= NULL;
	m_pFirstChild	= NULL;
	m_pNextSibling	= NULL;
	m_sName			= string();
	m_sValue		= string();
	m_sContent		= string();
	m_mapAttr.clear();

	return true;
}

void CExpatNode::IsValidName(const string& rcsName) const
{
	const string csErrDesc = rcsName + _T(": Invalid name !");

	if (rcsName.empty())
	{
		assert(false);
		throw CError(csErrDesc);
	}
	if (::isdigit(rcsName[0]))
	{
		assert(false);
		throw CError(csErrDesc);
	}

	size_t stLength = rcsName.length();
	for (size_t i = size_t() ; i < stLength ; ++i)
	{
		if (::isalpha(rcsName[i]) || ::isdigit(rcsName[i]) ||
			_T('_') == rcsName[i])
		{
			continue;
		}
		else
		{
			assert(false);
			throw CError(csErrDesc);
		}
	}
}

CExpatNode* CExpatNode::InsertNextSibling(const string& rcsName)
{
	IsValidName(rcsName);

	CExpatNode* pNode = new CExpatNode(rcsName);
	if(NULL == pNode)
	{
		assert(false);
		throw bad_alloc();
	}
	pNode->SetParent(GetParent());
	pNode->SetNextSibling(m_pNextSibling);
	SetNextSibling(pNode);

	return pNode;
}

CExpatNode* CExpatNode::InsertFirstChild(const string& rcsName)
{
	CExpatNode* pNode = new CExpatNode(rcsName);
	if(NULL == pNode)
	{
		assert(false);
		throw bad_alloc();
	}
	pNode->SetParent(this);
	pNode->SetNextSibling(m_pFirstChild);
	SetFirstChild(pNode);

	return pNode;
}

bool CExpatNode::Delete()
{
	/// Can not delete root node
	if (NULL == GetParent())
	{
		throw CError(string(_T("Can not delete root node !")));
	}

	CExpatNode* pPreChild	= GetParent();
	CExpatNode* pCurChild	= GetParent()->GetFirstChild();
	CExpatNode* pNextChild	= NULL;
	while (NULL != pCurChild)
	{
		pNextChild	= pCurChild->GetNextSibling();
		if (this == pCurChild)
		{
			if (pCurChild == GetParent()->GetFirstChild())
			{
				GetParent()->SetFirstChild(pNextChild);
			}
			else
			{
				pPreChild->SetNextSibling(pNextChild);
			}
			DestoryNode();
			delete pCurChild;
			return true;
		}
		pPreChild = pCurChild;
		pCurChild = pNextChild;
	}
	return false;
}

CExpatNode* CExpatNode::GetChildByPath(const string& rcsPath) const
{
	if (rcsPath.empty())
	{
		assert(false);
		throw CError(rcsPath + _T(": Path empty !"));
	}
	string sPath = rcsPath;
	if (_T('/') != *sPath.begin())	// Begin char is not '/'
	{
		throw CError(rcsPath + _T(": Path must begin with \'/\'!"));
	}
	else
	{
		sPath.erase(sPath.begin());
	}
	if (_T('/') == *(sPath.end() - 1))		// Last char is not '/'
	{
		string::iterator sItEnd = sPath.end();
		sPath.erase(--sItEnd);
	}

	size_t stIndexPre	= size_t();
	size_t stIndexCur	= size_t();
	CExpatNode* pChild	= (CExpatNode*)this;
	while (NULL != pChild)
	{
		stIndexCur = sPath.find(_T('/'), stIndexPre);
		string		sName;
		CExpatNode*	pTemp	= pChild;
		if (stIndexCur == string::npos)
		{
			sName = sPath.substr(stIndexPre);
			pChild = pTemp->GetFirstChildByName(sName);
			if (NULL != pChild)
			{
				return pChild;
			}
			break;
		}
		sName = sPath.substr(stIndexPre, stIndexCur - stIndexPre);
		pTemp = pChild->GetFirstChildByName(sName);
		if (NULL == pTemp)
		{
			return NULL;
		}
		pChild = pTemp;
		stIndexPre = ++stIndexCur;
	}

	return NULL;
}

const string CExpatNode::GetAttr(const string& rcsName) const
{
	IsValidName(rcsName);

	std::map<string, string>::const_iterator itFind = m_mapAttr.find(rcsName);
	if (itFind != m_mapAttr.end())
	{
		return itFind->second;
	}
	else
	{
		throw CError(rcsName + _T(": Not find attribute !"));
	}

	return string();
}

bool CExpatNode::SetAttr(const string& rcsName, const string& rcsValue)
{
	IsValidName(rcsName);

	string sKey;
	string sValue;
	sKey.assign(rcsName.begin(), rcsName.end());
	sValue.assign(rcsValue.begin(), rcsValue.end());
	m_mapAttr[sKey] = sValue;
	return true;
}

bool CExpatNode::RemoveAttr(const string& rcsName)
{
	IsValidName(rcsName);

	if (m_mapAttr.empty())
	{
		return false;
	}
	std::map<string, string>::iterator itFind = m_mapAttr.find(rcsName);
	if (itFind != m_mapAttr.end())
	{
		m_mapAttr.erase(itFind);
		return true;
	}
	return false;
}

void CExpatNode::GetAttrMap(std::map<string, string>& rmapAttr) const
{
	rmapAttr = m_mapAttr;
}

void CExpatNode::SetAttrMap(std::map<string, string>& rmapAttr)
{
	if (!rmapAttr.empty())
	{
		m_mapAttr.swap(rmapAttr);
	}
}

CExpatNode* CExpatNode::GetFirstChildByName(const string& rcsName) const
{
	IsValidName(rcsName);

	CExpatNode* pChild = m_pFirstChild;
	while (NULL != pChild)
	{
		if (pChild->GetName() == rcsName)
		{
			return pChild;
		}
		pChild = pChild->GetNextSibling();
	}

	return NULL;
}

CExpatNode* CExpatNode::GetNextSiblingByName(const string& rcsName) const
{
	IsValidName(rcsName);

	CExpatNode* pNextSibling = m_pNextSibling;
	while (NULL != pNextSibling)
	{
		if (pNextSibling->GetName() == rcsName)
		{
			return pNextSibling;
		}
		pNextSibling = pNextSibling->GetNextSibling();
	}

	return false;
}

string CExpatNode::ToString() const
{
	string sRet;
	sRet = string(_T("<")) + m_sName + AttrsToString() + string(_T(">"));
	if (!m_sValue.empty()) {
		sRet += m_sValue;
	}

	CExpatNode* pNextTemp	= m_pFirstChild;
	while (NULL != pNextTemp)
	{
		sRet += pNextTemp->ToString();
		pNextTemp = pNextTemp->GetNextSibling();
	}
	sRet += string(_T("</")) + m_sName + string(_T(">"));
	return sRet;
}

string CExpatNode::AttrsToString() const
{
	string sRet;
	std::map<string, string>::const_iterator itBegin	= m_mapAttr.begin();
	std::map<string, string>::const_iterator itEnd	= m_mapAttr.end();
	std::map<string, string>::const_iterator itTemp	= itBegin;
	for (itTemp = itBegin ; itTemp != itEnd ; ++itTemp)
	{
		// convert
		sRet += string(_T(" ")) + itTemp->first + string(_T("=")) +
					string(_T("\"")) + EncodingSpecialChar(itTemp->second) + 
					string(_T("\""));
	}
	return sRet;
}

///----------------------------------------------------------------------------
static const unsigned int g_s_cunNum = 5;
static const string g_s_csChar[g_s_cunNum] =
{
	_T("&gt;"), _T("&amp;"), _T("&lt;"), _T("&#039;"), _T("&quot;")
};

static const string g_s_csSpecialChar[g_s_cunNum] =
{
	_T(">"), _T("&"), _T("<"), _T("'"),	_T("\"")
};

class CEncodingSpecialChar
{
public:
	CEncodingSpecialChar()
	{
	}

	void operator()(const string::value_type& vtArgu)
	{
		string sTemp(string::size_type(1), vtArgu);
		for (unsigned int i = 0 ; i < g_s_cunNum ; ++i)
		{
			if (sTemp == g_s_csSpecialChar[i])
			{
				sTemp = g_s_csChar[i];
				break;
			}
		}
		m_sXml += sTemp;
	}
	const string& GetXmlString()
	{
		return m_sXml;
	}

protected:
	string m_sXml;
};

const string CExpatNode::EncodingSpecialChar(const string& rsXml) const
{
	/**
	'>' == &gt;,
	'&' == &amp;,
	'<' == &It;,
	''' == &#039;,
	'"' == &quot;
	*/
	CEncodingSpecialChar oEncodingChar;
	oEncodingChar = std::for_each(rsXml.begin(), rsXml.end(), oEncodingChar);
	return oEncodingChar.GetXmlString();
}

NS_END_LAYER_3
