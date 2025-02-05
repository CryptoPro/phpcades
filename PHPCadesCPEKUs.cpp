#include "stdafx.h"
#include "PHPCadesCPEKU.h"
#include "PHPCadesCPEKUs.h"
using namespace CryptoPro::PKI::CAdES;

//Методы
PHP_METHOD(CPEKUs, __construct) {
    zend_object *zobj = Z_OBJ_P(getThis());
    eku_col_obj *obj =
        (eku_col_obj *)((char *)zobj - XtOffsetOf(eku_col_obj, zobj));
    NS_SHARED_PTR::shared_ptr<CPPCadesCPEKUsObject> ptr(new CPPCadesCPEKUsObject());
    obj->m_pCppCadesImpl = ptr;
}

PHP_METHOD(CPEKUs, Add) {
    zval *item;
    zend_object *zobj = Z_OBJ_P(getThis());
    eku_col_obj *obj =
        (eku_col_obj *)((char *)zobj - XtOffsetOf(eku_col_obj, zobj));

    if (zend_parse_parameters(ZEND_NUM_ARGS() , "O", &item,
                              obj->type) == FAILURE)
        RETURN_WITH_EXCEPTION(E_INVALIDARG);

    zobj = Z_OBJ_P(item);
    eku_obj *iobj = (eku_obj *)((char *)item - XtOffsetOf(eku_obj, zobj));
    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->Add(iobj->m_pCppCadesImpl));
}

PHP_METHOD(CPEKUs, get_Count) {
    unsigned int count;
    zend_object *zobj = Z_OBJ_P(getThis());
    eku_col_obj *obj =
        (eku_col_obj *)((char *)zobj - XtOffsetOf(eku_col_obj, zobj));

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_Count(&count));

    RETURN_LONG(count);
}

PHP_METHOD(CPEKUs, get_Item) {
    long idx;
    NS_SHARED_PTR::shared_ptr<CPPCadesCPEKUObject> item;

    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &idx) == FAILURE)
        RETURN_WITH_EXCEPTION(E_INVALIDARG);

    zend_object *zobj = Z_OBJ_P(getThis());
    eku_col_obj *obj =
        (eku_col_obj *)((char *)zobj - XtOffsetOf(eku_col_obj, zobj));
    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_Item(idx, item));
    if (item == NULL)
        RETURN_WITH_EXCEPTION(ERROR_NO_MORE_ITEMS);

    object_init_ex(return_value, obj->type);
    zobj = Z_OBJ_P(return_value);
    eku_obj *iobj =
        (eku_obj *)((char *)zobj - XtOffsetOf(eku_obj, zobj));
    iobj->m_pCppCadesImpl = item;
}

PHP_METHOD(CPEKUs, Clear) {
    zend_object *zobj = Z_OBJ_P(getThis());
    eku_col_obj *obj =
        (eku_col_obj *)((char *)zobj - XtOffsetOf(eku_col_obj, zobj));
    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->Clear());
}

PHP_METHOD(CPEKUs, Remove) {
    long idx;

    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &idx) == FAILURE)
        RETURN_WITH_EXCEPTION(E_INVALIDARG);

    zend_object *zobj = Z_OBJ_P(getThis());
    eku_col_obj *obj =
        (eku_col_obj *)((char *)zobj - XtOffsetOf(eku_col_obj, zobj));
    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->Remove(idx));
}

//Вспомогательные функции обертки
zend_class_entry *eku_col_ce;
zend_object_handlers eku_col_obj_handlers;

static void eku_col_free(zend_object *object) {
    eku_col_obj *obj = (eku_col_obj *)((char *)object - XtOffsetOf(eku_col_obj, zobj));
    obj->m_pCppCadesImpl.reset();

    zend_object_std_dtor(object);
}

static zend_object* eku_col_create_handler(zend_class_entry *ce ) {
    eku_col_obj *obj = (eku_col_obj *)emalloc(sizeof(eku_col_obj) + zend_object_properties_size(ce));
    memset(obj, 0, sizeof(eku_col_obj) + zend_object_properties_size(ce));
    
    zend_object_std_init(&obj->zobj, ce);
    object_properties_init(&obj->zobj, ce);
    obj->zobj.handlers = &eku_col_obj_handlers;

    return &obj->zobj;
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpekus_construct, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpekus_add, 0, 0, 1)
 ZEND_ARG_INFO(0, item)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpekus_get_count, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpekus_get_item, 0, 0, 1)
 ZEND_ARG_INFO(0, index)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpekus_clear, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpekus_remove, 0, 0, 1)
 ZEND_ARG_INFO(0, index)
ZEND_END_ARG_INFO()

//связывание методов класса в function entry
zend_function_entry eku_col_methods[] = {
    PHP_ME(CPEKUs, __construct, arginfo_cpekus_construct, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
    PHP_ME(CPEKUs, Add, arginfo_cpekus_add, ZEND_ACC_PUBLIC)
    PHP_ME(CPEKUs, get_Count, arginfo_cpekus_get_count, ZEND_ACC_PUBLIC)
    PHP_ME(CPEKUs, get_Item, arginfo_cpekus_get_item, ZEND_ACC_PUBLIC)
    PHP_ME(CPEKUs, Clear, arginfo_cpekus_clear, ZEND_ACC_PUBLIC)
    PHP_ME(CPEKUs, Remove, arginfo_cpekus_remove, ZEND_ACC_PUBLIC)
    {NULL, NULL, NULL}};

void eku_col_init(void) {
    zend_class_entry ce;
    INIT_CLASS_ENTRY(ce, "CPEKUs", eku_col_methods);
    eku_col_ce = zend_register_internal_class(&ce );
    eku_col_ce->create_object = eku_col_create_handler;
    memcpy(&eku_col_obj_handlers, zend_get_std_object_handlers(),
           sizeof(zend_object_handlers));
    eku_col_obj_handlers.clone_obj = NULL;
    eku_col_obj_handlers.free_obj = eku_col_free;
    eku_col_obj_handlers.offset = XtOffsetOf(eku_col_obj, zobj);
}
