#include "stdafx.h"
#include "PHPCadesCPAttributes.h"
#include "PHPCadesCPAttribute.h"
using namespace CryptoPro::PKI::CAdES;

//Методы
PHP_METHOD(CPAttributes, __construct) {
    zend_object *zobj = Z_OBJ_P(getThis());
    attributes_col_obj *obj =
        (attributes_col_obj *)((char *)zobj - XtOffsetOf(attributes_col_obj, zobj));
    NS_SHARED_PTR::shared_ptr<CPPCadesCPAttributesObject> ptr(
        new CPPCadesCPAttributesObject());
    obj->m_pCppCadesImpl = ptr;
}

PHP_METHOD(CPAttributes, Add) {
    zval *item;
    zend_object *zobj = Z_OBJ_P(getThis());
    attributes_col_obj *obj =
        (attributes_col_obj *)((char *)zobj - XtOffsetOf(attributes_col_obj, zobj));
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "O", &item,
                              obj->type) == FAILURE)
        RETURN_WITH_EXCEPTION(E_INVALIDARG);

    zobj = Z_OBJ_P(item);
    attribute_obj *iobj = 
        (attribute_obj *)((char *)zobj - XtOffsetOf(attribute_obj, zobj));
    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->Add(iobj->m_pCppCadesImpl));
}

PHP_METHOD(CPAttributes, get_Count) {
    long count;
    zend_object *zobj = Z_OBJ_P(getThis());
    attributes_col_obj *obj =
        (attributes_col_obj *)((char *)zobj - XtOffsetOf(attributes_col_obj, zobj));

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_Count(&count));

    RETURN_LONG(count);
}

PHP_METHOD(CPAttributes, get_Item) {
    long idx;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &idx) == FAILURE)
        RETURN_WITH_EXCEPTION(E_INVALIDARG);

    zend_object *zobj = Z_OBJ_P(getThis());
    attributes_col_obj *obj =
        (attributes_col_obj *)((char *)zobj - XtOffsetOf(attributes_col_obj, zobj));

    object_init_ex(return_value, attribute_ce);
    zobj = Z_OBJ_P(return_value);
    attribute_obj *aobj =
        (attribute_obj *)((char *)zobj - XtOffsetOf(attribute_obj, zobj));

    HR_ERRORCHECK_RETURN(
        obj->m_pCppCadesImpl->get_Item(idx, aobj->m_pCppCadesImpl));
}

PHP_METHOD(CPAttributes, Clear) {
    zend_object *zobj = Z_OBJ_P(getThis());
    attributes_col_obj *obj =
        (attributes_col_obj *)((char *)zobj - XtOffsetOf(attributes_col_obj, zobj));
    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->Clear());
}

PHP_METHOD(CPAttributes, Remove) {
    long idx;

    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &idx) == FAILURE)
        RETURN_WITH_EXCEPTION(E_INVALIDARG);

    zend_object *zobj = Z_OBJ_P(getThis());
    attributes_col_obj *obj =
        (attributes_col_obj *)((char *)zobj - XtOffsetOf(attributes_col_obj, zobj));
    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->Remove(idx));
}

PHP_METHOD(CPAttributes, Assign) {
    zval *attrs;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "O", &attrs,
                              attributes_col_ce) == FAILURE)
        RETURN_WITH_EXCEPTION(E_INVALIDARG);

    zend_object *zobj = Z_OBJ_P(getThis());
    attributes_col_obj *obj =
        (attributes_col_obj *)((char *)zobj - XtOffsetOf(attributes_col_obj, zobj));

    zobj = Z_OBJ_P(attrs);
    attributes_col_obj *aobj = 
        (attributes_col_obj *)((char *)zobj - XtOffsetOf(attributes_col_obj, zobj));

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->Assign(
        aobj->m_pCppCadesImpl->get_CryptAttributesStruct()));
}

//Вспомогательные функции обертки
zend_class_entry *attributes_col_ce;
zend_object_handlers attributes_col_obj_handlers;

static void attributes_col_obj_free(zend_object *object ) {
    attributes_col_obj *obj = (attributes_col_obj *)((char *)object - XtOffsetOf(attributes_col_obj, zobj));
    obj->m_pCppCadesImpl.reset();

    zend_object_std_dtor(object);
}

static zend_object* attributes_col_obj_create_handler(zend_class_entry *ce ) {
    attributes_col_obj *obj = (attributes_col_obj *)emalloc(sizeof(attributes_col_obj) + zend_object_properties_size(ce));
    memset(obj, 0, sizeof(attributes_col_obj) + zend_object_properties_size(ce));
    
    zend_object_std_init(&obj->zobj, ce);
    object_properties_init(&obj->zobj, ce);
    obj->zobj.handlers = &attributes_col_obj_handlers;

    return &obj->zobj;
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpattributes_construct, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpattribute_add, 0, 0, 1)
 ZEND_ARG_INFO(0, item)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpattributes_get_count, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpattributes_get_item, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpattributes_clear, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpattribute_remove, 0, 0, 1)
 ZEND_ARG_INFO(0, index)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpattribute_assign, 0, 0, 1)
 ZEND_ARG_INFO(0, object)
ZEND_END_ARG_INFO()

//связывание методов класса в function entry
zend_function_entry attributes_col_obj_methods[] = {
    PHP_ME(CPAttributes, __construct, arginfo_cpattributes_construct, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
    PHP_ME(CPAttributes, Add, arginfo_cpattribute_add, ZEND_ACC_PUBLIC)
    PHP_ME(CPAttributes, get_Count, arginfo_cpattributes_get_count, ZEND_ACC_PUBLIC)
    PHP_ME(CPAttributes, get_Item, arginfo_cpattributes_get_item, ZEND_ACC_PUBLIC)
    PHP_ME(CPAttributes, Clear, arginfo_cpattributes_clear, ZEND_ACC_PUBLIC)
    PHP_ME(CPAttributes, Remove, arginfo_cpattribute_remove, ZEND_ACC_PUBLIC)
    PHP_ME(CPAttributes, Assign, arginfo_cpattribute_assign, ZEND_ACC_PUBLIC)
    {NULL, NULL, NULL}};

void attr_col_init(void) {
    zend_class_entry ce;
    INIT_CLASS_ENTRY(ce, "CPAttributes", attributes_col_obj_methods);
    attributes_col_ce = zend_register_internal_class(&ce );
    attributes_col_ce->create_object = attributes_col_obj_create_handler;
    memcpy(&attributes_col_obj_handlers, zend_get_std_object_handlers(),
           sizeof(zend_object_handlers));
    attributes_col_obj_handlers.clone_obj = NULL;
    attributes_col_obj_handlers.free_obj = attributes_col_obj_free;
    attributes_col_obj_handlers.offset = XtOffsetOf(attributes_col_obj, zobj);
}
