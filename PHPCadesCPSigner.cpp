#include "stdafx.h"
#include "PHPCadesCPSigner.h"
#include "PHPCadesCPCertificate.h"
#include "PHPCadesCPAttribute.h"
#include "PHPCadesCPAttributes.h"
using namespace CryptoPro::PKI::CAdES;

//Методы
PHP_METHOD(CPSigner, __construct) {
    zend_object *zobj = Z_OBJ_P(getThis());
    signer_obj *obj =
        (signer_obj *)((char *)zobj - XtOffsetOf(signer_obj, zobj));
    NS_SHARED_PTR::shared_ptr<CPPCadesCPSignerObject> ptr(new CPPCadesCPSignerObject());
    obj->m_pCppCadesImpl = ptr;
}

PHP_METHOD(CPSigner, get_Certificate) {
    NS_SHARED_PTR::shared_ptr<CPPCadesCPCertificateObject> ctxt;
    zend_object *zobj = Z_OBJ_P(getThis());
    signer_obj *obj =
        (signer_obj *)((char *)zobj - XtOffsetOf(signer_obj, zobj));

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_Certificate(ctxt));

    object_init_ex(return_value, cert_ce);
    zobj = Z_OBJ_P(return_value);
    certificate_obj *cobj =
        (certificate_obj *)((char *)zobj - XtOffsetOf(certificate_obj, zobj));
    cobj->m_pCppCadesImpl = ctxt;
}

PHP_METHOD(CPSigner, set_Certificate) {
    zval *cert;
    CCertContext ctxt;

    if (zend_parse_parameters(ZEND_NUM_ARGS() , "O", &cert, cert_ce) ==
        FAILURE)
        RETURN_WITH_EXCEPTION(E_INVALIDARG);

    zend_object *zobj = Z_OBJ_P(getThis());
    signer_obj *obj =
        (signer_obj *)((char *)zobj - XtOffsetOf(signer_obj, zobj));
    zobj = Z_OBJ_P(cert);
    certificate_obj *cobj = (certificate_obj *)((char *)zobj - XtOffsetOf(certificate_obj, zobj));

    HR_ERRORCHECK_RETURN(cobj->m_pCppCadesImpl->get_CertContext(ctxt));
    NS_SHARED_PTR::shared_ptr<CPPCadesCPCertificateObject> pCert(
        new CPPCadesCPCertificateObject());
    pCert->put_CertContext(ctxt);
    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->put_Certificate(pCert));
}

PHP_METHOD(CPSigner, get_Options) {
    CAPICOM_CERTIFICATE_INCLUDE_OPTION opt;

    zend_object *zobj = Z_OBJ_P(getThis());
    signer_obj *obj =
        (signer_obj *)((char *)zobj - XtOffsetOf(signer_obj, zobj));
    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_Options(&opt));

    RETURN_LONG(opt);
}

PHP_METHOD(CPSigner, set_Options) {
    long lOpt;
    CAPICOM_CERTIFICATE_INCLUDE_OPTION Opt;

    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &lOpt) == FAILURE)
        RETURN_WITH_EXCEPTION(E_INVALIDARG);

    Opt = (CAPICOM_CERTIFICATE_INCLUDE_OPTION)lOpt;

    zend_object *zobj = Z_OBJ_P(getThis());
    signer_obj *obj =
        (signer_obj *)((char *)zobj - XtOffsetOf(signer_obj, zobj));
    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->put_Options(Opt));
}

PHP_METHOD(CPSigner, get_AuthenticatedAttributes) {
    zend_object *zobj = Z_OBJ_P(getThis());
    signer_obj *obj =
        (signer_obj *)((char *)zobj - XtOffsetOf(signer_obj, zobj));

    object_init_ex(return_value, attributes_col_ce);
    zobj = Z_OBJ_P(return_value);
    attributes_col_obj *aobj =
        (attributes_col_obj *)((char *)zobj - XtOffsetOf(attributes_col_obj, zobj));
    aobj->type = attribute_ce;

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_AuthenticatedAttributes(
        aobj->m_pCppCadesImpl));
}

PHP_METHOD(CPSigner, get_UnauthenticatedAttributes) {
    zend_object *zobj = Z_OBJ_P(getThis());
    signer_obj *obj =
        (signer_obj *)((char *)zobj - XtOffsetOf(signer_obj, zobj));

    object_init_ex(return_value, attributes_col_ce);
    zobj = Z_OBJ_P(return_value);
    attributes_col_obj *aobj =
        (attributes_col_obj *)((char *)zobj - XtOffsetOf(attributes_col_obj, zobj));
    aobj->type = attribute_ce;

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_UnauthenticatedAttributes(
        aobj->m_pCppCadesImpl));
}

