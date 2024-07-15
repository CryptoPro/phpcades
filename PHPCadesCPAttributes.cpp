#include "stdafx.h"
#include "PHPCadesCPAttributes.h"
#include "PHPCadesCPAttribute.h"
using namespace CryptoPro::PKI::CAdES;

//Методы
PHP_METHOD(CPAttributes, __construct) {
    attr_col *obj =
        (attr_col *)zend_object_store_get_object(getThis() TSRMLS_CC);
    boost::shared_ptr<CPPCadesCPAttributesObject> ptr(
        new CPPCadesCPAttributesObject());
    obj->m_pCppCadesImpl = ptr;
}

PHP_METHOD(CPAttributes, Add) {
    zval *item;
    attr_col *obj =
        (attr_col *)zend_object_store_get_object(getThis() TSRMLS_CC);
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "O", &item,
                              obj->type) == FAILURE)
        RETURN_WITH_EXCEPTION(E_INVALIDARG);

    attr_obj *iobj = (attr_obj *)zend_object_store_get_object(item TSRMLS_CC);
    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->Add(iobj->m_pCppCadesImpl));
}

PHP_METHOD(CPAttributes, get_Count) {
    long count;
    attr_col *obj =
        (attr_col *)zend_object_store_get_object(getThis() TSRMLS_CC);

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_Count(&count));

    RETURN_LONG(count)
}

PHP_METHOD(CPAttributes, get_Item) {
    long idx;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &idx) == FAILURE)
        RETURN_WITH_EXCEPTION(E_INVALIDARG);

    attr_col *obj =
        (attr_col *)zend_object_store_get_object(getThis() TSRMLS_CC);

    object_init_ex(return_value, attr_ce);
    attr_obj *aobj =
        (attr_obj *)zend_object_store_get_object(return_value TSRMLS_CC);

    HR_ERRORCHECK_RETURN(
        obj->m_pCppCadesImpl->get_Item(idx, aobj->m_pCppCadesImpl));
}

PHP_METHOD(CPAttributes, Clear) {
    attr_col *obj =
        (attr_col *)zend_object_store_get_object(getThis() TSRMLS_CC);
    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->Clear());
}

PHP_METHOD(CPAttributes, Remove) {
    long idx;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &idx) == FAILURE)
        RETURN_WITH_EXCEPTION(E_INVALIDARG);

    attr_col *obj =
        (attr_col *)zend_object_store_get_object(getThis() TSRMLS_CC);
    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->Remove(idx));
}

PHP_METHOD(CPAttributes, Assign) {
    zval *attrs;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "O", &attrs,
                              attr_col_ce) == FAILURE)
        RETURN_WITH_EXCEPTION(E_INVALIDARG);

    attr_col *obj =
        (attr_col *)zend_object_store_get_object(getThis() TSRMLS_CC);
    attr_col *aobj = (attr_col *)zend_object_store_get_object(attrs TSRMLS_CC);
    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->Assign(
        aobj->m_pCppCadesImpl->get_CryptAttributesStruct()));
}

//Вспомогательные функции обертки
zend_class_entry *attr_col_ce;
zend_object_handlers attr_col_handlers;

void attr_col_free_storage(void *object TSRMLS_DC) {
    attr_col *obj = (attr_col *)object;
    obj->m_pCppCadesImpl.reset();

    zend_hash_destroy(obj->zo.properties);
    FREE_HASHTABLE(obj->zo.properties);

    efree(obj);
}

zend_object_value attr_col_create_handler(zend_class_entry *type TSRMLS_DC) {
    zend_object_value retval;

    attr_col *obj = (attr_col *)emalloc(sizeof(attr_col));
    memset(obj, 0, sizeof(attr_col));
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

    retval.handle = zend_objects_store_put(obj, NULL, attr_col_free_storage,
                                           NULL TSRMLS_CC);
    retval.handlers = &attr_col_handlers;

    return retval;
}

//связывание методов класса в function entry
zend_function_entry attr_col_methods[] = {
    PHP_ME(CPAttributes, __construct, NULL, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
    PHP_ME(CPAttributes, Add, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(CPAttributes, get_Count, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(CPAttributes, get_Item, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(CPAttributes, Clear, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(CPAttributes, Remove, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(CPAttributes, Assign, NULL, ZEND_ACC_PUBLIC){NULL, NULL, NULL}};

void attr_col_init(TSRMLS_D) {
    zend_class_entry ce;
    INIT_CLASS_ENTRY(ce, "CPAttributes", attr_col_methods);
    attr_col_ce = zend_register_internal_class(&ce TSRMLS_CC);
    attr_col_ce->create_object = attr_col_create_handler;
    memcpy(&attr_col_handlers, zend_get_std_object_handlers(),
           sizeof(zend_object_handlers));
    attr_col_handlers.clone_obj = NULL;
}
