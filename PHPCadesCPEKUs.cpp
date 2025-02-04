#include "stdafx.h"
#include "PHPCadesCPEKU.h"
#include "PHPCadesCPEKUs.h"
using namespace CryptoPro::PKI::CAdES;

//Методы
PHP_METHOD(CPEKUs, __construct) {
    eku_col *obj = (eku_col *)zend_object_store_get_object(getThis() TSRMLS_CC);
    NS_SHARED_PTR::shared_ptr<CPPCadesCPEKUsObject> ptr(new CPPCadesCPEKUsObject());
    obj->m_pCppCadesImpl = ptr;
}

PHP_METHOD(CPEKUs, Add) {
    zval *item;
    eku_col *obj = (eku_col *)zend_object_store_get_object(getThis() TSRMLS_CC);

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "O", &item,
                              obj->type) == FAILURE)
        RETURN_WITH_EXCEPTION(E_INVALIDARG);

    eku_obj *iobj = (eku_obj *)zend_object_store_get_object(item TSRMLS_CC);
    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->Add(iobj->m_pCppCadesImpl));
}

PHP_METHOD(CPEKUs, get_Count) {
    unsigned int count;
    eku_col *obj = (eku_col *)zend_object_store_get_object(getThis() TSRMLS_CC);

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_Count(&count));

    RETURN_LONG(count)
}

PHP_METHOD(CPEKUs, get_Item) {
    long idx;
    NS_SHARED_PTR::shared_ptr<CPPCadesCPEKUObject> item;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &idx) == FAILURE)
        RETURN_WITH_EXCEPTION(E_INVALIDARG);

    eku_col *obj = (eku_col *)zend_object_store_get_object(getThis() TSRMLS_CC);
    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_Item(idx, item));
    if (item == NULL)
        RETURN_WITH_EXCEPTION(ERROR_NO_MORE_ITEMS);

    object_init_ex(return_value, obj->type);
    eku_obj *iobj =
        (eku_obj *)zend_object_store_get_object(return_value TSRMLS_CC);
    iobj->m_pCppCadesImpl = item;
}

PHP_METHOD(CPEKUs, Clear) {
    eku_col *obj = (eku_col *)zend_object_store_get_object(getThis() TSRMLS_CC);
    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->Clear());
}

PHP_METHOD(CPEKUs, Remove) {
    long idx;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &idx) == FAILURE)
        RETURN_WITH_EXCEPTION(E_INVALIDARG);

    eku_col *obj = (eku_col *)zend_object_store_get_object(getThis() TSRMLS_CC);
    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->Remove(idx));
}

//Вспомогательные функции обертки
zend_class_entry *eku_col_ce;
zend_object_handlers eku_col_handlers;

void eku_col_free_storage(void *object TSRMLS_DC) {
    eku_col *obj = (eku_col *)object;
    obj->m_pCppCadesImpl.reset();

    zend_hash_destroy(obj->zo.properties);
    FREE_HASHTABLE(obj->zo.properties);

    efree(obj);
}

zend_object_value eku_col_create_handler(zend_class_entry *type TSRMLS_DC) {
    zend_object_value retval;

    eku_col *obj = (eku_col *)emalloc(sizeof(eku_col));
    memset(obj, 0, sizeof(eku_col));
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
        zend_objects_store_put(obj, NULL, eku_col_free_storage, NULL TSRMLS_CC);
    retval.handlers = &eku_col_handlers;

    return retval;
}

//связывание методов класса в function entry
zend_function_entry eku_col_methods[] = {
    PHP_ME(CPEKUs, __construct, NULL, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
    PHP_ME(CPEKUs, Add, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(CPEKUs, get_Count, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(CPEKUs, get_Item, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(CPEKUs, Clear, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(CPEKUs, Remove, NULL, ZEND_ACC_PUBLIC){NULL, NULL, NULL}};

void eku_col_init(TSRMLS_D) {
    zend_class_entry ce;
    INIT_CLASS_ENTRY(ce, "CPEKUs", eku_col_methods);
    eku_col_ce = zend_register_internal_class(&ce TSRMLS_CC);
    eku_col_ce->create_object = eku_col_create_handler;
    memcpy(&eku_col_handlers, zend_get_std_object_handlers(),
           sizeof(zend_object_handlers));
    eku_col_handlers.clone_obj = NULL;
}
