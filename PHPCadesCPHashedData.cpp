#include "stdafx.h"
#include "PHPCadesCPHashedData.h"
using namespace CryptoPro::PKI::CAdES;

PHP_METHOD(CPHashedData, __construct) {
    hash_dat_obj *obj =
        (hash_dat_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);
    obj->m_pCppCadesImpl = boost::shared_ptr<CPPCadesCPHashedDataObject>(
        new CPPCadesCPHashedDataObject());
}

PHP_METHOD(CPHashedData, Hash) {
    char *sVal;
    int lVal;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &sVal, &lVal) ==
        FAILURE)
        RETURN_WITH_EXCEPTION(E_INVALIDARG);

    hash_dat_obj *obj =
        (hash_dat_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);
    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->put_Hash(sVal, lVal));
}

PHP_METHOD(CPHashedData, SetHashValue) {
    char *sVal;
    int lVal;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &sVal, &lVal) ==
        FAILURE)
        RETURN_WITH_EXCEPTION(E_INVALIDARG);

    if (lVal < 10)
        RETURN_WITH_EXCEPTION(E_INVALIDARG);

    CAtlString Val(sVal, lVal);

    hash_dat_obj *obj =
        (hash_dat_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);
    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->put_HashValue(Val));
}

PHP_METHOD(CPHashedData, get_Key) {
    CAtlString Val;

    hash_dat_obj *obj =
        (hash_dat_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);
    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_Key(Val));

    RETURN_ATL_STRINGL(Val)
}

PHP_METHOD(CPHashedData, set_Key) {
    CAtlString sVal;
    char *Val;
    int len;

    hash_dat_obj *obj =
        (hash_dat_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &Val, &len) ==
        FAILURE)
        RETURN_WITH_EXCEPTION(E_INVALIDARG);

    sVal = CAtlString(Val);
    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->put_Key(sVal));
}

PHP_METHOD(CPHashedData, get_Value) {
    CAtlString Val;

    hash_dat_obj *obj =
        (hash_dat_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);
    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_Value(Val));

    RETURN_ATL_STRINGL(Val)
}

PHP_METHOD(CPHashedData, set_Algorithm) {
    long lAlgorithm;
    CAPICOM_HASH_ALGORITHM Algorithm;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &lAlgorithm) ==
        FAILURE)
        RETURN_WITH_EXCEPTION(E_INVALIDARG);

    Algorithm = (CAPICOM_HASH_ALGORITHM)lAlgorithm;

    hash_dat_obj *obj =
        (hash_dat_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);
    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->put_Algorithm(Algorithm));
}

PHP_METHOD(CPHashedData, get_Algorithm) {
    CAPICOM_HASH_ALGORITHM Algorithm;

    hash_dat_obj *obj =
        (hash_dat_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);
    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_Algorithm(&Algorithm));

    RETURN_LONG(Algorithm)
}

PHP_METHOD(CPHashedData, set_DataEncoding) {
    long lType;
    CADESCOM_CONTENT_ENCODING_TYPE Type;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &lType) ==
        FAILURE)
        RETURN_WITH_EXCEPTION(E_INVALIDARG);

    Type = (CADESCOM_CONTENT_ENCODING_TYPE)lType;

    hash_dat_obj *obj =
        (hash_dat_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);
    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->put_DataEncoding(Type));
}

PHP_METHOD(CPHashedData, get_DataEncoding) {
    CADESCOM_CONTENT_ENCODING_TYPE type;

    hash_dat_obj *obj =
        (hash_dat_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);
    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_DataEncoding(&type));

    RETURN_LONG(type)
}

zend_class_entry *hash_dat_class_entry;
zend_object_handlers hash_dat_handlers;

zend_function_entry hash_dat_methods[] = {
    PHP_ME(CPHashedData, __construct, NULL, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
    PHP_ME(CPHashedData, Hash, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(CPHashedData, SetHashValue, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(CPHashedData, get_Value, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(CPHashedData, set_Key, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(CPHashedData, get_Key, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(CPHashedData, set_Algorithm, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(CPHashedData, get_Algorithm, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(CPHashedData, set_DataEncoding, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(CPHashedData, get_DataEncoding, NULL, ZEND_ACC_PUBLIC){NULL, NULL,
                                                                  NULL}};

void hash_dat_free_storage(void *object TSRMLS_DC) {
    hash_dat_obj *obj = (hash_dat_obj *)object;
    obj->m_pCppCadesImpl.reset();

    zend_hash_destroy(obj->zo.properties);
    FREE_HASHTABLE(obj->zo.properties);

    efree(obj);
}

zend_object_value hash_dat_create_handler(zend_class_entry *type TSRMLS_DC) {
    zend_object_value retval;

    hash_dat_obj *obj = (hash_dat_obj *)emalloc(sizeof(hash_dat_obj));
    memset(obj, 0, sizeof(hash_dat_obj));
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

    retval.handle = zend_objects_store_put(obj, NULL, hash_dat_free_storage,
                                           NULL TSRMLS_CC);
    retval.handlers = &hash_dat_handlers;

    return retval;
}

void hash_dat_init(TSRMLS_D) {
    zend_class_entry ce;
    INIT_CLASS_ENTRY(ce, "CPHashedData", hash_dat_methods);
    hash_dat_class_entry = zend_register_internal_class(&ce TSRMLS_CC);
    hash_dat_class_entry->create_object = hash_dat_create_handler;
    memcpy(&hash_dat_handlers, zend_get_std_object_handlers(),
           sizeof(zend_object_handlers));
    hash_dat_handlers.clone_obj = NULL;
}
