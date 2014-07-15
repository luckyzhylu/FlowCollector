// CodingConv.cpp: implementation of the CCodingConv class.
//
//////////////////////////////////////////////////////////////////////

#include "StdAfx.h"

#include "CodingConv.h"
#include <stdio.h>

#include <memory.h>

#if WIN32
	#include <windows.h>
#else
	#include <strings.h>
	#include "iconv.h"
	#include "cerrno"
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

#if WIN32

static inline void Gb2312_2_Unicode(unsigned short* dst, char * src)
{
	::MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, src, 2, (LPWSTR)dst, 1);
}

static inline void Unicode_2_UTF8(char* dst, unsigned short* src)
{
	char* pchar = (char *)src;
	
	dst[0] = (0xE0 | ((pchar[1] & 0xF0) >> 4));
	dst[1] = (0x80 | ((pchar[1] & 0x0F) << 2)) + ((pchar[0] & 0xC0) >> 6);
	dst[2] = (0x80 | ( pchar[0] & 0x3F));
}

static inline void UTF8_2_Unicode(unsigned short* dst, const char * src)
{
	char* uchar = (char *)dst;
	
	uchar[1] = ((src[0] & 0x0F) << 4) + ((src[1] >> 2) & 0x0F);
	uchar[0] = ((src[1] & 0x03) << 6) + (src[2] & 0x3F);
}

static inline void Unicode_2_GB2312(char* dst, unsigned short uData)
{
	::WideCharToMultiByte(CP_ACP, NULL, (LPWSTR)&uData, 1, dst, 
				sizeof(unsigned short), NULL, NULL);
}

int CCodingConv::GB2312_2_UTF8(char * buf, int buf_len, 
			       char * src, int src_len)
{
	if (0 == src_len)
		src_len = strlen(src);

	int j = 0;
	for (int i = 0; i < src_len;)
	{
		if (j >= buf_len - 1)
			break;

		if (src[i] >= 0)
		{
			buf[j++] = src[i++];
		}
		else
		{
			unsigned short w_c = 0;
			Gb2312_2_Unicode(&w_c, src + i);

			char tmp[4] = "";
			Unicode_2_UTF8(tmp, &w_c);
			
			buf[j+0] = tmp[0];
			buf[j+1] = tmp[1];
			buf[j+2] = tmp[2];
			
			i += 2;
			j += 3;
		}
	}

	buf[j] = '\0';

	return j;
}

int CCodingConv::UTF8_2_GB2312(char * buf, int buf_len, 
			       const char * src, int src_len)
{
	if (0 == src_len)
		src_len = strlen(src);
	
	int j = 0;
	for (int i = 0; i < src_len;)
	{
		if (j >= buf_len - 1)
			break;

		if (src[i] >= 0)
		{
			buf[j++] = src[i++];
		}
		else
		{
			unsigned short w_c = 0;
			UTF8_2_Unicode(&w_c, src + i);
			
			char tmp[4] = "";
			Unicode_2_GB2312(tmp, w_c);
			
			buf[j+0] = tmp[0];
			buf[j+1] = tmp[1];
			
			i += 3;
			j += 2;
		}
	}
	
	buf[j] = '\0';
	
	return j;
}

#else // Linux
static inline  int
//code_convert(const char *from, const char *to, char* save, int savelen, char *src, int srclen)
code_convert(const char *from, const char *to, char *src, int srclen, char* save, int savelen)
{
        iconv_t cd;
        char   	*inbuf = src;
        char 	*outbuf = save;
        size_t 	outbufsize = savelen;
        int 	status = 0;
        int  	savesize = 0;
        int 	inbufsize = srclen;
        const char* inptr = inbuf;
        size_t  insize = inbufsize;
        char* 	outptr = outbuf;
        size_t 	outsize = outbufsize;
	//printf ("@@@@@@@@@@@ src:[%s]len(%d)\n", src, strlen(src));
	cd = iconv_open(to, from);
        // iconv(cd, NULL, NULL, NULL, NULL);
	if (inbufsize == 0)
	{
		status = -1;
		goto done;
	}
	while (insize > 0)
	{
		size_t res = iconv(cd,
				   (char**) &inptr,
				   &insize,
				   (char**) &outptr,
				   &outsize);
		if (outptr != outbuf)
		{
			int saved_errno = errno;
			int outsize = outptr - outbuf;
			strncpy (save + savesize, outbuf, outsize);
			errno = saved_errno;
		}
		if (res == (size_t)(-1))
		{
			if (errno == EILSEQ)
			{
				int one = 1;
				iconvctl(cd, ICONV_SET_DISCARD_ILSEQ, &one);
				status = -3;
			} else if (errno == EINVAL)
			{
				if (inbufsize == 0)
				{
					status = -4;
					goto done;
				} else
				{
					break;
				}
			} else if (errno == E2BIG)
			{
				status = -5;
				goto done;
			}else
			{
				status = -6;
				goto done;
			}
		}
	}
	status = strlen ( save );
done:
        iconv_close(cd);
	//printf ("ret:%d,src[%s]srclen:%d,save[%s],savelen:%d\n", status,
	//	src, srclen, save, savelen);
        return status;
}
/*
///////////////////////////////////
static inline int code_convert(char* srccharset, char* destcharset,
			       char* pinbuf, int& rninlen,
			       char* poutbuf, int& rnoutlen)
{
	iconv_t convt;
	int rc;
	char** pin = &pinbuf;
	char** pout	= &poutbuf;
	convt = ::iconv_open(destcharset, srccharset);
	if ((iconv_t)0 == convt)
	{
	  return -1;
	}
	::memset(poutbuf, 0, rnoutlen);

#ifdef __linux__
	printf ("111111111111111[%s]--[%d][%d]\n", pin, rninlen, rnoutlen);
	size_t stRet = ::iconv(convt, pin, (size_t*)&rninlen,
			       pout, (size_t*)&rnoutlen);
	printf ("22222222222222222222222222222222222:[%s]--[%d]\n", pout, rnoutlen);
	stRet = 1;

#else
#ifdef __sparc__
	size_t stRet = ::iconv(convt,
						   ( const char ** )pin,
						   (size_t*)&rninlen,
						   pout, (size_t*)&rnoutlen);
	
#endif
#endif
	if (-1 == stRet)
	{
		//printf ("");
		//::iconv_close(convt);
	  	//return -1;
	}
	printf ("333333333\n");
	::iconv_close(convt);
	return stRet;
}
*/
int CCodingConv::GB2312_2_UTF8(char * buf, int buf_len, 
			       char * src, int src_len)
{
	const int nFalse = -1;
  	if (0 == src_len)
		src_len = strlen(src);
	//printf ("GB2312_2_UTF8:src[%s]\n", src);
  	int nRet = code_convert("gbk", "utf-8", src, src_len, (char*)buf, buf_len);

	return ( nFalse == nRet ) ? nRet : strlen( buf );
}

int CCodingConv::UTF8_2_GB2312(char* buf, int buf_len,
			       const char * src, int src_len)
{
	const int nFalse = -1;
  	if (0 == src_len)
		src_len = strlen(src);
	//printf ("UTF8_2_GB2312:src[%s]\n", src);
	int nRet = code_convert("utf-8", "gbk", (char*)src, src_len,
		     (char*)buf, buf_len);

	return ( nFalse == nRet ) ? nRet : strlen( buf );
}

#endif
