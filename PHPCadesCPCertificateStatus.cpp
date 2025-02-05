#include "stdafx.h"
#include "PHPCadesCPCertificateStatus.h"
#include "PHPCadesCPCertificates.h"
#include "PHPCadesCPOID.h"
#include "PHPCadesCPEKU.h"
using namespace CryptoPro::PKI::CAdES;

PHP_METHOD(CPCertificateStatus, __construct) {
    zend_object *zobj = Z_OBJ_P(getThis());
    certstat_obj *obj =
        (certstat_obj *)((char *)zobj - XtOffsetOf(certstat_obj, zobj));
    obj->m_pCppCadesImpl = NS_SHARED_PTR::shared_ptr<CPPCadesCPCertificateStatusObject>(
        new CPPCadesCPCertificateStatusObject());
}

PHP_METHOD(CPCertificateStatus, get_Result) {
    BOOL res;
    zend_object *zobj = Z_OBJ_P(getThis());
    certstat_obj *obj =
        (certstat_obj *)((char *)zobj - XtOffsetOf(certstat_obj, zobj));

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_Result(&res));

    RETURN_LONG(res);
}

PHP_METHOD(CPCertificateStatus, get_CheckFlag) {
    CAPICOM_CHECK_FLAG flag;
    zend_object *zobj = Z_OBJ_P(getThis());
    certstat_obj *obj =
        (certstat_obj *)((char *)zobj - XtOffsetOf(certstat_obj, zobj));

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_CheckFlag(&flag));

    RETURN_LONG(flag);
}

PHP_METHOD(CPCertificateStatus, set_CheckFlag) {
    long lFlag;
    CAPICOM_CHECK_FLAG Flag;

    zend_object *zobj = Z_OBJ_P(getThis());
    certstat_obj *obj =
        (certstat_obj *)((char *)zobj - XtOffsetOf(certstat_obj, zobj));

    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &lFlag) ==
        FAILURE)
        RETURN_WITH_EXCEPTION(E_INVALIDARG);

    Flag = (CAPICOM_CHECK_FLAG)lFlag;

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->put_CheckFlag(Flag));
}

PHP_METHOD(CPCertificateStatus, EKU) {
    NS_SHARED_PTR::shared_ptr<CPPCadesCPEKUObject> ptr(new CPPCadesCPEKUObject());

    zend_object *zobj = Z_OBJ_P(getThis());
    certstat_obj *obj =
        (certstat_obj *)((char *)zobj - XtOffsetOf(certstat_obj, zobj));

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->EKU(ptr));

    object_init_ex(return_value, eku_ce);
    zobj = Z_OBJ_P(return_value);
    eku_obj *eobj =
        (eku_obj *)((char *)zobj - XtOffsetOf(eku_obj, zobj));

    eobj->m_pCppCadesImpl = ptr;
}

PHP_METHOD(CPCertificateStatus, get_VerificationTime) {
    CryptoPro::CDateTime time;
    CryptoPro::CStringProxy strpr;

    zend_object *zobj = Z_OBJ_P(getThis());
    certstat_obj *obj =
        (certstat_obj *)((char *)zobj - XtOffsetOf(certstat_obj, zobj));

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_VerificationTime(time));

    strpr = time.tostring();
    RETURN_PROXY_STRING(strpr)
}

PHP_METHOD(CPCertificateStatus, set_VerificationTime) {
    CryptoPro::CDateTime time;
    char *str;
    size_t len;

    zend_object *zobj = Z_OBJ_P(getThis());
    certstat_obj *obj =
        (certstat_obj *)((char *)zobj - XtOffsetOf(certstat_obj, zobj));

    if (zend_parse_parameters(ZEND_NUM_ARGS() , "s", &str, &len) ==
        FAILURE)
        RETURN_WITH_EXCEPTION(E_INVALIDARG);

    try {
        time = CryptoPro::CDateTime(str);
        HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->put_VerificationTime(time));
    } catch (...) {
        RETURN_WITH_EXCEPTION(E_INVALIDARG);
    }
}

