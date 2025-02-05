/*!
* \file $RCSfile$
* \version $Revision: 234279 $
* \date $Date:: 2021-10-26 16:40:10 +0300#$
* \author $Author: een $
*
* \brief Реализация форматирования сообщений об ошибках.
*
* Реализация форматирования сообщений об ошибках.
*/

#define IGNORE_LEGACY_FORMAT_MESSAGE_MSG

// Скопированы из "*_e.h"
#define FACILITY_TSPCLI                  0x210
#define FACILITY_OCSPCLI                 0x211
#define FACILITY_TSPSRV                  0x212
#define FACILITY_OCSPSRV                 0x213

#ifdef UNIX
#   include <string>
#   include <locale.h>
#   include "CSP_WinDef.h"
#   include "CSP_WinError.h"
#   include "ocspcli_e.h"
#   include "tspcli_e.h"
#else //_WIN32

#   define STRICT // Для более строгой типизации. Не верить заявлениям MS, что
          // в Visual C++ STRICT определено по умолчанию.
#   define WIN32_LEAN_AND_MEAN // Для ускорения компиляции
#   define _WIN32_WINNT 0x0501 // Должно работать начиная с XP

// Для ActCtx.h
#define ISOLATION_AWARE_ENABLED 1

#include <windows.h>
#include <ole2.h>
#include <lmerr.h>
#include <lmcons.h>
#include <activeds.h>
#include <ActCtx.h>

#endif //_WIN32

#ifndef UNIX
#pragma warning (push)
#pragma warning (disable:4838)
#endif
#include <atlstr.h>
#ifndef UNIX
#pragma warning (pop)
#endif
#include "errormsg.h"

static LPCWSTR eng_wrong_name = L"Wrong name format or an attempt is made to open container of another CSP.";
// Кодирование можно посмотреть в файле \trunk\CSP\capilite\CryptFindOIDInfo.cpp
// rus_wrong_name = L"Неверный формат имени или попытка открыть контейнер другого криптопровайдера.";
static LPCWSTR rus_wrong_name = L"\x41d\x435\x432\x435\x440\x43d\x44b\x439 \x444\x43e\x440\x43c\x430\x442 \x438\x43c\x435\x43d\x438 \x438\x43b\x438 \x43f\x43e\x43f\x44b\x442\x43a\x430 \x43e\x442\x43a\x440\x44b\x442\x44c \x43a\x43e\x43d\x442\x435\x439\x43d\x435\x440 \x434\x440\x443\x433\x43e\x433\x43e \x43a\x440\x438\x43f\x442\x43e\x43f\x440\x43e\x432\x430\x439\x434\x435\x440\x430.";


#ifndef UNIX
inline void _trimrigth(LPTSTR szBuf, LPCTSTR pszTargets);

static BOOL MakeOurMessage(HRESULT hr, LPWSTR szBuf, DWORD chBufLen, DWORD dwLangId)
{
    if (hr == SCARD_E_CARD_UNSUPPORTED) {
    LPCWSTR wrong_name_text;
    if (PRIMARYLANGID(dwLangId) == LANG_RUSSIAN)
        wrong_name_text = rus_wrong_name;
    else
        wrong_name_text = eng_wrong_name;
    _tcsncpy(szBuf, wrong_name_text, chBufLen - 1);
    return TRUE;
    }
    return FALSE;
}

