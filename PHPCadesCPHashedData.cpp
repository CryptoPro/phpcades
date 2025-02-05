#include "stdafx.h"
#include "PHPCadesCPHashedData.h"
using namespace CryptoPro::PKI::CAdES;

PHP_METHOD(CPHashedData, __construct) {
    zend_object *zobj = Z_OBJ_P(getThis());
    hashed_data_obj *obj =
        (hashed_data_obj *)((char *)zobj - XtOffsetOf(hashed_data_obj, zobj));
    obj->m_pCppCadesImpl = NS_SHARED_PTR::shared_ptr<CPPCadesCPHashedDataObject>(
        new CPPCadesCPHashedDataObject());
}

PHP_METHOD(CPHashedData, Hash) {
    char *sVal;
    size_t lVal;

    if (zend_parse_parameters(ZEND_NUM_ARGS() , "s", &sVal, &lVal) ==
        FAILURE)
        RETURN_WITH_EXCEPTION(E_INVALIDARG);

    zend_object *zobj = Z_OBJ_P(getThis());
    hashed_data_obj *obj =
        (hashed_data_obj *)((char *)zobj - XtOffsetOf(hashed_data_obj, zobj));
    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->put_Hash(sVal, lVal));
}

PHP_METHOD(CPHashedData, SetHashValue) {
    char *sVal;
    size_t lVal;

    if (zend_parse_parameters(ZEND_NUM_ARGS() , "s", &sVal, &lVal) ==
        FAILURE)
        RETURN_WITH_EXCEPTION(E_INVALIDARG);

    if (lVal < 10)
        RETURN_WITH_EXCEPTION(E_INVALIDARG);

    CAtlString Val(sVal, lVal);

    zend_object *zobj = Z_OBJ_P(getThis());
    hashed_data_obj *obj =
        (hashed_data_obj *)((char *)zobj - XtOffsetOf(hashed_data_obj, zobj));
    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->put_HashValue(Val));
}

PHP_METHOD(CPHashedData, get_Key) {
    CAtlString Val;

    zend_object *zobj = Z_OBJ_P(getThis());
    hashed_data_obj *obj =
            (hashed_data_obj *)((char *)zobj - XtOffsetOf(hashed_data_obj, zobj));
    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_Key(Val));

    RETURN_ATL_STRINGL(Val);
}

PHP_METHOD(CPHashedData, set_Key) {
    CAtlString sVal;
    char *Val;
    int len;

    if (zend_parse_parameters(ZEND_NUM_ARGS() , "s", &Val, &len) ==
        FAILURE)
        RETURN_WITH_EXCEPTION(E_INVALIDARG);

    zend_object *zobj = Z_OBJ_P(getThis());
    hashed_data_obj *obj =
            (hashed_data_obj *)((char *)zobj - XtOffsetOf(hashed_data_obj, zobj));

    sVal = CAtlString(Val);
    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->put_Key(sVal));
}

PHP_METHOD(CPHashedData, get_Value) {
    CAtlString Val;

    zend_object *zobj = Z_OBJ_P(getThis());
    hashed_data_obj *obj =
        (hashed_data_obj *)((char *)zobj - XtOffsetOf(hashed_data_obj, zobj));
    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_Value(Val));

    RETURN_ATL_STRINGL(Val);
}

PHP_METHOD(CPHashedData, set_Algorithm) {
    long lAlgorithm;
    CAPICOM_HASH_ALGORITHM Algorithm;

    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &lAlgorithm) ==
        FAILURE)
        RETURN_WITH_EXCEPTION(E_INVALIDARG);

    Algorithm = (CAPICOM_HASH_ALGORITHM)lAlgorithm;

    zend_object *zobj = Z_OBJ_P(getThis());
    hashed_data_obj *obj =
        (hashed_data_obj *)((char *)zobj - XtOffsetOf(hashed_data_obj, zobj));
    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->put_Algorithm(Algorithm));
}

PHP_METHOD(CPHashedData, get_Algorithm) {
    CAPICOM_HASH_ALGORITHM Algorithm;

    zend_object *zobj = Z_OBJ_P(getThis());
    hashed_data_obj *obj =
        (hashed_data_obj *)((char *)zobj - XtOffsetOf(hashed_data_obj, zobj));
    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_Algorithm(&Algorithm));

    RETURN_LONG(Algorithm);
}

