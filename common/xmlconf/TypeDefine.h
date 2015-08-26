/**
 * @file
 *
 * 本文件定义了若干个宏和类型，便于在不同操作系统平台之间进行代码移植
 */


#ifndef __TYPE_DEFINE__H__
#define __TYPE_DEFINE__H__

#include <cstring>
#include <cwchar>
#include <string>


//////////////////////////////////////////////////////////////////////
// string 类型定义

#ifdef _UNICODE
	typedef std::wstring	string;
#else
#endif



//////////////////////////////////////////////////////////////////////
// TCHAR 和标准 C 函数的定义

#ifdef _MSC_VER

	#include <tchar.h>

#else

	#ifdef _UNICODE

		#ifndef	_T
			#define _T(x)		L ## x
		#endif
		typedef wchar_t			TCHAR;


		/* Program */

		#define _tmain      wmain
		#define _tenviron   _wenviron
		#define __targv     __wargv


		/* Formatted i/o */

		#define _tprintf    wprintf
		#define _tcprintf   _cwprintf
		#define _ftprintf   fwprintf
		#define _stprintf   swprintf
		#define _sctprintf  _scwprintf
		#define _sntprintf  snwprintf
		#define _vtprintf   vwprintf
		#define _vftprintf  vfwprintf
		#define _vstprintf  vswprintf
		#define _vsctprintf _vscwprintf
		#define _vsntprintf _vsnwprintf
		#define _tscanf     wscanf
		#define _tcscanf    _cwscanf
		#define _ftscanf    fwscanf
		#define _stscanf    swscanf
		#define _sntscanf   _snwscanf


		/* Unformatted i/o */

		#define _fgettc     fgetwc
		#define _fgettchar  _fgetwchar
		#define _fgetts     fgetws
		#define _fputtc     fputwc
		#define _fputtchar  _fputwchar
		#define _fputts     fputws
		#define _cputts     _cputws
		#define _cgetts     _cgetws
		#define _gettc      getwc
		#define _gettch     _getwch
		#define _gettche    _getwche
		#define _gettchar   getwchar
		#define _getts      _getws
		#define _puttc      putwc
		#define _puttchar   putwchar
		#define _puttch     _putwch
		#define _putts      _putws
		#define _ungettc    ungetwc
		#define _ungettch   _ungetwch


		/* String conversion functions */

		#define _tcstod     wcstod
		#define _tcstol     wcstol
		#define _tcstoul    wcstoul
		#define _tstof      _wtof
		#define _tstol      _wtol
		#define _tstoi      _wtoi

		#define _itot       _itow
		#define _ltot       _ltow
		#define _ultot      _ultow
		#define _ttoi       _wtoi
		#define _ttol       _wtol

		#define _tstoi64    _wtoi64
		#define _ttoi64     _wtoi64
		#define _tcstoi64   _wcstoi64
		#define _tcstoui64  _wcstoui64
		#define _i64tot     _i64tow
		#define _ui64tot    _ui64tow


		/* String functions */

		#define _tcscat     wcscat
		#define _tcschr     wcschr
		#define _tcscpy     wcscpy
		#define _tcscspn    wcscspn
		#define _tcsdup     _wcsdup

		#define _tcslen     wcslen
		#define _tcsncat    wcsncat
		#define _tcsncpy    wcsncpy
		#define _tcspbrk    wcspbrk
		#define _tcsrchr    wcsrchr
		#define _tcsspn     wcsspn
		#define _tcsstr     wcsstr
		#define _tcstok     wcstok
		#define _tcserror   _wcserror
		#define __tcserror  __wcserror

		#define _tcsnset    _wcsnset
		#define _tcsrev     _wcsrev
		#define _tcsset     _wcsset

		#define _tcscmp     wcscmp
		#define _tcsicmp    _wcsicmp
		#define _tcsnccmp   wcsncmp
		#define _tcsncmp    wcsncmp
		#define _tcsncicmp  _wcsnicmp
		#define _tcsnicmp   _wcsnicmp

		#define _tcscoll    wcscoll
		#define _tcsicoll   _wcsicoll
		#define _tcsnccoll  _wcsncoll
		#define _tcsncoll   _wcsncoll
		#define _tcsncicoll _wcsnicoll
		#define _tcsnicoll  _wcsnicoll


		/* Execute functions */

		#define _texecl     _wexecl
		#define _texecle    _wexecle
		#define _texeclp    _wexeclp
		#define _texeclpe   _wexeclpe
		#define _texecv     _wexecv
		#define _texecve    _wexecve
		#define _texecvp    _wexecvp
		#define _texecvpe   _wexecvpe

		#define _tspawnl    _wspawnl
		#define _tspawnle   _wspawnle
		#define _tspawnlp   _wspawnlp
		#define _tspawnlpe  _wspawnlpe
		#define _tspawnv    _wspawnv
		#define _tspawnve   _wspawnve
		#define _tspawnvp   _wspawnvp
		#define _tspawnvpe  _wspawnvpe

		#define _tsystem    _wsystem


		/* Time functions */

		#define _tasctime   _wasctime
		#define _tctime     _wctime
		#define _tctime64   _wctime64
		#define _tstrdate   _wstrdate
		#define _tstrtime   _wstrtime
		#define _tutime     _wutime
		#define _tutime64   _wutime64
		#define _tcsftime   wcsftime


		/* Directory functions */

		#define _tchdir     wchdir
		#define _tgetcwd    _wgetcwd
		#define _tgetdcwd   _wgetdcwd
		#define _tmkdir     _wmkdir
		#define _trmdir     _wrmdir


		/* Environment/Path functions */

		#define _tfullpath  _wfullpath
		#define _tgetenv    _wgetenv
		#define _tmakepath  _wmakepath
		#define _tpgmptr    _wpgmptr
		#define _tputenv    _wputenv
		#define _tsearchenv _wsearchenv
		#define _tsplitpath _wsplitpath


		/* Stdio functions */

		#define _tfdopen    _wfdopen
		#define _tfsopen    _wfsopen
		#define _tfopen     _wfopen
		#define _tfreopen   _wfreopen
		#define _tperror    _wperror
		#define _tpopen     _wpopen
		#define _ttempnam   _wtempnam
		#define _ttmpnam    _wtmpnam


		/* Io functions */

		#define _taccess    _waccess
		#define _tchmod     _wchmod
		#define _tcreat     _wcreat
		#define _tfindfirst _wfindfirst
		#define _tfindfirst64   _wfindfirst64
		#define _tfindfirsti64  _wfindfirsti64
		#define _tfindnext  _wfindnext
		#define _tfindnext64    _wfindnext64
		#define _tfindnexti64   _wfindnexti64
		#define _tmktemp    _wmktemp
		#define _topen      _wopen
		#define _tremove    _wremove
		#define _trename    _wrename
		#define _tsopen     _wsopen
		#define _tunlink    _wunlink

		#define _tfinddata_t    _wfinddata_t
		#define _tfinddata64_t  __wfinddata64_t
		#define _tfinddatai64_t _wfinddatai64_t


		/* Stat functions */

		#define _tstat      _wstat
		#define _tstat64    _wstat64
		#define _tstati64   _wstati64


		/* Setlocale functions */

		#define _tsetlocale _wsetlocale


		/* "logical-character" mappings */

		#define _tcsclen    wcslen
		#define _tcsnccat   wcsncat
		#define _tcsnccpy   wcsncpy
		#define _tcsncset   _wcsnset

		#define _tcsdec     _wcsdec
		#define _tcsinc     _wcsinc
		#define _tcsnbcnt   _wcsncnt
		#define _tcsnccnt   _wcsncnt
		#define _tcsnextc   _wcsnextc
		#define _tcsninc    _wcsninc
		#define _tcsspnp    _wcsspnp

		#define _tcslwr     _wcslwr
		#define _tcsupr     _wcsupr
		#define _tcsxfrm    wcsxfrm


		/* ctype-functions */

		#define _totupper   towupper
		#define _totlower   towlower

		#define _istalnum   iswalnum
		#define _istalpha   iswalpha
		#define _istascii   iswascii
		#define _istcntrl   iswcntrl
		#define _istdigit   iswdigit
		#define _istgraph   iswgraph
		#define _istlower   iswlower
		#define _istprint   iswprint
		#define _istpunct   iswpunct
		#define _istspace   iswspace
		#define _istupper   iswupper
		#define _istxdigit  iswxdigit


		#define _istlead(_c)    (0)
		#define _istlegal(_c)   (1)
		#define _istleadbyte(_c)    (0)



	#else   // not define _UNICODE

		#ifndef _T
			#define _T(x)		x
		#endif
		typedef char			TCHAR;


		/* Program */

		#define _tmain      main
		#define _tenviron   environ
		#define __targv     __argv


		/* Formatted i/o */

		#define _tprintf    printf
		#define _tcprintf   _cprintf
		#define _ftprintf   fprintf
		#define _stprintf   sprintf
		#define _sctprintf  _scprintf
		#define _sntprintf  snprintf
		#define _vtprintf   vprintf
		#define _vftprintf  vfprintf
		#define _vstprintf  vsprintf
		#define _vsctprintf _vscprintf
		#define _vsntprintf _vsnprintf
		#define _tscanf     scanf
		#define _tcscanf    _cscanf
		#define _ftscanf    fscanf
		#define _stscanf    sscanf
		#define _sntscanf   _snscanf


		/* Unformatted i/o */

		#define _fgettc     fgetc
		#define _fgettchar  _fgetchar
		#define _fgetts     fgets
		#define _fputtc     fputc
		#define _fputtchar  _fputchar
		#define _fputts     fputs
		#define _cputts     _cputs
		#define _cgetts     _cgets
		#define _gettc      getc
		#define _gettch     _getch
		#define _gettche    _getche
		#define _gettchar   getchar
		#define _getts      gets
		#define _puttc      putc
		#define _puttchar   putchar
		#define _puttch     _putch
		#define _putts      puts
		#define _ungettc    ungetc
		#define _ungettch   _ungetch


		/* String conversion functions */

		#define _tcstod     strtod
		#define _tcstol     strtol
		#define _tcstoul    strtoul
		#define _tstof      atof
		#define _tstol      atol
		#define _tstoi      atoi

		#define _itot       _itoa
		#define _ltot       _ltoa
		#define _ultot      _ultoa
		#define _ttoi       atoi
		#define _ttol       atol

		#define _tstoi64    _atoi64
		#define _ttoi64     _atoi64
		#define _tcstoi64   _strtoi64
		#define _tcstoui64  _strtoui64
		#define _i64tot     _i64toa
		#define _ui64tot    _ui64toa


		/* String functions */

		#define _tcscat     strcat
		#define _tcschr     strchr
		#define _tcscpy     strcpy
		#define _tcscspn    strcspn
		#define _tcsdup     _strdup

		#define _tcslen     strlen
		#define _tcsncat    strncat
		#define _tcsncpy    strncpy
		#define _tcspbrk    strpbrk
		#define _tcsrchr    strrchr
		#define _tcsspn     strspn
		#define _tcsstr     strstr
		#define _tcstok     strtok
		#define _tcserror   strerror
		#define __tcserror  _strerror

		#define _tcsnset    _strnset
		#define _tcsrev     _strrev
		#define _tcsset     _strset

		#define _tcscmp     strcmp
		#define _tcsicmp    _stricmp
		#define _tcsnccmp   strncmp
		#define _tcsncmp    strncmp
		#define _tcsncicmp  _strnicmp
		#define _tcsnicmp   _strnicmp

		#define _tcscoll    strcoll
		#define _tcsicoll   _stricoll
		#define _tcsnccoll  _strncoll
		#define _tcsncoll   _strncoll
		#define _tcsncicoll _strnicoll
		#define _tcsnicoll  _strnicoll


		/* Execute functions */

		#define _texecl     execl
		#define _texecle    execle
		#define _texeclp    execlp
		#define _texeclpe   _execlpe
		#define _texecv     execv
		#define _texecve    execve
		#define _texecvp    execvp
		#define _texecvpe   _execvpe

		#define _tspawnl    _spawnl
		#define _tspawnle   _spawnle
		#define _tspawnlp   _spawnlp
		#define _tspawnlpe  _spawnlpe
		#define _tspawnv    _spawnv
		#define _tspawnve   _spawnve
		#define _tspawnvp   _spawnvp
		#define _tspawnvpe  _spawnvpe

		#define _tsystem    system


		/* Time functions */

		#define _tasctime   asctime
		#define _tctime     ctime
		#define _tctime64   _ctime64
		#define _tstrdate   _strdate
		#define _tstrtime   _strtime
		#define _tutime     _utime
		#define _tutime64   _utime64
		#define _tcsftime   strftime


		/* Directory functions */

		#define _tchdir     chdir
		#define _tgetcwd    getcwd
		#define _tgetdcwd   _getdcwd
		#define _tmkdir     _mkdir
		#define _trmdir     _rmdir


		/* Environment/Path functions */

		#define _tfullpath  _fullpath
		#define _tgetenv    getenv
		#define _tmakepath  _makepath
		#define _tpgmptr    _pgmptr
		#define _tputenv    putenv
		#define _tsearchenv _searchenv
		#define _tsplitpath _splitpath


		/* Stdio functions */

		#define _tfdopen    fdopen
		#define _tfsopen    _fsopen
		#define _tfopen     fopen
		#define _tfreopen   freopen
		#define _tperror    perror
		#define _tpopen     popen
		#define _ttempnam   tempnam
		#define _ttmpnam    tmpnam


		/* Io functions */

		#define _taccess    access
		#define _tchmod     chmod
		#define _tcreat     _creat
		#define _tfindfirst _findfirst
		#define _tfindfirst64   _findfirst64
		#define _tfindfirsti64  _findfirsti64
		#define _tfindnext  _findnext
		#define _tfindnext64    _findnext64
		#define _tfindnexti64   _findnexti64
		#define _tmktemp    mktemp
		#define _topen      open
		#define _tremove    remove
		#define _trename    rename
		#define _tsopen     _sopen
		#define _tunlink    _unlink

		#define _tfinddata_t    _finddata_t
		#define _tfinddata64_t  __finddata64_t
		#define _tfinddatai64_t _finddatai64_t


		/* Stat functions */

		#define _tstat      stat
		#define _tstat64    stat64
		#define _tstati64   _stati64


		/* Setlocale functions */

		#define _tsetlocale setlocale


		/* "logical-character" mappings */

		#define _tcsclen    strlen
		#define _tcsnccat   strncat
		#define _tcsnccpy   strncpy
		#define _tcsncset   _strnset

		#define _tcsdec     _strdec
		#define _tcsinc     _strinc
		#define _tcsnbcnt   _strncnt
		#define _tcsnccnt   _strncnt
		#define _tcsnextc   _strnextc
		#define _tcsninc    _strninc
		#define _tcsspnp    _strspnp

		#define _tcslwr     _strlwr
		#define _tcsupr     _strupr
		#define _tcsxfrm    strxfrm


		/* ctype-functions */

		#define _totupper   toupper
		#define _totlower   tolower

		#define _istalnum   isalnum
		#define _istalpha   isalpha
		#define _istascii   isascii
		#define _istcntrl   iscntrl
		#define _istdigit   isdigit
		#define _istgraph   isgraph
		#define _istlower   islower
		#define _istprint   isprint
		#define _istpunct   ispunct
		#define _istspace   isspace
		#define _istupper   isupper
		#define _istxdigit  isxdigit


		#define _istlead(_c)    (0)
		#define _istlegal(_c)   (1)
		#define _istleadbyte(_c)    (0)



	#endif // _UNICODE


#endif // _MSC_VER



//////////////////////////////////////////////////////////////////////
// 不同宽度的整数类型的定义

typedef unsigned char		BYTE;		///< 8 bit integer
typedef unsigned short		WORD;		///< 16 bit integer
typedef unsigned long		DWORD;		///< 32 bit integer



//////////////////////////////////////////////////////////////////////
// 不同函数调用方式的定义

#ifdef _MSC_VER
	#define CALLBACK		__stdcall
	#define WINAPI			__stdcall
	#define PASCAL			__stdcall
#else
	#define CALLBACK
	#define WINAPI
	#define PASCAL
#endif // _MSC_VER



#endif // #ifndef __TYPE_DEFINE__H__
