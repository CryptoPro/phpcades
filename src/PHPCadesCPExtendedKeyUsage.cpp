#include "stdafx.h"
#include "PHPCadesCPExtendedKeyUsage.h"
#include "PHPCadesCPEKU.h"
#include "PHPCadesCPEKUs.h"
using namespace CryptoPro::PKI::CAdES;

PHP_METHOD(CPExtendedKeyUsage, __construct) {
    zend_object *zobj = Z_OBJ_P(getThis());
    exku_obj *obj =
        (exku_obj *)((char *)zobj - XtOffsetOf(exku_obj, zobj));
    obj->m_pCppCadesImpl = NS_SHARED_PTR::shared_ptr<CPPCadesCPExtendedKeyUsageObject>(
        new CPPCadesCPExtendedKeyUsageObject());
}

PHP_METHOD(CPExtendedKeyUsage, get_IsPresent) {
    BOOL val;

    zend_object *zobj = Z_OBJ_P(getThis());
    exku_obj *obj =
        (exku_obj *)((char *)zobj - XtOffsetOf(exku_obj, zobj));
    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_IsPresent(&val));

    RETURN_LONG(val);
}

PHP_METHOD(CPExtendedKeyUsage, get_IsCritical) {
    BOOL val;

    zend_object *zobj = Z_OBJ_P(getThis());
    exku_obj *obj =
        (exku_obj *)((char *)zobj - XtOffsetOf(exku_obj, zobj));
    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_IsCritical(&val));

    RETURN_LONG(val);
}

PHP_METHOD(CPExtendedKeyUsage, get_EKUs) {
    zend_object *zobj = Z_OBJ_P(getThis());
    exku_obj *obj =
        (exku_obj *)((char *)zobj - XtOffsetOf(exku_obj, zobj));
    NS_SHARED_PTR::shared_ptr<CPPCadesCPEKUsObject> ptr(new CPPCadesCPEKUsObject());

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_EKUs(ptr));

    object_init_ex(return_value, eku_col_ce);
    zobj = Z_OBJ_P(return_value);
    eku_col_obj *ekus =
        (eku_col_obj *)((char *)zobj - XtOffsetOf(eku_col_obj, zobj));

    ekus->m_pCppCadesImpl = ptr;
    ekus->type = eku_ce;
}

zend_object_handlers exku_obj_handlers;
zend_class_entry *exku_ce;

static void exku_free(zend_object* object) {
    exku_obj *obj = (exku_obj *)((char *)object - XtOffsetOf(exku_obj, zobj));;
    obj->m_pCppCadesImpl.reset();

    zend_object_std_dtor(object);
}

static zend_object* exku_create_handler(zend_class_entry *ce ) {
    exku_obj *obj = (exku_obj *)emalloc(sizeof(exku_obj) + zend_object_properties_size(ce));
    memset(obj, 0, sizeof(exku_obj) + zend_object_properties_size(ce));
    
    zend_object_std_init(&obj->zobj, ce);
    object_properties_init(&obj->zobj, ce);
    obj->zobj.handlers = &exku_obj_handlers;

    return &obj->zobj;
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpextendedkeyusage_construct, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpextendedkeyusage_get_ispresent, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpextendedkeyusage_get_iscritical, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpextendedkeyusage_get_ekus, 0, 0, 0)
ZEND_END_ARG_INFO()

//связывание методов класса в function entry
zend_function_entry exku_methods[] = {
    PHP_ME(CPExtendedKeyUsage, __construct, arginfo_cpextendedkeyusage_construct, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
    PHP_ME(CPExtendedKeyUsage, get_IsPresent, arginfo_cpextendedkeyusage_get_ispresent, ZEND_ACC_PUBLIC)
    PHP_ME(CPExtendedKeyUsage, get_IsCritical, arginfo_cpextendedkeyusage_get_iscritical, ZEND_ACC_PUBLIC) 
    PHP_ME(CPExtendedKeyUsage, get_EKUs, arginfo_cpextendedkeyusage_get_ekus, ZEND_ACC_PUBLIC)
    {NULL, NULL, NULL}};

void exku_init(void) {
    zend_class_entry ce;
    INIT_CLASS_ENTRY(ce, "CPExtendedKeyUsage", exku_methods);
    exku_ce = zend_register_internal_class(&ce );
    exku_ce->create_object = exku_create_handler;
    memcpy(&exku_obj_handlers, zend_get_std_object_handlers(),
           sizeof(zend_object_handlers));
    exku_obj_handlers.clone_obj = NULL;
    exku_obj_handlers.free_obj = exku_free;
    exku_obj_handlers.offset = XtOffsetOf(exku_obj, zobj);
}
