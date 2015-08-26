#ifndef __AFX_STDAFX_H__
#define __AFX_STDAFX_H__


#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers

#ifdef _WIn32
#pragma warning (disable: 4511)
#pragma warning (disable: 4512)
#pragma warning (disable: 4786)
#pragma warning (disable: 4290)
#endif

#include <cassert>


#define PROC_ERROR(sDesc)					\
{											\
	assert(false);							\
	throw CError(sDesc);					\
}											\


#endif // #ifndef __AFX_STDAFX_H__