BOOL GetErrorMessage(
    HRESULT hr, LPTSTR szBuf, DWORD chBufLen, DWORD dwLangId)
{
    static CryptoPro::ActCtx::CActCtxHandle actCtxAssociated;

    if (!chBufLen)
    {
        return FALSE;
    }
    szBuf[0] = 0;
    HMODULE hInst = 0;
    DWORD dwFacility = HRESULT_FACILITY(hr);
    switch (dwFacility) {
    case FACILITY_TSPCLI:
        {
            CryptoPro::ActCtx::CActCtxActivator activator(actCtxAssociated);
            hInst = ::GetModuleHandle(TEXT("tspcli.dll"));
            if (hInst)
            {
                break;
            }
            hInst = ::GetModuleHandle(TEXT("cades.dll"));
            if (hInst)
            {
                //TODO: Если конструктор выбросит исключение, то здесь случится
                //полная фигня.
                static CryptoPro::ActCtx::CActCtxHandle actCtxCadesDll(hInst);
                CryptoPro::ActCtx::CActCtxActivator activatorCadesDll(actCtxCadesDll);
                hInst = ::GetModuleHandle(TEXT("tspcli.dll"));
            }
        }
        break;
    case FACILITY_OCSPCLI:
        {
            CryptoPro::ActCtx::CActCtxActivator activator(actCtxAssociated);
            hInst = ::GetModuleHandle(TEXT("ocspcli.dll"));
            if (hInst)
            {
                break;
            }
            hInst = ::GetModuleHandle(TEXT("cades.dll"));
            if (hInst)
            {
                //TODO: Если конструктор выбросит исключение, то здесь случится
                //полная фигня.
                static CryptoPro::ActCtx::CActCtxHandle actCtxCadesDll(hInst);
                CryptoPro::ActCtx::CActCtxActivator activatorCadesDll(actCtxCadesDll);
                hInst = ::GetModuleHandle(TEXT("ocspcli.dll"));
            }
        }
        break;
    case FACILITY_MSMQ:
        hInst = ::GetModuleHandle(TEXT("mqutil.dll"));
        break;
    case FACILITY_ITF:
        hInst = ::GetModuleHandle(TEXT("oledb32r.dll"));
        break;
    }

    if (!hInst
        && (dwFacility == FACILITY_TSPCLI || dwFacility == FACILITY_OCSPCLI))
    {
        // Для наших кодов ошибок попробуем найти сообщение в модуле,
        // содержащем данный исполняемый код. Например, cadescom.dll
        // получит сообщение именно таким путём.
        //
        // В качестве адреса в GetModuleHandleEx(
        // GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS) передаём адрес литерала,
        // который гарантированно будет в адресном пространстве данного
        // модуля. Код вовзрата намеренно игнорируем, т.к. нам достаточно
        // того, что в hInst останется 0.
        ::GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS
            | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, _T(" "), &hInst);
    }

    DWORD dwCode = HRESULT_CODE(hr);
    if (!hInst)
    {
    if (dwCode >= NERR_BASE && dwCode <= MAX_NERR)
    {
        hInst = ::GetModuleHandle(MESSAGE_FILENAME);
    }
    }
    BOOL dwRet = FALSE;
    DWORD dwFlagsMod = FORMAT_MESSAGE_IGNORE_INSERTS | FORMAT_MESSAGE_FROM_HMODULE;

    dwRet = MakeOurMessage(hr, szBuf, chBufLen, dwLangId);
    if (!dwRet) {
    if (hInst) {
        dwRet = FormatMessage(dwFlagsMod, hInst, hr, dwLangId, szBuf, chBufLen, NULL);
        // Если не нашли сообщение в конкретно заданном языке,
        // спросим в языке 0 (будет поиск по разным системным языкам)
        if (!dwRet && dwLangId)
        dwRet = FormatMessage(dwFlagsMod, hInst, hr, 0, szBuf, chBufLen, NULL);
        hInst = 0;
    }
    }
    DWORD dwFlagsSys = FORMAT_MESSAGE_IGNORE_INSERTS | FORMAT_MESSAGE_FROM_SYSTEM;
    if (!dwRet) {
    dwRet = FormatMessage(dwFlagsSys, 0, hr, dwLangId, szBuf, chBufLen, NULL);
    // Если не нашли сообщение в конкретно заданном языке,
    // спросим в языке 0 (будет поиск по разным системным языкам)
    if (!dwRet && dwLangId)
        dwRet = FormatMessage(dwFlagsSys, 0, hr, 0, szBuf, chBufLen, NULL);
    }
    if (!dwRet)
    {
    hInst = ::GetModuleHandle(TEXT("winhttp.dll"));
    if (hInst)
    {
        // Тут используем dwCode, а не полный hr!
        dwRet = FormatMessage(dwFlagsMod, hInst, dwCode, dwLangId, szBuf, chBufLen, NULL);
        // Если не нашли сообщение в конкретно заданном языке,
        // спросим в языке 0 (будет поиск по разным системным языкам)
        if (!dwRet && dwLangId)
        dwRet = FormatMessage(dwFlagsMod, hInst, dwCode, 0, szBuf, chBufLen, NULL);
    }
    }
    if (!dwRet)
    {
    hInst = ::GetModuleHandle(TEXT("ntdsbmsg.dll"));
    if (hInst)
    {
        dwRet = FormatMessage(dwFlagsMod, hInst, hr, dwLangId, szBuf, chBufLen, NULL);
        // Если не нашли сообщение в конкретно заданном языке,
        // спросим в языке 0 (будет поиск по разным системным языкам)
        if (!dwRet && dwLangId)
        dwRet = FormatMessage(dwFlagsMod, hInst, hr, 0, szBuf, chBufLen, NULL);
    }
    }
    if (!dwRet)
    {
    hInst = ::GetModuleHandle(TEXT("wininet.dll"));
    if (hInst)
    {
        dwRet = FormatMessage(dwFlagsMod, hInst, hr, dwLangId, szBuf, chBufLen, NULL);
        // Если не нашли сообщение в конкретно заданном языке,
        // спросим в языке 0 (будет поиск по разным системным языкам)
        if (!dwRet && dwLangId)
        dwRet = FormatMessage(dwFlagsMod, hInst, hr, 0, szBuf, chBufLen, NULL);
    }
    }
    if (!dwRet && hr >= 0x80005000 && hr < 0x80006000) {
    switch(hr) {
#define ADSERROR(x) case x: _tcsncpy_s(szBuf, chBufLen, _T(#x), _TRUNCATE); dwRet = TRUE; break
        ADSERROR(E_ADS_BAD_PATHNAME);
        ADSERROR(E_ADS_INVALID_DOMAIN_OBJECT);
        ADSERROR(E_ADS_INVALID_USER_OBJECT);
        ADSERROR(E_ADS_INVALID_COMPUTER_OBJECT);
        ADSERROR(E_ADS_UNKNOWN_OBJECT);
        ADSERROR(E_ADS_PROPERTY_NOT_SET);
        ADSERROR(E_ADS_PROPERTY_NOT_SUPPORTED);
        ADSERROR(E_ADS_PROPERTY_INVALID);
        ADSERROR(E_ADS_BAD_PARAMETER);
        ADSERROR(E_ADS_OBJECT_UNBOUND);
        ADSERROR(E_ADS_PROPERTY_NOT_MODIFIED);
        ADSERROR(E_ADS_PROPERTY_MODIFIED);
        ADSERROR(E_ADS_CANT_CONVERT_DATATYPE);
        ADSERROR(E_ADS_PROPERTY_NOT_FOUND);
        ADSERROR(E_ADS_OBJECT_EXISTS);
        ADSERROR(E_ADS_SCHEMA_VIOLATION);
        ADSERROR(E_ADS_COLUMN_NOT_SET);
        ADSERROR(E_ADS_INVALID_FILTER);
#undef ADSERROR
    }
    }
    if (dwRet && szBuf[0])
    _trimrigth(szBuf, _T("\r\n"));
    if (dwFacility == FACILITY_WIN32 || hr >= 0x80005000 && hr < 0x80006000)
    {
    WCHAR szExtErr[256];
    WCHAR szProv[256];
    LPCTSTR szFormat;
    if (szBuf[0])
        szFormat = _T(" [%ws, #%d (%ws)]");
    else
        szFormat = _T("ADs [%ws, #%d (%ws)]");
    // Get extended error value.
    hInst = ::GetModuleHandle(TEXT("activeds.dll"));
    if (hInst)
    {
        typedef HRESULT (WINAPI *LPADSGETLASTERROR)
        (LPDWORD, LPWSTR, DWORD, LPWSTR, DWORD);
        LPADSGETLASTERROR lpADsGetLastError = LPADSGETLASTERROR(
        GetProcAddress(hInst, "ADsGetLastError"));
        if (lpADsGetLastError != NULL) {
        hr = lpADsGetLastError( &dwCode, szExtErr, 256, szProv, 256);
        if (SUCCEEDED(hr) && dwCode != 0) {
            TCHAR szFormattedBuf[MAX_PATH];
            if (_stprintf_s(szFormattedBuf, MAX_PATH,
            szFormat, szProv, dwCode, szExtErr) > 0)
            if (!_tcsncat_s(szBuf, chBufLen, szFormattedBuf,
                _TRUNCATE))
                dwRet = TRUE;
        }
        }
    }
    }
    return dwRet ? TRUE : FALSE;
}