PHP_METHOD(CPCertificateStatus, set_UrlRetrievalTimeout) {
    long urt;

    zend_object *zobj = Z_OBJ_P(getThis());
    certstat_obj *obj =
        (certstat_obj *)((char *)zobj - XtOffsetOf(certstat_obj, zobj));

    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &urt) == FAILURE)
        RETURN_WITH_EXCEPTION(E_INVALIDARG);

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->put_UrlRetrievalTimeout(urt));
}

PHP_METHOD(CPCertificateStatus, get_UrlRetrievalTimeout) {
    long urt;

    zend_object *zobj = Z_OBJ_P(getThis());
    certstat_obj *obj =
        (certstat_obj *)((char *)zobj - XtOffsetOf(certstat_obj, zobj));

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_UrlRetrievalTimeout(&urt));

    RETURN_LONG(urt);
}

PHP_METHOD(CPCertificateStatus, CertificatePolicies) {
    NS_SHARED_PTR::shared_ptr<CPPCadesCPOIDsObject> oids(new CPPCadesCPOIDsObject());
    NS_SHARED_PTR::shared_ptr<CPPCadesCPOIDObject> oid;
    unsigned int count;
    zval *CPoid = new zval();

    zend_object *zobj = Z_OBJ_P(getThis());
    certstat_obj *obj =
        (certstat_obj *)((char *)zobj - XtOffsetOf(certstat_obj, zobj));

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->CertificatePolicies(oids));
    HR_ERRORCHECK_RETURN(oids->get_Count(&count));

    array_init(return_value);
    object_init_ex(CPoid, oid_ce);

    for (unsigned int i = 1; i <= count; i++) {
        HR_ERRORCHECK_RETURN(oids->get_Item(i, oid));
        zobj = Z_OBJ_P(CPoid);
        oid_obj *arg = (oid_obj *)((char *)zobj - XtOffsetOf(oid_obj, zobj));
        arg->m_pCppCadesImpl = oid;
        add_next_index_zval(CPoid, return_value);
    }
}

PHP_METHOD(CPCertificateStatus, ApplicationPolicies) {
    NS_SHARED_PTR::shared_ptr<CPPCadesCPOIDsObject> oids(new CPPCadesCPOIDsObject());
    NS_SHARED_PTR::shared_ptr<CPPCadesCPOIDObject> oid;
    unsigned int count;
    zval *CPoid = new zval();

    zend_object *zobj = Z_OBJ_P(getThis());
    certstat_obj *obj =
        (certstat_obj *)((char *)zobj - XtOffsetOf(certstat_obj, zobj));

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->ApplicationPolicies(oids));
    HR_ERRORCHECK_RETURN(oids->get_Count(&count));

    array_init(return_value);
    object_init_ex(CPoid, oid_ce);

    for (unsigned int i = 1; i <= count; i++) {
        HR_ERRORCHECK_RETURN(oids->get_Item(i, oid));
        zobj = Z_OBJ_P(CPoid);
        oid_obj *arg = (oid_obj *)((char *)zobj - XtOffsetOf(oid_obj, zobj));
        arg->m_pCppCadesImpl = oid;
        add_next_index_zval(CPoid, return_value);
    }
}

PHP_METHOD(CPCertificateStatus, get_ValidationCertificates) {
    NS_SHARED_PTR::shared_ptr<CPPCadesCPCertificatesObject> certs(
        new CPPCadesCPCertificatesObject());

    zend_object *zobj = Z_OBJ_P(getThis());
    certstat_obj *obj =
        (certstat_obj *)((char *)zobj - XtOffsetOf(certstat_obj, zobj));

    HR_ERRORCHECK_RETURN(
        obj->m_pCppCadesImpl->get_ValidationCertificates(certs));

    object_init_ex(return_value, certs_ce);
    zobj = Z_OBJ_P(return_value);
    certs_obj *cobj =
        (certs_obj *)((char *)zobj - XtOffsetOf(certs_obj, zobj));
    cobj->m_pCppCadesImpl = certs;
}

zend_object_handlers certstat_obj_handlers;
zend_class_entry *certstat_ce;

static void certstat_free(zend_object *object ) {
    certstat_obj *obj = (certstat_obj *)((char *)object - XtOffsetOf(certstat_obj, zobj));
    obj->m_pCppCadesImpl.reset();

    zend_object_std_dtor(object);
}

