#include "stdafx.h"
#include "PHPCadesCPRawSignature.h"
#include "PHPCadesCPHashedData.h"
#include "PHPCadesCPCertificate.h"
using namespace CryptoPro::PKI::CAdES;

PHP_METHOD(CPRawSignature, __construct) {
    raw_sig_obj *obj =
        (raw_sig_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);
    obj->m_pCppCadesImpl = boost::shared_ptr<CPPCadesRawSignatureObject>(
        new CPPCadesRawSignatureObject());
}

PHP_METHOD(CPRawSignature, VerifyHash) {
    zval *zHashedData;
    char *sVal;
    int lVal;
    zval *zCert;
    CCertContext Context;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "OsO", &zHashedData,
                              hash_dat_class_entry, &sVal, &lVal, &zCert,
                              cert_ce) == FAILURE)
        RETURN_WITH_EXCEPTION(E_INVALIDARG);

    hash_dat_obj *pHashedData =
        (hash_dat_obj *)zend_object_store_get_object(zHashedData TSRMLS_CC);
    cert_obj *pCert = (cert_obj *)zend_object_store_get_object(zCert TSRMLS_CC);
    CAtlString Val(sVal, lVal);

    raw_sig_obj *obj =
        (raw_sig_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->VerifyHash(
        pHashedData->m_pCppCadesImpl, Val, pCert->m_pCppCadesImpl));
}

PHP_METHOD(CPRawSignature, SignHash) {
    zval *zHashedData;
    zval *zCert;
    CAtlString Val;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "OO", &zHashedData,
                              hash_dat_class_entry, &zCert, cert_ce) == FAILURE)
        RETURN_WITH_EXCEPTION(E_INVALIDARG);

    hash_dat_obj *pHashedData =
        (hash_dat_obj *)zend_object_store_get_object(zHashedData TSRMLS_CC);
    cert_obj *pCert = (cert_obj *)zend_object_store_get_object(zCert TSRMLS_CC);

    raw_sig_obj *obj =
        (raw_sig_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);
    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->SignHash(
        pHashedData->m_pCppCadesImpl, pCert->m_pCppCadesImpl, Val));
    RETURN_ATL_STRINGL(Val)
}

zend_function_entry raw_sig_methods[] = {
    PHP_ME(CPRawSignature, __construct, NULL, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
    PHP_ME(CPRawSignature, VerifyHash, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(CPRawSignature, SignHash, NULL, ZEND_ACC_PUBLIC){NULL, NULL, NULL}};

zend_class_entry *raw_sig_class_entry;
zend_object_handlers raw_sig_handlers;

void raw_sig_free_storage(void *object TSRMLS_DC) {
    raw_sig_obj *obj = (raw_sig_obj *)object;
    obj->m_pCppCadesImpl.reset();

    zend_hash_destroy(obj->zo.properties);
    FREE_HASHTABLE(obj->zo.properties);

    efree(obj);
}

zend_object_value raw_sig_create_handler(zend_class_entry *type TSRMLS_DC) {
    zend_object_value retval;

    raw_sig_obj *obj = (raw_sig_obj *)emalloc(sizeof(raw_sig_obj));
    memset(obj, 0, sizeof(raw_sig_obj));
    obj->zo.ce = type;

    ALLOC_HASHTABLE(obj->zo.properties);
    zend_hash_init(obj->zo.properties, 0, NULL, ZVAL_PTR_DTOR, 0);
#if PHP_VERSION_ID < 50399
    zval *tmp;
    zend_hash_copy(obj->zo.properties, &(type->default_properties),
                   (copy_ctor_func_t)zval_add_ref, (void *)&tmp,
                   sizeof(zval *));
#else
    object_properties_init(&obj->zo, type);
#endif

    retval.handle =
        zend_objects_store_put(obj, NULL, raw_sig_free_storage, NULL TSRMLS_CC);
    retval.handlers = &raw_sig_handlers;

    return retval;
}

void raw_sig_init(TSRMLS_D) {
    zend_class_entry ce;
    INIT_CLASS_ENTRY(ce, "CPRawSignature", raw_sig_methods);
    raw_sig_class_entry = zend_register_internal_class(&ce TSRMLS_CC);
    raw_sig_class_entry->create_object = raw_sig_create_handler;
    memcpy(&raw_sig_handlers, zend_get_std_object_handlers(),
           sizeof(zend_object_handlers));
    raw_sig_handlers.clone_obj = NULL;
}
