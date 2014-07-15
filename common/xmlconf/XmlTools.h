#ifndef _XML_TOOLS_H_
#define _XML_TOOLS_H_

#include <utility>
#include <map>
#include <vector>
#include <exception>

#include "ExpatNode.h"
#include "ExpatParser.h"
#include <Error.h>
#include <Public.h>

using std::map;
using std::vector;
using std::exception;

NS_VITO_XML_CONF

template<
			class Parser = CExpatParser, 
			class ExceptionDispose = CError
		>
class XmlParser : public Parser
{
public:
	typedef typename Parser::CNode_t	CNode_t;

public:
	XmlParser() throw()
	{
	}
	~XmlParser() throw()
	{
	}

	// Load and save xml
	inline bool LoadXmlFile(const string& rcsFilePath) 
							throw(ExceptionDispose)
	{
		try
		{
			return Parser::LoadXmlFile(rcsFilePath);
		}
		catch (exception& exceptionCur)
		{
			throw ExceptionDispose(exceptionCur.what());
		}
		catch (...)
		{
			throw ExceptionDispose(string(_T("Open xml file with error !")));
		}
		return false;
	}
	inline bool SaveXmlFile(const string& rcsFilePath) throw(ExceptionDispose)
	{
		try
		{
			return Parser::SaveXmlFile(rcsFilePath);
		}
		catch (exception& exceptionCur)
		{
			throw ExceptionDispose(exceptionCur.what());
		}
		catch (...)
		{
			throw ExceptionDispose(string(_T("Save xml file with error !")));
		}
		return false;
	}
	inline bool LoadXmlString(const string& rcsXml)
							throw(ExceptionDispose)
	{
		try
		{
			return Parser::LoadXmlString(rcsXml);
		}
		catch (exception& exceptionCur)
		{
			throw ExceptionDispose(exceptionCur.what());
		}
		catch (...)
		{
			throw ExceptionDispose(string(_T("Open xml string with error !")));
		}
		return false;
	}
	inline bool SaveXmlString(string& rcsXml) throw(ExceptionDispose)
	{
		try
		{
			return Parser::SaveXmlString(rcsXml);
		}
		catch (exception& exceptionCur)
		{
			throw ExceptionDispose(exceptionCur.what());
		}
		catch (...)
		{
			throw ExceptionDispose(string(_T("Save xml string with error !")));
		}
		return false;
	}

	inline const CNode_t* GetRootNode()
	{
		return Parser::GetRootNode();
	}
	inline const CNode_t* CreateXml(const string& rcsVersion, 
								const string& rcsEncoding, 
								const string& rcsRootName)
	{
		return Parser::CreateXml(rcsVersion, rcsEncoding, rcsRootName);
	}

};

NS_END_LAYER_3

#endif // _XML_TOOLS_H_