PHP_METHOD(CPHashedData, set_DataEncoding) {
    long lType;
    CADESCOM_CONTENT_ENCODING_TYPE Type;

    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &lType) ==
        FAILURE)
        RETURN_WITH_EXCEPTION(E_INVALIDARG);

    Type = (CADESCOM_CONTENT_ENCODING_TYPE)lType;

    zend_object *zobj = Z_OBJ_P(getThis());
    hashed_data_obj *obj =
        (hashed_data_obj *)((char *)zobj - XtOffsetOf(hashed_data_obj, zobj));
    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->put_DataEncoding(Type));
}

PHP_METHOD(CPHashedData, get_DataEncoding) {
    CADESCOM_CONTENT_ENCODING_TYPE type;

    zend_object *zobj = Z_OBJ_P(getThis());
    hashed_data_obj *obj =
        (hashed_data_obj *)((char *)zobj - XtOffsetOf(hashed_data_obj, zobj));
    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_DataEncoding(&type));

    RETURN_LONG(type);
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_cphasheddata_construct, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cphasheddata_hash, 0, 0, 1)
 ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cphasheddata_sethashvalue, 0, 0, 1)
 ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cphasheddata_get_value, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cphasheddata_set_key, 0, 0, 1)
 ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cphasheddata_get_key, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cphasheddata_set_algorithm, 0, 0, 1)
 ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cphasheddata_get_algorithm, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cphasheddata_set_dataencoding, 0, 0, 1)
 ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cphasheddata_get_dataencoding, 0, 0, 0)
ZEND_END_ARG_INFO()

zend_class_entry *hashed_data_ce;
zend_object_handlers hashed_data_obj_handlers;

zend_function_entry hashed_data_methods[] = {
    PHP_ME(CPHashedData, __construct, arginfo_cphasheddata_construct, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
    PHP_ME(CPHashedData, Hash, arginfo_cphasheddata_hash, ZEND_ACC_PUBLIC)
    PHP_ME(CPHashedData, SetHashValue, arginfo_cphasheddata_sethashvalue, ZEND_ACC_PUBLIC)
    PHP_ME(CPHashedData, get_Value, arginfo_cphasheddata_get_value, ZEND_ACC_PUBLIC)
    PHP_ME(CPHashedData, set_Key, arginfo_cphasheddata_set_key, ZEND_ACC_PUBLIC)
    PHP_ME(CPHashedData, get_Key, arginfo_cphasheddata_get_key, ZEND_ACC_PUBLIC)
    PHP_ME(CPHashedData, set_Algorithm, arginfo_cphasheddata_set_algorithm, ZEND_ACC_PUBLIC)
    PHP_ME(CPHashedData, get_Algorithm, arginfo_cphasheddata_get_algorithm, ZEND_ACC_PUBLIC)
    PHP_ME(CPHashedData, set_DataEncoding, arginfo_cphasheddata_set_dataencoding, ZEND_ACC_PUBLIC)
    PHP_ME(CPHashedData, get_DataEncoding, arginfo_cphasheddata_get_dataencoding, ZEND_ACC_PUBLIC)
    {NULL, NULL, NULL}};

static void hashed_data_free(zend_object *object ) {
    hashed_data_obj *obj = (hashed_data_obj *)((char *)object - XtOffsetOf(hashed_data_obj, zobj));
    obj->m_pCppCadesImpl.reset();

    zend_object_std_dtor(object);
}

static zend_object* hashed_data_create_handler(zend_class_entry *ce ) {
    hashed_data_obj *obj = (hashed_data_obj *)emalloc(sizeof(hashed_data_obj) + zend_object_properties_size(ce));
    memset(obj, 0, sizeof(hashed_data_obj) + zend_object_properties_size(ce));
    
    zend_object_std_init(&obj->zobj, ce);
    object_properties_init(&obj->zobj, ce);
    obj->zobj.handlers = &hashed_data_obj_handlers;

    return &obj->zobj;
}

void hashed_data_init(void) {
    zend_class_entry ce;
    INIT_CLASS_ENTRY(ce, "CPHashedData", hashed_data_methods);
    hashed_data_ce = zend_register_internal_class(&ce );
    hashed_data_ce->create_object = hashed_data_create_handler;
    memcpy(&hashed_data_obj_handlers, zend_get_std_object_handlers(),
           sizeof(zend_object_handlers));
    hashed_data_obj_handlers.clone_obj = NULL;
    hashed_data_obj_handlers.free_obj = hashed_data_free;
    hashed_data_obj_handlers.offset = XtOffsetOf(hashed_data_obj, zobj);
}
