#include "stdafx.h"
#include "PHPCadesCPEnvelopedData.h"
#include "PHPCadesCPRecipients.h"
#include "CPPCadesCPSigner.h"
using namespace CryptoPro::PKI::CAdES;

PHP_METHOD(CPEnvelopedData, __construct) {
    enveloped_data_obj *obj =
        (enveloped_data_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);
    obj->m_pCppCadesImpl = new CPPCadesCPEnvelopedDataObject();
}

PHP_METHOD(CPEnvelopedData, get_Content) {
    CStringBlob content;

    enveloped_data_obj *obj =
        (enveloped_data_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_Content(content));

    RETURN_ATL_STRING_A(content)
}

PHP_METHOD(CPEnvelopedData, set_Content) {
    char *str;
    unsigned int len;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &str, &len) ==
        FAILURE)
        RETURN_WITH_EXCEPTION(E_INVALIDARG);

    enveloped_data_obj *obj =
        (enveloped_data_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->put_Content(str, len));
}

PHP_METHOD(CPEnvelopedData, get_ContentEncoding) {
    CADESCOM_CONTENT_ENCODING_TYPE type;

    enveloped_data_obj *obj =
        (enveloped_data_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_ContentEncoding(&type));

    RETURN_LONG(type)
}

PHP_METHOD(CPEnvelopedData, set_ContentEncoding) {
    int type;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &type) == FAILURE)
        RETURN_WITH_EXCEPTION(E_INVALIDARG);

    enveloped_data_obj *obj =
        (enveloped_data_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);
    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->put_ContentEncoding(
        (CADESCOM_CONTENT_ENCODING_TYPE)type));
}

PHP_METHOD(CPEnvelopedData, Encrypt) {
    long lType;
    CAPICOM_ENCODING_TYPE Type;
    CryptoPro::CBlob data;
    char *str;
    int len;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &lType) ==
        FAILURE)
        RETURN_WITH_EXCEPTION(E_INVALIDARG);

    Type = (CAPICOM_ENCODING_TYPE)lType;

    enveloped_data_obj *obj =
        (enveloped_data_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->Encrypt(Type, data));

    len = data.cbData();
    str = (char *)ecalloc(len, sizeof(char));
    memcpy(str, data.pbData(), len);

    RETURN_STRINGL(str, len, 0)
}

PHP_METHOD(CPEnvelopedData, Decrypt) {
    CryptoPro::CBlob data;
    unsigned char *str;
    int len;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &str, &len) ==
        FAILURE)
        RETURN_WITH_EXCEPTION(E_INVALIDARG);

    enveloped_data_obj *obj =
        (enveloped_data_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);
    data.assign(str, len);

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->Decrypt(data));
}

PHP_METHOD(CPEnvelopedData, get_Recipients) {
    enveloped_data_obj *obj =
        (enveloped_data_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);
    object_init_ex(return_value, recipients_class_entry);
    recipients_obj *Recipients_ptr =
        (recipients_obj *)zend_object_store_get_object(return_value TSRMLS_CC);

    HR_ERRORCHECK_RETURN(
        obj->m_pCppCadesImpl->get_Recipients(Recipients_ptr->m_pCppCadesImpl));
}

zend_object_handlers enveloped_data_obj_handlers;
zend_class_entry *enveloped_data_ce;

void enveloped_data_free_storage(void *object TSRMLS_DC) {
    enveloped_data_obj *obj = (enveloped_data_obj *)object;
    delete obj->m_pCppCadesImpl;

    zend_hash_destroy(obj->zo.properties);
    FREE_HASHTABLE(obj->zo.properties);

    efree(obj);
}

zend_object_value enveloped_data_create_handler(zend_class_entry *type
                                                    TSRMLS_DC) {
    zend_object_value retval;

    enveloped_data_obj *obj =
        (enveloped_data_obj *)emalloc(sizeof(enveloped_data_obj));
    memset(obj, 0, sizeof(enveloped_data_obj));
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

    retval.handle = zend_objects_store_put(
        obj, NULL, enveloped_data_free_storage, NULL TSRMLS_CC);
    retval.handlers = &enveloped_data_obj_handlers;

    return retval;
}

//связывание методов класса в function entry
zend_function_entry enveloped_data_methods[] = {
    PHP_ME(CPEnvelopedData, __construct, NULL, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
    PHP_ME(CPEnvelopedData, get_Content, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(CPEnvelopedData, set_Content, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(CPEnvelopedData, get_ContentEncoding, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(CPEnvelopedData, set_ContentEncoding, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(CPEnvelopedData, Encrypt, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(CPEnvelopedData, Decrypt, NULL, ZEND_ACC_PUBLIC)
    /*PHP_ME(CPEnvelopedData, get_Algorithm,       NULL, ZEND_ACC_PUBLIC)*/
    PHP_ME(CPEnvelopedData, get_Recipients, NULL, ZEND_ACC_PUBLIC){NULL, NULL,
                                                                   NULL}};

void enveloped_data_init(TSRMLS_D) {
    zend_class_entry ce;
    INIT_CLASS_ENTRY(ce, "CPEnvelopedData", enveloped_data_methods);
    enveloped_data_ce = zend_register_internal_class(&ce TSRMLS_CC);
    enveloped_data_ce->create_object = enveloped_data_create_handler;
    memcpy(&enveloped_data_obj_handlers, zend_get_std_object_handlers(),
           sizeof(zend_object_handlers));
    enveloped_data_obj_handlers.clone_obj = NULL;
}
