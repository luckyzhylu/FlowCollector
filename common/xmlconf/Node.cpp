#include "StdAfx.h"
#include <cassert>

#include <Public.h>
#include <Node.h>
#include "XmlTools.h"

NS_VITO_XML_CONF

typedef XmlParser<>::CNode_t CNode_t;

class CNodeImpl : public CNode_t
{
};

// Static data member
CNode CNode::NullNode = CNode(NULL);

CNode::CNode() throw() : m_pNodeImpl(NULL)
{
}

CNode::CNode(CNodeImpl* pNodeImpl) throw() : m_pNodeImpl(pNodeImpl)
{
}

CNode::~CNode() throw()
{
	m_pNodeImpl = NULL;
}

//-----------------------------------------------------------------------
bool CNode::operator==(const CNode& rcOtherNode) const throw(CError)
{
	return m_pNodeImpl == rcOtherNode.m_pNodeImpl;
}

bool CNode::operator!=(const CNode& rcOtherNode) const throw(CError)
{
	return m_pNodeImpl != rcOtherNode.m_pNodeImpl;
}

//-----------------------------------------------------------------------

const string& CNode::GetValue() const
{
	return GetNodeImpl()->GetValue();
}


void CNode::SetValue(const string& rcsValue) throw(CError)
{
	GetNodeImpl()->SetValue(rcsValue);
}

// Get and set node info
const string& CNode::GetName() const throw(CError)
{
	return GetNodeImpl()->GetName();
}

void CNode::SetName(const string& rcsName) throw(CError)
{
	GetNodeImpl()->SetName(rcsName);
}

const CNode CNode::InsertFirstChild(const string& rcsName) throw(CError)
{
	return CNode(static_cast<CNodeImpl*>(
							GetNodeImpl()->InsertFirstChild(rcsName)));
}

const CNode CNode::InsertNextSibling(const string& rcsName) throw(CError)
{
	return CNode(static_cast<CNodeImpl*>(
							GetNodeImpl()->InsertNextSibling(rcsName)));
}

void CNode::Delete() throw(CError)
{
	if (GetNodeImpl()->Delete())
	{
		m_pNodeImpl = NULL;
	}
}

const string CNode::GetAttribute(const string& rcsAttName) const throw(CError)
{
	return GetNodeImpl()->GetAttr(rcsAttName);
}

void CNode::SetAttribute(const string& rcsAttName, const string& rcsAttValue)
  throw(CError)
{
	GetNodeImpl()->SetAttr(rcsAttName, rcsAttValue);
}

void CNode::RemoveAttribute(const string& rcsAttName) throw(CError)
{
	GetNodeImpl()->RemoveAttr(rcsAttName);
}

void CNode::GetAttrMap(map<string, string>& rAttrMap) const
{
	GetNodeImpl()->GetAttrMap(rAttrMap);
}

void CNode::SetAttrMap(map<string, string>& rcAttrMap)
{
	GetNodeImpl()->SetAttrMap(rcAttrMap);
}

//----------------------------------------------------------------------
// Get other node
const CNode CNode::GetParent() const throw(CError)
{
	return CNode(static_cast<CNodeImpl*>(GetNodeImpl()->GetParent()));
}

const CNode CNode::GetFirstChild() const throw(CError)
{
	return CNode(static_cast<CNodeImpl*>(GetNodeImpl()->GetFirstChild()));
}

const CNode CNode::GetNextSibling() const throw(CError)
{
	return CNode(static_cast<CNodeImpl*>(GetNodeImpl()->GetNextSibling()));
}

const CNode CNode::GetChildByPath(const string& rcsPath) const throw(CError)
{
	return CNode(static_cast<CNodeImpl*>(
			GetNodeImpl()->GetChildByPath(rcsPath)));
}

const CNode CNode::GetFirstChildByName(const string& rcsName)
  const throw(CError)
{
	return CNode(static_cast<CNodeImpl*>(
			GetNodeImpl()->GetFirstChildByName(rcsName)));
}

const CNode CNode::GetNextSiblingByName(const string& rcsName)
  const throw(CError)
{
	return CNode(static_cast<CNodeImpl*>(
			GetNodeImpl()->GetNextSiblingByName(rcsName)));
}

const string CNode::ToString() const throw(CError)
{
	return GetNodeImpl()->ToString();
}

const CNodeImpl* CNode::GetNodeImpl() const throw(CError)
{
	if (NULL == m_pNodeImpl)
	{
		assert(false);
		throw CError(string(_T("Invalid node !")));
	}
	return m_pNodeImpl;
}

CNodeImpl* CNode::GetNodeImpl() throw(CError)
{
	if (NULL == m_pNodeImpl)
	{
		assert(false);
		throw CError(string(_T("Invalid node !")));
	}
	return m_pNodeImpl;
}

NS_END_LAYER_3
