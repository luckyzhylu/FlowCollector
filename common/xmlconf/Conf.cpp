#include <Public.h>
#include <Conf.h>
#include <Node.h>
#include <Error.h>
#include "XmlTools.h"
#include "ExpatParser.h"

NS_VITO_XML_CONF

class CConfImpl : public XmlParser<>
{
public:
	typedef XmlParser<>::CNode_t	CNode_t;

};

CConf::CConf() throw() : m_pConfImpl(NULL)
{
	m_pConfImpl = new CConfImpl();
	assert(NULL != m_pConfImpl);
}

CConf::~CConf() throw()
{
	if (NULL != m_pConfImpl)
	{
		delete m_pConfImpl;
		m_pConfImpl = NULL;
	}
}

void CConf::LoadXmlFile(const string& rcsFile) throw(CError)
{
	m_pConfImpl->LoadXmlFile(rcsFile);
}

void CConf::LoadXmlText(const string& rcsText) throw(CError)
{
	m_pConfImpl->LoadXmlString(rcsText);
}

void CConf::SaveXmlFile(const string& rcsFile) const throw(CError)
{
	m_pConfImpl->SaveXmlFile(rcsFile);
}

void CConf::SaveXmlText(string& rsText) const throw(CError)
{
	m_pConfImpl->SaveXmlString(rsText);
}

void CConf::Clear()
{
	m_pConfImpl->Clear();
}

bool CConf::Empty() const throw()
{
	return m_pConfImpl->Empty();
}

const CNode CConf::GetRootNode() const throw()
{
	return CNode((CNodeImpl*)(m_pConfImpl->GetRootNode()));
}

NS_END_LAYER_3