PHP_METHOD(CPSigner, get_TSAAddress) {
    CAtlString adrs;

    zend_object *zobj = Z_OBJ_P(getThis());
    signer_obj *obj =
        (signer_obj *)((char *)zobj - XtOffsetOf(signer_obj, zobj));

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_TSAAddress(adrs));

    RETURN_ATL_STRING(adrs)
}

PHP_METHOD(CPSigner, set_TSAAddress) {
    char *str;
    size_t len;

    if (zend_parse_parameters(ZEND_NUM_ARGS() , "s", &str, &len) ==
        FAILURE)
        RETURN_WITH_EXCEPTION(E_INVALIDARG);

    zend_object *zobj = Z_OBJ_P(getThis());
    signer_obj *obj =
        (signer_obj *)((char *)zobj - XtOffsetOf(signer_obj, zobj));

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->put_TSAAddress(CAtlString(str)));
}

PHP_METHOD(CPSigner, get_CRLs) {
    unsigned int count;
    unsigned int len;
    char *str = NULL;
    NS_SHARED_PTR::shared_ptr<CryptoPro::CBlob> pBlob;
    NS_SHARED_PTR::shared_ptr<CPPCadesCPBlobsObject> ptr;

    zend_object *zobj = Z_OBJ_P(getThis());
    signer_obj *obj =
        (signer_obj *)((char *)zobj - XtOffsetOf(signer_obj, zobj));
    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_CRLs(ptr));

    HR_ERRORCHECK_RETURN(ptr->get_Count(&count));

    array_init(return_value);
    for (unsigned int i = 1; i <= count; i++) {
        ptr->get_Item(i, pBlob);
        len = pBlob->cbData();
        str = (char *)ecalloc(len, sizeof(char));
        memcpy(str, pBlob->pbData(), len);
        add_next_index_stringl(return_value, str, len);
        str = NULL;
    }
}

PHP_METHOD(CPSigner, get_OCSPResponses) {
    unsigned int count;
    unsigned int len;
    char *str = NULL;
    NS_SHARED_PTR::shared_ptr<CryptoPro::CBlob> pBlob;
    NS_SHARED_PTR::shared_ptr<CPPCadesCPBlobsObject> ptr;

    zend_object *zobj = Z_OBJ_P(getThis());
    signer_obj *obj =
        (signer_obj *)((char *)zobj - XtOffsetOf(signer_obj, zobj));
    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_OCSPResponses(ptr));

    HR_ERRORCHECK_RETURN(ptr->get_Count(&count));

    array_init(return_value);
    for (unsigned int i = 1; i <= count; i++) {
        ptr->get_Item(i, pBlob);
        len = pBlob->cbData();
        str = (char *)ecalloc(len, sizeof(char));
        memcpy(str, pBlob->pbData(), len);
        add_next_index_stringl(return_value, str, len);
        str = NULL;
    }
}

PHP_METHOD(CPSigner, get_SigningTime) {
    CryptoPro::CDateTime time;
    CryptoPro::CStringProxy strpr;

    zend_object *zobj = Z_OBJ_P(getThis());
    signer_obj *obj =
        (signer_obj *)((char *)zobj - XtOffsetOf(signer_obj, zobj));

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_SigningTime(time));

    strpr = time.tostring();
    RETURN_PROXY_STRING(strpr)
}

PHP_METHOD(CPSigner, get_SignatureTimeStampTime) {
    CryptoPro::CDateTime time;
    CryptoPro::CStringProxy strpr;

    zend_object *zobj = Z_OBJ_P(getThis());
    signer_obj *obj =
        (signer_obj *)((char *)zobj - XtOffsetOf(signer_obj, zobj));

    HR_ERRORCHECK_RETURN(
        obj->m_pCppCadesImpl->get_SignatureTimeStampTime(time));

    strpr = time.tostring();
    RETURN_PROXY_STRING(strpr);
}

PHP_METHOD(CPSigner, set_KeyPin) {
    char *str;
    size_t len;

    if (zend_parse_parameters(ZEND_NUM_ARGS() , "s", &str, &len) ==
        FAILURE)
        RETURN_WITH_EXCEPTION(E_INVALIDARG);

    zend_object *zobj = Z_OBJ_P(getThis());
    signer_obj *obj =
        (signer_obj *)((char *)zobj - XtOffsetOf(signer_obj, zobj));
    CAtlStringA pin(CA2CA(CAtlStringA(str), CP_UTF8));
    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->put_KeyPin(pin));
}