void _trimrigth(LPTSTR szBuf, LPCTSTR pszTargets)
{
    // if we're not trimming anything, we're not doing any work
    if( (pszTargets == NULL) || (*pszTargets == 0) )
    return;
    // find beginning of trailing matches
    // by starting at beginning
    LPCTSTR psz = szBuf;
    LPCTSTR pszLast = NULL;
    while (*psz != 0) {
    if (_tcschr( pszTargets, *psz ) != NULL) {
        if (pszLast == NULL)
        pszLast = psz;
    } else
        pszLast = NULL;
    psz = psz + 1;
    }
    if (pszLast != NULL ) {
    // truncate at left-most matching character
    int iLast = int(pszLast - szBuf);
    szBuf[iLast] = 0;
    }
}

const ATL::CAtlStringW GetErrorMessage(HRESULT hr, DWORD dwLangId)
{
    ATL::CAtlString sBuf;
    TCHAR *szBuf = sBuf.GetBuffer(1024);
    BOOL res = GetErrorMessage(hr, szBuf, 1024, dwLangId);
    sBuf.ReleaseBuffer();
    if (!res)
        sBuf.AppendFormat(L"Unknown error code (0x%08X)", hr);

    return sBuf;
}
#else //UNIX

typedef enum _CAPICOM_ERROR_CODE
{
    CAPICOM_E_ENCODE_INVALID_TYPE   = 0x80880100,
    CAPICOM_E_EKU_INVALID_OID   = 0x80880200,
    CAPICOM_E_EKU_OID_NOT_INITIALIZED   = 0x80880201,
    CAPICOM_E_CERTIFICATE_NOT_INITIALIZED   = 0x80880210,
    CAPICOM_E_CERTIFICATE_NO_PRIVATE_KEY    = 0x80880211,
    CAPICOM_E_CHAIN_NOT_BUILT   = 0x80880220,
    CAPICOM_E_STORE_NOT_OPENED  = 0x80880230,
    CAPICOM_E_STORE_EMPTY   = 0x80880231,
    CAPICOM_E_STORE_INVALID_OPEN_MODE   = 0x80880232,
    CAPICOM_E_STORE_INVALID_SAVE_AS_TYPE    = 0x80880233,
    CAPICOM_E_ATTRIBUTE_NAME_NOT_INITIALIZED    = 0x80880240,
    CAPICOM_E_ATTRIBUTE_VALUE_NOT_INITIALIZED   = 0x80880241,
    CAPICOM_E_ATTRIBUTE_INVALID_NAME    = 0x80880242,
    CAPICOM_E_ATTRIBUTE_INVALID_VALUE   = 0x80880243,
    CAPICOM_E_SIGNER_NOT_INITIALIZED    = 0x80880250,
    CAPICOM_E_SIGNER_NOT_FOUND  = 0x80880251,
    CAPICOM_E_SIGNER_NO_CHAIN   = 0x80880252,
    CAPICOM_E_SIGNER_INVALID_USAGE  = 0x80880253,
    CAPICOM_E_SIGN_NOT_INITIALIZED  = 0x80880260,
    CAPICOM_E_SIGN_INVALID_TYPE = 0x80880261,
    CAPICOM_E_SIGN_NOT_SIGNED   = 0x80880262,
    CAPICOM_E_INVALID_ALGORITHM = 0x80880270,
    CAPICOM_E_INVALID_KEY_LENGTH    = 0x80880271,
    CAPICOM_E_ENVELOP_NOT_INITIALIZED   = 0x80880280,
    CAPICOM_E_ENVELOP_INVALID_TYPE  = 0x80880281,
    CAPICOM_E_ENVELOP_NO_RECIPIENT  = 0x80880282,
    CAPICOM_E_ENVELOP_RECIPIENT_NOT_FOUND   = 0x80880283,
    CAPICOM_E_ENCRYPT_NOT_INITIALIZED   = 0x80880290,
    CAPICOM_E_ENCRYPT_INVALID_TYPE  = 0x80880291,
    CAPICOM_E_ENCRYPT_NO_SECRET = 0x80880292,
    CAPICOM_E_NOT_SUPPORTED = 0x80880900,
    CAPICOM_E_UI_DISABLED   = 0x80880901,
    CAPICOM_E_CANCELLED = 0x80880902,
    CAPICOM_E_NOT_ALLOWED   = 0x80880903,
    CAPICOM_E_OUT_OF_RESOURCE   = 0x80880904,
    CAPICOM_E_INTERNAL  = 0x80880911,
    CAPICOM_E_UNKNOWN   = 0x80880999,
    CAPICOM_E_PRIVATE_KEY_NOT_INITIALIZED   = 0x80880300,
    CAPICOM_E_PRIVATE_KEY_NOT_EXPORTABLE    = 0x80880301,
    CAPICOM_E_ENCODE_NOT_INITIALIZED    = 0x80880320,
    CAPICOM_E_EXTENSION_NOT_INITIALIZED = 0x80880330,
    CAPICOM_E_PROPERTY_NOT_INITIALIZED  = 0x80880340,
    CAPICOM_E_FIND_INVALID_TYPE = 0x80880350,
    CAPICOM_E_FIND_INVALID_PREDEFINED_POLICY    = 0x80880351,
    CAPICOM_E_CODE_NOT_INITIALIZED  = 0x80880360,
    CAPICOM_E_CODE_NOT_SIGNED   = 0x80880361,
    CAPICOM_E_CODE_DESCRIPTION_NOT_INITIALIZED  = 0x80880362,
    CAPICOM_E_CODE_DESCRIPTION_URL_NOT_INITIALIZED  = 0x80880363,
    CAPICOM_E_CODE_INVALID_TIMESTAMP_URL    = 0x80880364,
    CAPICOM_E_HASH_NO_DATA  = 0x80880370,
    CAPICOM_E_INVALID_CONVERT_TYPE  = 0x80880380
} CAPICOM_ERROR_CODE;

