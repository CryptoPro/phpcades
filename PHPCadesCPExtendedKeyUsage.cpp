#include "stdafx.h"
#include "PHPCadesCPExtendedKeyUsage.h"
#include "PHPCadesCPEKU.h"
#include "PHPCadesCPEKUs.h"
using namespace CryptoPro::PKI::CAdES;

PHP_METHOD(CPExtendedKeyUsage, __construct) {

    exku_obj *obj =
        (exku_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);
    obj->m_pCppCadesImpl = NS_SHARED_PTR::shared_ptr<CPPCadesCPExtendedKeyUsageObject>(
        new CPPCadesCPExtendedKeyUsageObject());
}

PHP_METHOD(CPExtendedKeyUsage, get_IsPresent) {
    BOOL val;

    exku_obj *obj =
        (exku_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);
    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_IsPresent(&val));

    RETURN_LONG(val)
}

PHP_METHOD(CPExtendedKeyUsage, get_IsCritical) {
    BOOL val;

    exku_obj *obj =
        (exku_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);
    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_IsCritical(&val));

    RETURN_LONG(val)
}

PHP_METHOD(CPExtendedKeyUsage, get_EKUs) {
    exku_obj *obj =
        (exku_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);
    NS_SHARED_PTR::shared_ptr<CPPCadesCPEKUsObject> ptr(new CPPCadesCPEKUsObject());

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_EKUs(ptr));

    object_init_ex(return_value, eku_col_ce);
    eku_col *ekus =
        (eku_col *)zend_object_store_get_object(return_value TSRMLS_CC);

    ekus->m_pCppCadesImpl = ptr;
    ekus->type = eku_ce;
}

zend_object_handlers exku_obj_handlers;
zend_class_entry *exku_ce;

void exku_free_storage(void *object TSRMLS_DC) {
    exku_obj *obj = (exku_obj *)object;
    obj->m_pCppCadesImpl.reset();

    zend_hash_destroy(obj->zo.properties);
    FREE_HASHTABLE(obj->zo.properties);

    efree(obj);
}

zend_object_value exku_create_handler(zend_class_entry *type TSRMLS_DC) {
    zend_object_value retval;

    exku_obj *obj = (exku_obj *)emalloc(sizeof(exku_obj));
    memset(obj, 0, sizeof(exku_obj));
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
        zend_objects_store_put(obj, NULL, exku_free_storage, NULL TSRMLS_CC);
    retval.handlers = &exku_obj_handlers;

    return retval;
}

//���������� ������� ������ � function entry
zend_function_entry exku_methods[] = {
    PHP_ME(CPExtendedKeyUsage, __construct, NULL,
           ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
    PHP_ME(CPExtendedKeyUsage, get_IsPresent, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(CPExtendedKeyUsage, get_IsCritical, NULL, ZEND_ACC_PUBLIC) PHP_ME(
        CPExtendedKeyUsage, get_EKUs, NULL, ZEND_ACC_PUBLIC){NULL, NULL, NULL}};

void exku_init(TSRMLS_D) {
    zend_class_entry ce;
    INIT_CLASS_ENTRY(ce, "CPExtendedKeyUsage", exku_methods);
    exku_ce = zend_register_internal_class(&ce TSRMLS_CC);
    exku_ce->create_object = exku_create_handler;
    memcpy(&exku_obj_handlers, zend_get_std_object_handlers(),
           sizeof(zend_object_handlers));
    exku_obj_handlers.clone_obj = NULL;
}
