#include "stdafx.h"
#include "PHPCadesCPEKU.h"
using namespace CryptoPro::PKI::CAdES;

//Методы
PHP_METHOD(CPEKU, __construct) {

    zend_object *zobj = Z_OBJ_P(getThis());
    eku_obj *obj =
        (eku_obj *)((char *)zobj - XtOffsetOf(eku_obj, zobj));
    NS_SHARED_PTR::shared_ptr<CPPCadesCPEKUObject> eku(new CPPCadesCPEKUObject());
    obj->m_pCppCadesImpl = eku;
}

PHP_METHOD(CPEKU, get_Name) {
    CAPICOM_EKU Name;

    zend_object *zobj = Z_OBJ_P(getThis());
    eku_obj *obj =
        (eku_obj *)((char *)zobj - XtOffsetOf(eku_obj, zobj));

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_Name(&Name));

    RETURN_LONG(Name);
}

PHP_METHOD(CPEKU, set_Name) {
    long lName;
    CAPICOM_EKU Name;

    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &lName) ==
        FAILURE)
        RETURN_WITH_EXCEPTION(E_INVALIDARG);
    Name = (CAPICOM_EKU)lName;

    zend_object *zobj = Z_OBJ_P(getThis());
    eku_obj *obj =
        (eku_obj *)((char *)zobj - XtOffsetOf(eku_obj, zobj));

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->put_Name(Name));
}

PHP_METHOD(CPEKU, get_OID) {
    CAtlStringA OID;

    zend_object *zobj = Z_OBJ_P(getThis());
    eku_obj *obj =
        (eku_obj *)((char *)zobj - XtOffsetOf(eku_obj, zobj));
    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_OID(OID));

    RETURN_ATL_STRING_A(OID)
}

PHP_METHOD(CPEKU, set_OID) {
    CAtlStringA OIDw;
    char *OID;
    size_t len;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "s", &OID, &len) ==
        FAILURE)
        RETURN_WITH_EXCEPTION(E_INVALIDARG);

    zend_object *zobj = Z_OBJ_P(getThis());
    eku_obj *obj =
        (eku_obj *)((char *)zobj - XtOffsetOf(eku_obj, zobj));

    OIDw = CAtlString(OID);
    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->put_OID(OIDw));
}

//Вспомогательные функции обертки
zend_object_handlers eku_obj_handlers;
zend_class_entry *eku_ce;

static void eku_free(zend_object *object) {
    eku_obj *obj = (eku_obj *)((char *)object - XtOffsetOf(eku_obj, zobj));
    obj->m_pCppCadesImpl.reset();

    zend_object_std_dtor(object);
}

static zend_object* eku_create_handler(zend_class_entry *ce ) {
    eku_obj *obj = (eku_obj *)emalloc(sizeof(eku_obj) + zend_object_properties_size(ce));
    memset(obj, 0, sizeof(eku_obj) + zend_object_properties_size(ce));
    
    zend_object_std_init(&obj->zobj, ce);
    object_properties_init(&obj->zobj, ce);
    obj->zobj.handlers = &eku_obj_handlers;

    return &obj->zobj;
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpeku_construct, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpeku_get_name, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpeku_set_name, 0, 0, 1)
 ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpeku_get_oid, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpeku_set_oid, 0, 0, 1)
 ZEND_ARG_INFO(0, oid)
ZEND_END_ARG_INFO()

//связывание методов класса в function entry
zend_function_entry eku_methods[] = {
    PHP_ME(CPEKU, __construct, arginfo_cpeku_construct, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
    PHP_ME(CPEKU, get_Name, arginfo_cpeku_get_name, ZEND_ACC_PUBLIC)
    PHP_ME(CPEKU, set_Name, arginfo_cpeku_set_name, ZEND_ACC_PUBLIC)
    PHP_ME(CPEKU, get_OID, arginfo_cpeku_get_oid, ZEND_ACC_PUBLIC)
    PHP_ME(CPEKU, set_OID, arginfo_cpeku_set_oid, ZEND_ACC_PUBLIC)
    {NULL, NULL, NULL}};

void eku_init(void) {
    zend_class_entry ce;
    INIT_CLASS_ENTRY(ce, "CPEKU", eku_methods);
    eku_ce = zend_register_internal_class(&ce );
    eku_ce->create_object = eku_create_handler;
    memcpy(&eku_obj_handlers, zend_get_std_object_handlers(),
           sizeof(zend_object_handlers));
    eku_obj_handlers.clone_obj = NULL;
    eku_obj_handlers.free_obj = eku_free;
    eku_obj_handlers.offset = XtOffsetOf(eku_obj, zobj);
}