static bool check_locale_is_russian(DWORD dwLangId)
{
    if (PRIMARYLANGID(dwLangId) == LANG_RUSSIAN) {
	return true;
    }
    if (PRIMARYLANGID(dwLangId) == LANG_NEUTRAL) {
	// copy paste from FormatMessage.cpp
	static const char *loc = setlocale(LC_MESSAGES, NULL);
	static bool is_russian_locale = (loc && strncmp(loc, "ru_RU", 5) == 0);

	return is_russian_locale;
    }
    return false;
}

static BOOL MakeOurMessage(HRESULT hr, DWORD dwLangId, ATL::CAtlStringW& strRet)
{
    if (hr == SCARD_E_CARD_UNSUPPORTED) {
	if (check_locale_is_russian(dwLangId)) {
	    strRet = rus_wrong_name;
	}
	else {
	    strRet = eng_wrong_name;
	}
	return TRUE;
    }
    return FALSE;
}


const ATL::CAtlStringW GetErrorMessage(HRESULT hr, DWORD dwLangId)
{
    ATL::CAtlStringW ret;
    WCHAR *szBuf = ret.GetBuffer(1024);
    DWORD res = FormatMessageW(FORMAT_MESSAGE_IGNORE_INSERTS, 0, hr, dwLangId, szBuf, 1024, NULL);
    ret.ReleaseBuffer();
    if (res != 0) {
	ATL::CAtlStringW ourRet;
	if (MakeOurMessage(hr, dwLangId, ourRet)) {
	    return ourRet;
	}

	return ret;
    }

    bool bRussian = check_locale_is_russian(dwLangId);
    switch(hr){
        case (HRESULT)CAPICOM_E_STORE_NOT_OPENED:
	    if (bRussian) {
		// Объект Store не был инициализирован.
		ret = L"\x41e\x431\x44a\x435\x43a\x442 Store \x43d\x435 \x431\x44b\x43b \x438\x43d\x438\x446\x438\x430\x43b\x438\x437\x438\x440\x43e\x432\x430\x43d.";
	    }
	    else {
		ret = L"The Store object does not represent an opened certificate store.";
	    }
            break;
        case (HRESULT)NS_E_CURL_INVALIDSCHEME: 
	    if (bRussian) {
		// URL-адрес содержит некорректную схему.
		ret = L"URL-\x430\x434\x440\x435\x441 \x441\x43e\x434\x435\x440\x436\x438\x442 \x43d\x435\x43a\x43e\x440\x440\x435\x43a\x442\x43d\x443\x44e \x441\x445\x435\x43c\x443.";
	    }
	    else {
		ret = L"The URL contains an invalid scheme.";
	    }
            break;
        default:
	    if (bRussian) {
		// Внутренняя ошибка
		ret = L"\x412\x43d\x443\x442\x440\x435\x43d\x43d\x44f\x44f \x43e\x448\x438\x431\x43a\x430.";
	    }
	    else {
		ret = L"Internal error.";
	    }
            break;
    }
    return ret;
}
#endif //UNIX
