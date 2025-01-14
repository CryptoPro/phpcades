#include "stdafx.h"
#include "PHPCadesCPRecipients.h"
#include "PHPCadesCPCertificate.h"
using namespace CryptoPro::PKI::CAdES;

PHP_METHOD(CPRecipients, Add) {
    zval *php_var;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "O", &php_var,
                              cert_ce) == FAILURE)
        RETURN_WITH_EXCEPTION(E_INVALIDARG);

    recipients_obj *obj =
        (recipients_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);

    cert_obj *Recipient =
        (cert_obj *)zend_object_store_get_object(php_var TSRMLS_CC);
    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->Add(Recipient->m_pCppCadesImpl));
}

//���� ������, ������� ����� �������� �� ����� ����
PHP_METHOD(CPRecipients, get_Count) {
    unsigned int value;

    recipients_obj *obj =
        (recipients_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_Count(&value));

    RETURN_LONG(value)
}

//���� ������, ������� ����� �������� �� ����� ����
PHP_METHOD(CPRecipients, get_Item) {
    long index;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &index) ==
        FAILURE)
        RETURN_WITH_EXCEPTION(E_INVALIDARG);

    recipients_obj *obj =
        (recipients_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);

    NS_SHARED_PTR::shared_ptr<CPPCadesCPCertificateObject> pVal;
    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_Item(index, pVal));

    object_init_ex(return_value, cert_ce);
    cert_obj *Recipient =
        (cert_obj *)zend_object_store_get_object(return_value TSRMLS_CC);
    Recipient->m_pCppCadesImpl = pVal;
}

PHP_METHOD(CPRecipients, Clear) {
    recipients_obj *obj =
        (recipients_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);
    obj->m_pCppCadesImpl->Clear();
}

PHP_METHOD(CPRecipients, Remove) {
    long index;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &index) ==
        FAILURE)
        RETURN_WITH_EXCEPTION(E_INVALIDARG);

    recipients_obj *obj =
        (recipients_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->Remove(index));
}

zend_class_entry *recipients_class_entry;
zend_object_handlers recipients_handlers;

void recipients_free_storage(void *object TSRMLS_DC) {
    recipients_obj *obj = (recipients_obj *)object;
    obj->m_pCppCadesImpl.reset();

    zend_hash_destroy(obj->zo.properties);
    FREE_HASHTABLE(obj->zo.properties);

    efree(obj);
}

zend_function_entry recipients_methods[] = {
    PHP_ME(CPRecipients, Add, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(CPRecipients, get_Count, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(CPRecipients, get_Item, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(CPRecipients, Clear, NULL, ZEND_ACC_PUBLIC){NULL, NULL, NULL}};

zend_object_value recipients_create_handler(zend_class_entry *type TSRMLS_DC) {
    zend_object_value retval;

    recipients_obj *obj = (recipients_obj *)emalloc(sizeof(recipients_obj));
    memset(obj, 0, sizeof(recipients_obj));

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
    retval.handle = zend_objects_store_put(obj, NULL, recipients_free_storage,
                                           NULL TSRMLS_CC);
    retval.handlers = &recipients_handlers;

    return retval;
}

void recipients_init(TSRMLS_D) {
    zend_class_entry ce;
    INIT_CLASS_ENTRY(ce, "CPRecipients", recipients_methods);
    recipients_class_entry = zend_register_internal_class(&ce TSRMLS_CC);
    recipients_class_entry->create_object = recipients_create_handler;
    memcpy(&recipients_handlers, zend_get_std_object_handlers(),
           sizeof(zend_object_handlers));
    recipients_handlers.clone_obj = NULL;
}