static zend_object* certstat_create_handler(zend_class_entry *ce ) {
    certstat_obj *obj = (certstat_obj *)emalloc(sizeof(certstat_obj) + zend_object_properties_size(ce));
    memset(obj, 0, sizeof(certstat_obj) + zend_object_properties_size(ce));
    
    zend_object_std_init(&obj->zobj, ce);
    object_properties_init(&obj->zobj, ce);
    obj->zobj.handlers = &certstat_obj_handlers;

    return &obj->zobj;
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpcertificatestatus_construct, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpcertificatestatus_get_result, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpcertificatestatus_get_checkflag, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpcertificatestatus_set_checkflag, 0, 0, 1)
 ZEND_ARG_INFO(0, checkflag)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpcertificatestatus_eku, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpcertificatestatus_get_verificationtime, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpcertificatestatus_set_verificationtime, 0, 0, 1)
 ZEND_ARG_INFO(0, time)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpcertificatestatus_get_urlretrievaltimeout, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpcertificatestatus_set_urlretrievaltimeout, 0, 0, 1)
 ZEND_ARG_INFO(0, timeout)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpcertificatestatus_certificatepolicies, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpcertificatestatus_applicationpolicies, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpcertificatestatus_get_validationcertificates, 0, 0, 0)
ZEND_END_ARG_INFO()

//связывание методов класса в function entry
zend_function_entry certstat_methods[] = {
    PHP_ME(CPCertificateStatus, __construct, arginfo_cpcertificatestatus_construct, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
    PHP_ME(CPCertificateStatus, get_Result, arginfo_cpcertificatestatus_get_result, ZEND_ACC_PUBLIC)
    PHP_ME(CPCertificateStatus, get_CheckFlag, arginfo_cpcertificatestatus_get_checkflag, ZEND_ACC_PUBLIC)
    PHP_ME(CPCertificateStatus, set_CheckFlag, arginfo_cpcertificatestatus_set_checkflag, ZEND_ACC_PUBLIC)
    PHP_ME(CPCertificateStatus, EKU, arginfo_cpcertificatestatus_eku, ZEND_ACC_PUBLIC)
    PHP_ME(CPCertificateStatus, get_VerificationTime, arginfo_cpcertificatestatus_get_verificationtime, ZEND_ACC_PUBLIC)
    PHP_ME(CPCertificateStatus, set_VerificationTime, arginfo_cpcertificatestatus_set_verificationtime, ZEND_ACC_PUBLIC)
    PHP_ME(CPCertificateStatus, get_UrlRetrievalTimeout, arginfo_cpcertificatestatus_get_urlretrievaltimeout, ZEND_ACC_PUBLIC)
    PHP_ME(CPCertificateStatus, set_UrlRetrievalTimeout, arginfo_cpcertificatestatus_set_urlretrievaltimeout, ZEND_ACC_PUBLIC)
    PHP_ME(CPCertificateStatus, CertificatePolicies, arginfo_cpcertificatestatus_certificatepolicies, ZEND_ACC_PUBLIC)
    PHP_ME(CPCertificateStatus, ApplicationPolicies, arginfo_cpcertificatestatus_applicationpolicies, ZEND_ACC_PUBLIC)
    PHP_ME(CPCertificateStatus, get_ValidationCertificates, arginfo_cpcertificatestatus_get_validationcertificates, ZEND_ACC_PUBLIC)
    {NULL, NULL, NULL}};

void certstat_init(void) {
    zend_class_entry ce;
    INIT_CLASS_ENTRY(ce, "CPCertificateStatus", certstat_methods);
    certstat_ce = zend_register_internal_class(&ce );
    certstat_ce->create_object = certstat_create_handler;
    memcpy(&certstat_obj_handlers, zend_get_std_object_handlers(),
           sizeof(zend_object_handlers));
    certstat_obj_handlers.clone_obj = NULL;
    certstat_obj_handlers.free_obj = certstat_free;
    certstat_obj_handlers.offset = XtOffsetOf(certstat_obj, zobj);
}
