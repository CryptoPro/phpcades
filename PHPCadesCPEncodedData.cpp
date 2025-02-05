#include "stdafx.h"
#include "PHPCadesCPEncodedData.h"
using namespace CryptoPro::PKI::CAdES;

PHP_METHOD(CPEncodedData, __construct) {
    encoded_data_obj *obj =
        (encoded_data_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);
    obj->m_pCppCadesImpl = NS_SHARED_PTR::shared_ptr<CPPCadesCPEncodedDataObject>(
        new CPPCadesCPEncodedDataObject());
}

PHP_METHOD(CPEncodedData, Format) {
    CAtlStringW atlstr;
    long lML;
    BOOL bML;

    encoded_data_obj *obj =
        (encoded_data_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &lML) == FAILURE)
        RETURN_WITH_EXCEPTION(E_INVALIDARG);

    bML = (BOOL)lML;

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->Format(bML, atlstr));

    RETURN_ATL_STRING_W(atlstr)
}

PHP_METHOD(CPEncodedData, get_Value) {
    long lType;
    CAPICOM_ENCODING_TYPE Type;
    CryptoPro::CBlob data;
    char *str;
    unsigned int len;

    encoded_data_obj *obj =
        (encoded_data_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &lType) ==
        FAILURE)
        RETURN_WITH_EXCEPTION(E_INVALIDARG);

    Type = (CAPICOM_ENCODING_TYPE)lType;

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_Value(Type, data));

    len = data.cbData();
    str = (char *)ecalloc(len, sizeof(char));
    memcpy(str, data.pbData(), len);

    RETURN_STRINGL(str, len, 0)
}

zend_object_handlers encoded_data_obj_handlers;
zend_class_entry *encoded_data_ce;

void encoded_data_free_storage(void *object TSRMLS_DC) {
    encoded_data_obj *obj = (encoded_data_obj *)object;
    obj->m_pCppCadesImpl.reset();

    zend_hash_destroy(obj->zo.properties);
    FREE_HASHTABLE(obj->zo.properties);

    efree(obj);
}

zend_object_value encoded_data_create_handler(zend_class_entry *type
                                                  TSRMLS_DC) {
    zend_object_value retval;

    encoded_data_obj *obj =
        (encoded_data_obj *)emalloc(sizeof(encoded_data_obj));
    memset(obj, 0, sizeof(encoded_data_obj));
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

    retval.handle = zend_objects_store_put(obj, NULL, encoded_data_free_storage,
                                           NULL TSRMLS_CC);
    retval.handlers = &encoded_data_obj_handlers;

    return retval;
}

//связывание методов класса в function entry
zend_function_entry encoded_data_methods[] = {
    PHP_ME(CPEncodedData, __construct, NULL, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
    PHP_ME(CPEncodedData, Format, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(CPEncodedData, get_Value, NULL, ZEND_ACC_PUBLIC){NULL, NULL, NULL}};

void encoded_data_init(TSRMLS_D) {
    zend_class_entry ce;
    INIT_CLASS_ENTRY(ce, "CPEncodedData", encoded_data_methods);
    encoded_data_ce = zend_register_internal_class(&ce TSRMLS_CC);
    encoded_data_ce->create_object = encoded_data_create_handler;
    memcpy(&encoded_data_obj_handlers, zend_get_std_object_handlers(),
           sizeof(zend_object_handlers));
    encoded_data_obj_handlers.clone_obj = NULL;
}
