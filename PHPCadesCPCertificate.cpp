#include "stdafx.h"
#include "PHPCadesCPCertificate.h"
#include "PHPCadesCPCertificates.h"
#include "PHPCadesCPKeyUsage.h"
#include "PHPCadesCPExtendedKeyUsage.h"
#include "PHPCadesCPPrivateKey.h"
#include "PHPCadesCPPublicKey.h"
#include "PHPCadesCPBasicConstraints.h"
#include "PHPCadesCPCertificateStatus.h"
using namespace CryptoPro::PKI::CAdES;

//Методы
PHP_METHOD(CPCertificate, __construct) {
    zend_object *zobj = Z_OBJ_P(getThis());
    certificate_obj *obj =
        (certificate_obj *)((char *)zobj - XtOffsetOf(certificate_obj, zobj));
    NS_SHARED_PTR::shared_ptr<CPPCadesCPCertificateObject> cert(
        new CPPCadesCPCertificateObject());
    obj->m_pCppCadesImpl = cert;
}

PHP_METHOD(CPCertificate, GetInfo) {
    CAtlString infoW;
    long lType;
    CAPICOM_CERT_INFO_TYPE Type;

    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &lType) ==
        FAILURE)
        RETURN_WITH_EXCEPTION(E_INVALIDARG);

    Type = (CAPICOM_CERT_INFO_TYPE)lType;

    zend_object *zobj = Z_OBJ_P(getThis());
    certificate_obj *obj =
        (certificate_obj *)((char *)zobj - XtOffsetOf(certificate_obj, zobj));
    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->GetInfo(Type, infoW));

    RETURN_ATL_STRING(infoW);
}

PHP_METHOD(CPCertificate, FindPrivateKey) {
    size_t len;
    char *str;

    if (zend_parse_parameters(ZEND_NUM_ARGS() , "|s", &str, &len) ==
        FAILURE) {
        RETURN_WITH_EXCEPTION(E_INVALIDARG);
    }

    zend_object *zobj = Z_OBJ_P(getThis());
    certificate_obj *obj =
        (certificate_obj *)((char *)zobj - XtOffsetOf(certificate_obj, zobj));

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->FindPrivateKey(CAtlString(str, len)));
}

PHP_METHOD(CPCertificate, HasPrivateKey) {
    BOOL has;

    zend_object *zobj = Z_OBJ_P(getThis());
    certificate_obj *obj =
        (certificate_obj *)((char *)zobj - XtOffsetOf(certificate_obj, zobj));

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->HasPrivateKey(&has));
    if (has) {
        RETURN_TRUE;
    }
    else {
        RETURN_FALSE;
    }
}

PHP_METHOD(CPCertificate, IsValid) {
    NS_SHARED_PTR::shared_ptr<CPPCadesCPCertificateStatusObject> stat(
        new CPPCadesCPCertificateStatusObject());

    zend_object *zobj = Z_OBJ_P(getThis());
    certificate_obj *obj =
        (certificate_obj *)((char *)zobj - XtOffsetOf(certificate_obj, zobj));

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->IsValid(stat));

    object_init_ex(return_value, certstat_ce);
    zobj = Z_OBJ_P(return_value);
    certstat_obj *cstat =
        (certstat_obj *)((char *)zobj - XtOffsetOf(certstat_obj, zobj));
    cstat->m_pCppCadesImpl = stat;
}

PHP_METHOD(CPCertificate, KeyUsage) {
    zend_object *zobj = Z_OBJ_P(getThis());
    certificate_obj *obj =
        (certificate_obj *)((char *)zobj - XtOffsetOf(certificate_obj, zobj));

    object_init_ex(return_value, ku_ce);
    zobj = Z_OBJ_P(return_value);
    ku_obj *kobj =
        (ku_obj *)((char *)zobj - XtOffsetOf(ku_obj, zobj));

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->KeyUsage(kobj->m_pCppCadesImpl));
}

