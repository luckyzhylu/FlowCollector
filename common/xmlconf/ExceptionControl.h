#ifndef _EXCEPTION_CONTROL_H_
#define _EXCEPTION_CONTROL_H_

#include <Public.h>

// Namespace begin
NS_VITO_XML_CONF

template<class dispose>
class exception_control : public exception, public dispose
{
public:
	exception_control(const string& ctstrDesc = string())
					: m_tstrDesc(ctstrDesc)
	{
	}

	~exception_control()
	{
	}

	inline dispose_event()
	{
		assert(!string.empty());
		dispose::dispose_event(m_tstrDesc);
	}
	
protected:
	string m_tstrDesc;
	
};

// Namespace end
NS_END_LAYER_3

#define // _EXCEPTION_CONTROL_H_
