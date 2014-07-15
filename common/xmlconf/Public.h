#ifndef __VITO__XML__CONF__PUBLIC__H__
#define __VITO__XML__CONF__PUBLIC__H__

#include <stdexcept>
#include <TypeDefine.h>



#define NS_VITO_XML_CONF	namespace XmlConf {		\

#ifndef NS_END_LAYER_3
	#define NS_END_LAYER_3		}
#endif


#ifdef _MSC_VER
	#pragma warning(disable:4290)
#endif

#if defined(WIN32) && !defined(_LIB)


	#define LIB_DEBUG_OPT "R"

	#ifdef _UNICODE
		#error "Not support unicode option!"
	#else
		#define LIB_CHARSET_OPT "A"
	#endif

	#ifdef _DLL
		#define LIB_RT_OPT "D"
	#else
		#define LIB_RT_OPT "S"
	#endif

	#ifndef _MT
		#error "Must enable multi thread compile option!"
	#endif

	#ifndef _CPPRTTI
		#error "Must enable run-time type information!"
	#endif

	#ifndef _CPPUNWIND
		#error "Must enable exception handling!"
	#endif

	#ifdef _MSC_VER

	#else
		#error "Must compile with VC++ in win32!"
	#endif


	#ifdef COMPILER_OPT
		#define XMLCONF_LIB "Conf_" LIB_DEBUG_OPT LIB_CHARSET_OPT LIB_RT_OPT "_" COMPILER_OPT ".lib"
		#pragma message("Linking " XMLCONF_LIB)
		#pragma comment(lib, XMLCONF_LIB)
	#endif

	#ifdef LIB_DEBUG_OPT
		#undef LIB_DEBUG_OPT
	#endif

	#ifdef LIB_CHARSET_OPT
		#undef LIB_CHARSET_OPT
	#endif

	#ifdef LIB_RT_OPT
		#undef LIB_RT_OPT
	#endif

	#ifdef COMPILER_OPT
		#undef COMPILER_OPT
	#endif

	#ifdef XMLCONF_LIB
		#undef XMLCONF_LIB
	#endif

#endif // #if defined(WIN32) && !defined(_LIB)

#endif // #ifndef __VITO__XML__CONF__PUBLIC__H__