PHP_METHOD(CPCertificate, ExtendedKeyUsage) {
    zend_object *zobj = Z_OBJ_P(getThis());
    certificate_obj *obj =
        (certificate_obj *)((char *)zobj - XtOffsetOf(certificate_obj, zobj));

    object_init_ex(return_value, exku_ce);
    zobj = Z_OBJ_P(return_value);
    exku_obj *exkobj =
        (exku_obj *)((char *)zobj - XtOffsetOf(exku_obj, zobj));

    HR_ERRORCHECK_RETURN(
        obj->m_pCppCadesImpl->ExtendedKeyUsage(exkobj->m_pCppCadesImpl));
}

PHP_METHOD(CPCertificate, Export) {
    CryptoPro::CBlob value;
    int len;
    char *str;
    long lType;
    CAPICOM_ENCODING_TYPE Type;

    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &lType) ==
        FAILURE) {
        RETURN_WITH_EXCEPTION(E_INVALIDARG);
    }

    Type = (CAPICOM_ENCODING_TYPE)lType;

    zend_object *zobj = Z_OBJ_P(getThis());
    certificate_obj *obj =
        (certificate_obj *)((char *)zobj - XtOffsetOf(certificate_obj, zobj));

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->Export(Type, value));

    len = value.cbData();
    str = (char *)ecalloc(len, sizeof(char));
    memcpy(str, value.pbData(), len);

    RETURN_STRINGL(str, len - 2); //удаляем перевод строки иначе php будет мусор оставлять в переменных
}

PHP_METHOD(CPCertificate, Import) {
    CryptoPro::CBlob value;
    size_t len;
    char *str;

    if (zend_parse_parameters(ZEND_NUM_ARGS() , "s", &str, &len) ==
        FAILURE) {
        RETURN_WITH_EXCEPTION(E_INVALIDARG);
    }

    value.assign((unsigned char *)str, len);

    zend_object *zobj = Z_OBJ_P(getThis());
    certificate_obj *obj =
        (certificate_obj *)((char *)zobj - XtOffsetOf(certificate_obj, zobj));

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->Import(value));
}

PHP_METHOD(CPCertificate, get_SerialNumber) {
    CAtlString numberW;

    zend_object *zobj = Z_OBJ_P(getThis());
    certificate_obj *obj =
        (certificate_obj *)((char *)zobj - XtOffsetOf(certificate_obj, zobj));

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_SerialNumber(numberW));
    RETURN_ATL_STRING(numberW);
}

PHP_METHOD(CPCertificate, get_Thumbprint) {
    CAtlString thumbprW;

    zend_object *zobj = Z_OBJ_P(getThis());
    certificate_obj *obj =
        (certificate_obj *)((char *)zobj - XtOffsetOf(certificate_obj, zobj));

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_Thumbprint(thumbprW));
    RETURN_ATL_STRING(thumbprW);
}

PHP_METHOD(CPCertificate, get_SubjectName) {
    CAtlString nameW;

    zend_object *zobj = Z_OBJ_P(getThis());
    certificate_obj *obj =
        (certificate_obj *)((char *)zobj - XtOffsetOf(certificate_obj, zobj));

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_SubjectName(nameW));
    RETURN_ATL_STRING(nameW);
}

PHP_METHOD(CPCertificate, get_IssuerName) {
    CAtlString nameW;

    zend_object *zobj = Z_OBJ_P(getThis());
    certificate_obj *obj =
        (certificate_obj *)((char *)zobj - XtOffsetOf(certificate_obj, zobj));

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_IssuerName(nameW));
    RETURN_ATL_STRING(nameW);
}

PHP_METHOD(CPCertificate, get_Version) {
    DWORD version;

    zend_object *zobj = Z_OBJ_P(getThis());
    certificate_obj *obj =
        (certificate_obj *)((char *)zobj - XtOffsetOf(certificate_obj, zobj));

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_Version(&version));
    RETURN_LONG(version);
}

