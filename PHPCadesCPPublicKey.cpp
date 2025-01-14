#include "stdafx.h"
#include "PHPCadesCPPublicKey.h"
#include "PHPCadesCPEncodedData.h"
#include "PHPCadesCPOID.h"
using namespace CryptoPro::PKI::CAdES;

PHP_METHOD(CPPublicKey, __construct) {
    public_key_obj *obj =
        (public_key_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);
    obj->m_pCppCadesImpl = NS_SHARED_PTR::shared_ptr<CPPCadesCPPublicKeyObject>(
        new CPPCadesCPPublicKeyObject());
}

PHP_METHOD(CPPublicKey, get_Algorithm) {
    public_key_obj *obj =
        (public_key_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);

    object_init_ex(return_value, oid_ce);
    oid_obj *oobj =
        (oid_obj *)zend_object_store_get_object(return_value TSRMLS_CC);
    oobj->m_pCppCadesImpl =
        NS_SHARED_PTR::shared_ptr<CPPCadesCPOIDObject>(new CPPCadesCPOIDObject());

    HR_ERRORCHECK_RETURN(
        obj->m_pCppCadesImpl->get_Algorithm(oobj->m_pCppCadesImpl));
}

PHP_METHOD(CPPublicKey, get_Length) {
    DWORD len;

    public_key_obj *obj =
        (public_key_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);
    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_Length(&len));

    RETURN_LONG(len)
}

PHP_METHOD(CPPublicKey, get_EncodedKey) {
    public_key_obj *obj =
        (public_key_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);

    object_init_ex(return_value, encoded_data_ce);
    encoded_data_obj *dobj = (encoded_data_obj *)zend_object_store_get_object(
        return_value TSRMLS_CC);

    HR_ERRORCHECK_RETURN(
        obj->m_pCppCadesImpl->get_EncodedKey(dobj->m_pCppCadesImpl));
}

PHP_METHOD(CPPublicKey, get_EncodedParameters) {
    public_key_obj *obj =
        (public_key_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);

    object_init_ex(return_value, encoded_data_ce);
    encoded_data_obj *dobj = (encoded_data_obj *)zend_object_store_get_object(
        return_value TSRMLS_CC);

    HR_ERRORCHECK_RETURN(
        obj->m_pCppCadesImpl->get_EncodedParameters(dobj->m_pCppCadesImpl));
}

zend_object_handlers public_key_obj_handlers;
zend_class_entry *public_key_ce;

void public_key_free_storage(void *object TSRMLS_DC) {
    public_key_obj *obj = (public_key_obj *)object;
    obj->m_pCppCadesImpl.reset();

    zend_hash_destroy(obj->zo.properties);
    FREE_HASHTABLE(obj->zo.properties);

    efree(obj);
}

zend_object_value public_key_create_handler(zend_class_entry *type TSRMLS_DC) {
    zend_object_value retval;

    public_key_obj *obj = (public_key_obj *)emalloc(sizeof(public_key_obj));
    memset(obj, 0, sizeof(public_key_obj));
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

    retval.handle = zend_objects_store_put(obj, NULL, public_key_free_storage,
                                           NULL TSRMLS_CC);
    retval.handlers = &public_key_obj_handlers;

    return retval;
}

//���������� ������� ������ � function entry
zend_function_entry public_key_methods[] = {
    PHP_ME(CPPublicKey, __construct, NULL, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
    PHP_ME(CPPublicKey, get_Algorithm, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(CPPublicKey, get_Length, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(CPPublicKey, get_EncodedKey, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(CPPublicKey, get_EncodedParameters, NULL,
           ZEND_ACC_PUBLIC){NULL, NULL, NULL}};

void public_key_init(TSRMLS_D) {
    zend_class_entry ce;
    INIT_CLASS_ENTRY(ce, "CPPublicKey", public_key_methods);
    public_key_ce = zend_register_internal_class(&ce TSRMLS_CC);
    public_key_ce->create_object = public_key_create_handler;
    memcpy(&public_key_obj_handlers, zend_get_std_object_handlers(),
           sizeof(zend_object_handlers));
    public_key_obj_handlers.clone_obj = NULL;
}
