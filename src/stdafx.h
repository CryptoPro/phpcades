// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//
#pragma once

#define CRYPT_SIGN_MESSAGE_PARA_HAS_CMS_FIELDS
#define CMSG_SIGNER_ENCODE_INFO_HAS_CMS_FIELDS
#define CMSG_SIGNED_ENCODE_INFO_HAS_CMS_FIELDS
#define CERT_PARA_HAS_EXTRA_FIELDS
#define IGNORE_LEGACY_FORMAT_MESSAGE_MSG

#define IS_CADES_VERSION_GREATER_EQUAL(major, minor, build) \
    (CPRO_CADES_VERSION_MAJOR > (major) || \
    (CPRO_CADES_VERSION_MAJOR == (major) && CPRO_CADES_VERSION_MINOR > (minor)) || \
    (CPRO_CADES_VERSION_MAJOR == (major) && CPRO_CADES_VERSION_MINOR == (minor) && CPRO_CADES_VERSION_BUILD >= (build)))

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#ifdef _WIN32
#define RETURN_ATL_STRING  RETURN_ATL_STRING_W
#define RETURN_ATL_STRINGL RETURN_ATL_STRINGL_W
#endif

/* C99 requires these for C++ to get the definitions
 * of INT64_MAX and other macros used by Zend/zend_long.h
 * C11 drops this requirement, so these effectively
 * just backport that piece of behavior.
 */
#ifdef __cplusplus
# ifndef __STDC_LIMIT_MACROS
#  define __STDC_LIMIT_MACROS
# endif
# ifndef __STDC_CONSTANT_MACROS
#  define __STDC_CONSTANT_MACROS
# endif
#endif


#include <iostream>
#include <memory> //Этот хедер тут нужен что бы компилить с новыми версиями libstdc++
                  //в них есть конфликт с __in и __out макросами которые определены в MS хедерах.

#ifdef UNIX
    #include "CSP_WinDef.h"
    #include "CSP_WinError.h"
    #include <string>
    #include <stdarg.h>
    #include <atldef2.h>
    #define CADES_CLASS
    #define RETURN_ATL_STRING  RETURN_ATL_STRING_A
    #define RETURN_ATL_STRINGL RETURN_ATL_STRINGL_A
#else
#   include <Windows.h>
#endif //UNIX

#include <WinCryptEx.h>

#include "atltrace2.h"
#include <atldef2.h>
#include <atlenc.h>
#include <atlcrypt2.h>

#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#ifndef NS_SHARED_PTR
#define NS_SHARED_PTR boost
#endif

#define _ATL_APARTMENT_THREADED
// some CString constructors will be explicit
#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS
// turns off ATL's hiding of some common and often safely ignored warning messages
#define _ATL_ALL_WARNINGS

#include <atlbase.h>
#ifdef _WIN32
#include <atlcom.h>
#endif //_WIN32
#pragma warning (push)
#pragma warning (disable: 4127)
#include <atlstr.h>
#pragma warning (pop)
#include <errormsg.h>


#ifdef PHP_WIN32
#define PHP_COMPILER_ID "VC9"
#	define PHP_EXTNAME_API __declspec(dllexport)
#include "zend_config.w32.h" 
#elif defined(__GNUC__) && __GNUC__ >= 4
#	define PHP_EXTNAME_API __attribute__ ((visibility("default")))
#else
#	define PHP_EXTNAME_API
#endif
#ifndef UNIX
#pragma warning(push)
#pragma warning (disable:4005)
#endif
#ifdef ZTS
#include "TSRM.h"
#endif

#ifndef UNIX
#pragma warning (disable: 4127)
#endif
#include "php.h"
#include "php_ini.h"
#ifndef UNIX
#pragma warning(pop)
#endif
#include "zend_exceptions.h"

#define RETURN_ATL_STRING_W(atlstr)\
    {\
    char* str;\
    int len = 0;\
    len = atlstr.GetLength();\
    str = (char *)ecalloc(len + 1, sizeof(char));\
    wcstombs(str, atlstr, len);\
    str[len] = '\0';\
    RETURN_STRING(str);\
    }

#define RETURN_ATL_STRINGL_W(atlstr)\
    {\
    char* str;\
    int len = 0;\
    len = atlstr.GetLength();\
    str = (char *)ecalloc(len, sizeof(char));\
    wcstombs(str, atlstr, len);\
    RETURN_STRINGL(str, len);\
    }

#define RETURN_ATL_STRING_A(atlstr)\
    {\
    char* str;\
    int len = 0;\
    len = atlstr.GetLength();\
    str = (char *)ecalloc(len + 1, sizeof(char));\
    memcpy(str, atlstr, len);\
    str[len] = '\0';\
    RETURN_STRING(str);\
    }

#define RETURN_ATL_STRINGL_A(atlstr)\
    {\
    char* str;\
    int len = 0;\
    len = atlstr.GetLength();\
    str = (char *)ecalloc(len, sizeof(char));\
    memcpy(str, atlstr, len);\
    RETURN_STRINGL(str, len);\
    }

#define RETURN_PROXY_STRING(prstr)\
    {\
    char* str;\
    int len = 0;\
    len = strlen(prstr.c_str());\
    str = (char *)ecalloc(len + 1, sizeof(char));\
    strncpy(str, prstr.c_str(), len + 1);\
    RETURN_STRING(str);\
    }

#ifdef UNIX //разные макросы ибо на линуксе нет  _vscwprintf() который нужен внутри AppendFormat().

#ifdef MAKELANGID
    #undef MAKELANGID
#endif //MAKELANGID

#define MAKELANGID(a,b) 0x409 //English U.S.

#define RETURN_WITH_EXCEPTION(err)	                                \
    do {								\
        CAtlStringW message = GetErrorMessage(HRESULT_FROM_WIN32(err),	\
	    MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US));              \
        wchar_t buff[14];                                               \
        swprintf(buff, 14, L" (0x%08X)", err);                          \
        message.Append(buff);                                           \
        zend_throw_exception(zend_exception_get_default(), CW2A(message, CP_UTF8), err );\
        RETURN_FALSE;\
        } while (0)

#else
#define RETURN_WITH_EXCEPTION(err)	\
    do {								\
        CAtlStringW message = GetErrorMessage(HRESULT_FROM_WIN32(err),	\
	    MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US));              \
        message.AppendFormat(L" (0x%08X)", err);                        \
        zend_throw_exception(zend_exception_get_default(), CW2A(message, CP_UTF8), err );\
        RETURN_FALSE;\
        } while (0)

#endif //UNIX

#define HR_ERRORCHECK_RETURN(expr)		\
    __pragma(warning(push))			\
    __pragma(warning(disable: 4127))		\
    do {					\
	HRESULT stdafx_hr = (expr);		\
	if(stdafx_hr != S_OK)			\
	{					\
	    RETURN_WITH_EXCEPTION(stdafx_hr);	\
	}					\
    } while (0)					\
    __pragma(warning(pop))


#ifdef ZTS
#define EXTNAME_G(v) TSRMG(extname_globals_id, zend_extname_globals *, v)
#else
#define EXTNAME_G(v) (extname_globals.v)
#endif