PHP_METHOD(CPCertificate, get_ValidToDate) {
    CryptoPro::CDateTime date;
    CryptoPro::CStringProxy strpr;

    zend_object *zobj = Z_OBJ_P(getThis());
    certificate_obj *obj =
        (certificate_obj *)((char *)zobj - XtOffsetOf(certificate_obj, zobj));

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_ValidToDate(date));
    strpr = date.tostring();
    RETURN_PROXY_STRING(strpr);
}

PHP_METHOD(CPCertificate, get_ValidFromDate) {
    CryptoPro::CDateTime date;
    CryptoPro::CStringProxy strpr;

    zend_object *zobj = Z_OBJ_P(getThis());
    certificate_obj *obj =
        (certificate_obj *)((char *)zobj - XtOffsetOf(certificate_obj, zobj));

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_ValidFromDate(date));
    strpr = date.tostring();
    RETURN_PROXY_STRING(strpr);
}

PHP_METHOD(CPCertificate, PrivateKey) {
    zend_object *zobj = Z_OBJ_P(getThis());
    certificate_obj *obj =
        (certificate_obj *)((char *)zobj - XtOffsetOf(certificate_obj, zobj));

    object_init_ex(return_value, private_key_ce);
    zobj = Z_OBJ_P(return_value);
    private_key_obj *kobj =
        (private_key_obj *)((char *)zobj - XtOffsetOf(private_key_obj, zobj));

    HR_ERRORCHECK_RETURN(
        obj->m_pCppCadesImpl->PrivateKey(kobj->m_pCppCadesImpl));
}

PHP_METHOD(CPCertificate, PublicKey) {
    zend_object *zobj = Z_OBJ_P(getThis());
    certificate_obj *obj =
        (certificate_obj *)((char *)zobj - XtOffsetOf(certificate_obj, zobj));

    object_init_ex(return_value, public_key_ce);
    zobj = Z_OBJ_P(return_value);
    public_key_obj *kobj =
        (public_key_obj *)((char *)zobj - XtOffsetOf(public_key_obj, zobj));

    HR_ERRORCHECK_RETURN(
        obj->m_pCppCadesImpl->PublicKey(kobj->m_pCppCadesImpl));
}

PHP_METHOD(CPCertificate, BasicConstraints) {
    zend_object *zobj = Z_OBJ_P(getThis());
    certificate_obj *obj =
        (certificate_obj *)((char *)zobj - XtOffsetOf(certificate_obj, zobj));

    object_init_ex(return_value, basic_constr_ce);
    zobj = Z_OBJ_P(return_value);
    basic_constr_obj *bcobj = (basic_constr_obj *)((char *)zobj - XtOffsetOf(basic_constr_obj, zobj));

    HR_ERRORCHECK_RETURN(
        obj->m_pCppCadesImpl->BasicConstraints(bcobj->m_pCppCadesImpl));
}

//Вспомогательные функции обертки
zend_object_handlers certificate_obj_handlers;
zend_class_entry *cert_ce;

static void cert_free(zend_object *object ) {
    certificate_obj *obj = (certificate_obj *)((char *)object - XtOffsetOf(certificate_obj, zobj));
    obj->m_pCppCadesImpl.reset();

    zend_object_std_dtor(object);
}

static zend_object* cert_create_handler(zend_class_entry *ce ) {
    certificate_obj *obj = (certificate_obj *)emalloc(sizeof(certificate_obj) + zend_object_properties_size(ce));
    memset(obj, 0, sizeof(certificate_obj) + zend_object_properties_size(ce));
    
    zend_object_std_init(&obj->zobj, ce);
    object_properties_init(&obj->zobj, ce);
    obj->zobj.handlers = &certificate_obj_handlers;

    return &obj->zobj;
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpcertificate_construct, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpcertificate_getinfo, 0, 0, 1)
 ZEND_ARG_INFO(0, type)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpcertificate_findprivatekey, 0, 0, 0)
 ZEND_ARG_INFO(0, criteria_reserved)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpcertificate_hasprivatekey, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpcertificate_isvalid, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpcertificate_extendedkeyusage, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpcertificate_keyusage, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpcertificate_export, 0, 0, 1)
 ZEND_ARG_INFO(0, encodingtype)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpcertificate_import, 0, 0, 1)
 ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpcertificate_get_serialnumber, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpcertificate_get_thumbprint, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpcertificate_get_subjectname, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpcertificate_get_issuername, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpcertificate_get_version, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpcertificate_get_validtodate, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpcertificate_get_validfromdate, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpcertificate_get_basicconstraints, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpcertificate_get_publickey, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpcertificate_get_privatekey, 0, 0, 0)
