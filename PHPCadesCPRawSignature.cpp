#include "stdafx.h"
#include "PHPCadesCPRawSignature.h"
#include "PHPCadesCPHashedData.h"
#include "PHPCadesCPCertificate.h"
using namespace CryptoPro::PKI::CAdES;

PHP_METHOD(CPRawSignature, __construct) {
    zend_object *zobj = Z_OBJ_P(getThis());
    raw_sig_obj *obj =
        (raw_sig_obj *)((char *)zobj - XtOffsetOf(raw_sig_obj, zobj));
    obj->m_pCppCadesImpl = NS_SHARED_PTR::shared_ptr<CPPCadesRawSignatureObject>(
        new CPPCadesRawSignatureObject());
}

PHP_METHOD(CPRawSignature, VerifyHash) {
    zval *zHashedData;
    char *sVal;
    size_t lVal;
    zval *zCert;
    CCertContext Context;

    if (zend_parse_parameters(ZEND_NUM_ARGS() , "OsO", &zHashedData,
                              hashed_data_ce, &sVal, &lVal, &zCert,
                              cert_ce) == FAILURE)
        RETURN_WITH_EXCEPTION(E_INVALIDARG);

    CAtlString Val(sVal, lVal);
    zend_object *zobj = Z_OBJ_P(getThis());
    raw_sig_obj *obj =
        (raw_sig_obj *)((char *)zobj - XtOffsetOf(raw_sig_obj, zobj));

    zobj = Z_OBJ_P(zHashedData);
    hashed_data_obj *pHashedData =
        (hashed_data_obj *)((char *)zobj - XtOffsetOf(hashed_data_obj, zobj));

    zobj = Z_OBJ_P(zCert);    
    certificate_obj *pCert = (certificate_obj *)((char *)zobj - XtOffsetOf(certificate_obj, zobj));

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->VerifyHash(
        pHashedData->m_pCppCadesImpl, Val, pCert->m_pCppCadesImpl));
}

PHP_METHOD(CPRawSignature, SignHash) {
    zval *zHashedData;
    zval *zCert;
    CAtlString Val;

    if (zend_parse_parameters(ZEND_NUM_ARGS() , "OO", &zHashedData,
                              hashed_data_ce, &zCert, cert_ce) == FAILURE)
        RETURN_WITH_EXCEPTION(E_INVALIDARG);

    zend_object *zobj = Z_OBJ_P(getThis());
    raw_sig_obj *obj =
        (raw_sig_obj *)((char *)zobj - XtOffsetOf(raw_sig_obj, zobj));

    zobj = Z_OBJ_P(zHashedData);
    hashed_data_obj *pHashedData =
        (hashed_data_obj *)((char *)zobj - XtOffsetOf(hashed_data_obj, zobj));

    zobj = Z_OBJ_P(zCert);    
    certificate_obj *pCert = (certificate_obj *)((char *)zobj - XtOffsetOf(certificate_obj, zobj));


    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->SignHash(
        pHashedData->m_pCppCadesImpl, pCert->m_pCppCadesImpl, Val));
    RETURN_ATL_STRINGL(Val)
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_cprawsignature_construct, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cprawsignature_verifyhash, 0, 0, 3)
 ZEND_ARG_INFO(0, hasheddata)
 ZEND_ARG_INFO(0, hashvalue)
 ZEND_ARG_INFO(0, certificate)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cprawsignature_signhash, 0, 0, 2)
 ZEND_ARG_INFO(0, hasheddata)
 ZEND_ARG_INFO(0, certificate)
ZEND_END_ARG_INFO()

zend_function_entry raw_sig_methods[] = {
    PHP_ME(CPRawSignature, __construct, arginfo_cprawsignature_construct, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
    PHP_ME(CPRawSignature, VerifyHash, arginfo_cprawsignature_verifyhash, ZEND_ACC_PUBLIC)
    PHP_ME(CPRawSignature, SignHash, arginfo_cprawsignature_signhash, ZEND_ACC_PUBLIC){NULL, NULL, NULL}};

zend_class_entry *raw_sig_ce;
zend_object_handlers raw_sig_obj_handlers;

static void raw_sig_free(zend_object *object ) {
    raw_sig_obj *obj = (raw_sig_obj *)((char *)object - XtOffsetOf(raw_sig_obj, zobj));
    obj->m_pCppCadesImpl.reset();

    zend_object_std_dtor(object);
}

static zend_object* raw_sig_create_handler(zend_class_entry *ce ) {
    raw_sig_obj *obj = (raw_sig_obj *)emalloc(sizeof(raw_sig_obj) + zend_object_properties_size(ce));
    memset(obj, 0, sizeof(raw_sig_obj) + zend_object_properties_size(ce));
    
    zend_object_std_init(&obj->zobj, ce);
    object_properties_init(&obj->zobj, ce);
    obj->zobj.handlers = &raw_sig_obj_handlers;

    return &obj->zobj;
}

void raw_sig_init(void) {
    zend_class_entry ce;
    INIT_CLASS_ENTRY(ce, "CPRawSignature", raw_sig_methods);
    raw_sig_ce = zend_register_internal_class(&ce );
    raw_sig_ce->create_object = raw_sig_create_handler;
    memcpy(&raw_sig_obj_handlers, zend_get_std_object_handlers(),
           sizeof(zend_object_handlers));
    raw_sig_obj_handlers.clone_obj = NULL;
    raw_sig_obj_handlers.free_obj = raw_sig_free;
    raw_sig_obj_handlers.offset = XtOffsetOf(raw_sig_obj, zobj);
}