//Вспомогательные функции обертки
zend_object_handlers signer_obj_handlers;
zend_class_entry *signer_ce;

static void signer_free(zend_object *object) {
    signer_obj *obj = (signer_obj *)((char *)object - XtOffsetOf(signer_obj, zobj));
    obj->m_pCppCadesImpl.reset();

    zend_object_std_dtor(object);
}

static zend_object* signer_create_handler(zend_class_entry *ce ) {
    signer_obj *obj = (signer_obj *)emalloc(sizeof(signer_obj) + zend_object_properties_size(ce));
    memset(obj, 0, sizeof(signer_obj) + zend_object_properties_size(ce));
    
    zend_object_std_init(&obj->zobj, ce);
    object_properties_init(&obj->zobj, ce);
    obj->zobj.handlers = &signer_obj_handlers;

    return &obj->zobj;
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpsigner_construct, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpsigner_get_certificate, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpsigner_set_certificate, 0, 0, 1)
 ZEND_ARG_INFO(0, certificate)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpsigner_get_options, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpsigner_set_options, 0, 0, 1)
 ZEND_ARG_INFO(0, options)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpsigner_get_authenticatedattributes, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpsigner_get_unauthenticatedattributes, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpsigner_get_tsaaddress, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpsigner_set_tsaaddress, 0, 0, 1)
 ZEND_ARG_INFO(0, tsaaddress)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpsigner_get_crls, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpsigner_get_ocspresponses, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpsigner_get_signingtime, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpsigner_get_signaturetimestamptime, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpsigneddata_set_keypin, 0, 0, 1)
 ZEND_ARG_INFO(0, pin)
ZEND_END_ARG_INFO()

zend_function_entry CPSigner_methods[] = {
    PHP_ME(CPSigner, __construct, arginfo_cpsigner_construct, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
    PHP_ME(CPSigner, get_Certificate, arginfo_cpsigner_get_certificate, ZEND_ACC_PUBLIC)
    PHP_ME(CPSigner, set_Certificate, arginfo_cpsigner_set_certificate, ZEND_ACC_PUBLIC)
    PHP_ME(CPSigner, get_Options, arginfo_cpsigner_get_options, ZEND_ACC_PUBLIC)
    PHP_ME(CPSigner, set_Options, arginfo_cpsigner_set_options, ZEND_ACC_PUBLIC)
    PHP_ME(CPSigner, get_AuthenticatedAttributes, arginfo_cpsigner_get_authenticatedattributes, ZEND_ACC_PUBLIC)
    PHP_ME(CPSigner, get_UnauthenticatedAttributes, arginfo_cpsigner_get_unauthenticatedattributes, ZEND_ACC_PUBLIC)
    PHP_ME(CPSigner, get_TSAAddress, arginfo_cpsigner_get_tsaaddress, ZEND_ACC_PUBLIC)
    PHP_ME(CPSigner, set_TSAAddress, arginfo_cpsigner_set_tsaaddress, ZEND_ACC_PUBLIC)
    PHP_ME(CPSigner, get_CRLs, arginfo_cpsigner_get_crls, ZEND_ACC_PUBLIC)
    PHP_ME(CPSigner, get_OCSPResponses, arginfo_cpsigner_get_ocspresponses, ZEND_ACC_PUBLIC)
    PHP_ME(CPSigner, get_SigningTime, arginfo_cpsigner_get_signingtime, ZEND_ACC_PUBLIC)
    PHP_ME(CPSigner, get_SignatureTimeStampTime, arginfo_cpsigner_get_signaturetimestamptime, ZEND_ACC_PUBLIC)
    PHP_ME(CPSigner, set_KeyPin, arginfo_cpsigneddata_set_keypin, ZEND_ACC_PUBLIC)
    {NULL, NULL, NULL}};

void sig_init(void) {
    zend_class_entry ce;
    INIT_CLASS_ENTRY(ce, "CPSigner", CPSigner_methods);
    signer_ce = zend_register_internal_class(&ce );
    signer_ce->create_object = signer_create_handler;
    memcpy(&signer_obj_handlers, zend_get_std_object_handlers(),
           sizeof(zend_object_handlers));
    signer_obj_handlers.clone_obj = NULL;
    signer_obj_handlers.free_obj = signer_free;
    signer_obj_handlers.offset = XtOffsetOf(signer_obj, zobj);
}