ZEND_END_ARG_INFO()

//связывание методов класса в function entry
zend_function_entry cert_methods[] = {
    PHP_ME(CPCertificate, __construct, arginfo_cpcertificate_construct, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
    PHP_ME(CPCertificate, GetInfo, arginfo_cpcertificate_getinfo, ZEND_ACC_PUBLIC)
    PHP_ME(CPCertificate, FindPrivateKey, arginfo_cpcertificate_findprivatekey, ZEND_ACC_PUBLIC)
    PHP_ME(CPCertificate, HasPrivateKey, arginfo_cpcertificate_hasprivatekey, ZEND_ACC_PUBLIC)
    PHP_ME(CPCertificate, IsValid, arginfo_cpcertificate_isvalid, ZEND_ACC_PUBLIC)
    PHP_ME(CPCertificate, ExtendedKeyUsage, arginfo_cpcertificate_extendedkeyusage, ZEND_ACC_PUBLIC)
    PHP_ME(CPCertificate, KeyUsage, arginfo_cpcertificate_keyusage, ZEND_ACC_PUBLIC)
    PHP_ME(CPCertificate, Export, arginfo_cpcertificate_export, ZEND_ACC_PUBLIC)
    PHP_ME(CPCertificate, Import, arginfo_cpcertificate_import, ZEND_ACC_PUBLIC)
    PHP_ME(CPCertificate, get_SerialNumber, arginfo_cpcertificate_get_serialnumber, ZEND_ACC_PUBLIC)
    PHP_ME(CPCertificate, get_Thumbprint, arginfo_cpcertificate_get_thumbprint, ZEND_ACC_PUBLIC)
    PHP_ME(CPCertificate, get_SubjectName, arginfo_cpcertificate_get_subjectname, ZEND_ACC_PUBLIC)
    PHP_ME(CPCertificate, get_IssuerName, arginfo_cpcertificate_get_issuername, ZEND_ACC_PUBLIC)
    PHP_ME(CPCertificate, get_Version, arginfo_cpcertificate_get_version, ZEND_ACC_PUBLIC)
    PHP_ME(CPCertificate, get_ValidToDate, arginfo_cpcertificate_get_validtodate, ZEND_ACC_PUBLIC)
    PHP_ME(CPCertificate, get_ValidFromDate, arginfo_cpcertificate_get_validfromdate, ZEND_ACC_PUBLIC)
    PHP_ME(CPCertificate, BasicConstraints, arginfo_cpcertificate_get_basicconstraints, ZEND_ACC_PUBLIC)
    PHP_ME(CPCertificate, PublicKey, arginfo_cpcertificate_get_publickey, ZEND_ACC_PUBLIC)
    PHP_ME(CPCertificate, PrivateKey, arginfo_cpcertificate_get_privatekey, ZEND_ACC_PUBLIC)
    {NULL, NULL, NULL}};

void cert_init(void) {
    zend_class_entry ce;
    INIT_CLASS_ENTRY(ce, "CPCertificate", cert_methods);
    cert_ce = zend_register_internal_class(&ce );
    cert_ce->create_object = cert_create_handler;
    memcpy(&certificate_obj_handlers, zend_get_std_object_handlers(),
           sizeof(zend_object_handlers));
    certificate_obj_handlers.clone_obj = NULL;
    certificate_obj_handlers.free_obj = cert_free;
    certificate_obj_handlers.offset = XtOffsetOf(certificate_obj, zobj);
}
