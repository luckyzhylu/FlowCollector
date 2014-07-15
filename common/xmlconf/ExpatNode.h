#ifndef _EXPAT_NODE_H_
#define _EXPAT_NODE_H_

#include <map>
#include <assert.h>
#include <string>
#include <Public.h>
using namespace std;


NS_VITO_XML_CONF

class CExpatNode
{
public:
	CExpatNode(const string& rcsName = string());
	~CExpatNode();

	bool Delete();
	CExpatNode* InsertNextSibling(const string& rcsName = string());
	CExpatNode* InsertFirstChild(const string& rcsName = string());

	CExpatNode* GetChildByPath(const string& rcsPath) const;
	CExpatNode* GetFirstChildByName(const string& rcsName) const;
	CExpatNode* GetNextSiblingByName(const string& rcsName) const;

	const string GetAttr(const string& rcsName) const;
	bool SetAttr(const string& rcsName, const string& rcsValue);
	bool RemoveAttr(const string& rcsName);

	void GetAttrMap(std::map<string, string>& rmapAttr) const;
	void SetAttrMap(std::map<string, string>& rmapAttr);

	// Creare xml node info
	string ToString() const;
	inline void SetValue(const string& rcsValue)
	{
		m_sValue = rcsValue;
	}
	inline const string& GetValue() const
	{
		return m_sValue;
	}
	inline bool SetName(const string& rcsName)
	{
		IsValidName(rcsName);
		m_sName = rcsName;
		return true;
	}
	inline const string& GetName() const
	{
		return m_sName;
	}
	inline CExpatNode* SetParent(CExpatNode* pParent)
	{
		return m_pParent = pParent;
	}
	inline CExpatNode* GetParent() const
	{
		return m_pParent;
	}
	inline CExpatNode* SetFirstChild(CExpatNode* pFirstChild)
	{
		if(pFirstChild != NULL)
		{
			assert(pFirstChild->GetParent() == this);
		}
		return m_pFirstChild = pFirstChild;
	}
	inline CExpatNode* GetFirstChild() const
	{
		return m_pFirstChild;
	}
	inline CExpatNode* SetNextSibling(CExpatNode* pNextSibling)
	{
		if(pNextSibling != NULL)
		{
			assert(pNextSibling->GetParent() == this->GetParent());
		}
		return m_pNextSibling = pNextSibling;
	}
	inline CExpatNode* GetNextSibling() const
	{
		assert(GetParent() != NULL);
		return m_pNextSibling;
	}

protected:
	bool DestoryNode();
	void IsValidName(const string& rcsName) const;

	const string EncodingSpecialChar(const string& rsXml) const;
	string AttrsToString() const;

protected:
	CExpatNode*					m_pParent;
	CExpatNode*					m_pFirstChild;
	CExpatNode*					m_pNextSibling;

	string						m_sName;
	string						m_sValue;
	string						m_sContent;

	std::map<string, string>	m_mapAttr;

};

NS_END_LAYER_3

#endif // _EXPAT_NODE_H_
