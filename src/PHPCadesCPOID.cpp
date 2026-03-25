#include "stdafx.h"
#include "PHPCadesCPOID.h"
using namespace CryptoPro::PKI::CAdES;

PHP_METHOD(CPOID, __construct) {
    zend_object *zobj = Z_OBJ_P(getThis());
    oid_obj *obj = (oid_obj *)((char *)zobj - XtOffsetOf(oid_obj, zobj));
    obj->m_pCppCadesImpl =
        NS_SHARED_PTR::shared_ptr<CPPCadesCPOIDObject>(new CPPCadesCPOIDObject());
}

PHP_METHOD(CPOID, get_Value) {
    NS_SHARED_PTR::shared_ptr<CAtlStringA> atl;

    zend_object *zobj = Z_OBJ_P(getThis());
    oid_obj *obj = (oid_obj *)((char *)zobj - XtOffsetOf(oid_obj, zobj));

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_Value(atl));

    RETURN_ATL_STRING_A((*atl))
}

PHP_METHOD(CPOID, set_Value) {
    char *str;
    size_t len;

    zend_object *zobj = Z_OBJ_P(getThis());
    oid_obj *obj = (oid_obj *)((char *)zobj - XtOffsetOf(oid_obj, zobj));

    if (zend_parse_parameters(ZEND_NUM_ARGS() , "s", &str, &len) ==
        FAILURE)
        RETURN_WITH_EXCEPTION(E_INVALIDARG);

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->put_Value(CAtlStringA(str)));
}

PHP_METHOD(CPOID, get_FriendlyName) {
    CAtlString atlstr;

    zend_object *zobj = Z_OBJ_P(getThis());
    oid_obj *obj = (oid_obj *)((char *)zobj - XtOffsetOf(oid_obj, zobj));

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_FriendlyName(atlstr));

    RETURN_ATL_STRING(atlstr)
}

zend_object_handlers oid_obj_handlers;
zend_class_entry *oid_ce;

static void oid_free(zend_object *object ) {
    oid_obj *obj = (oid_obj *)((char *)object - XtOffsetOf(oid_obj, zobj));
    obj->m_pCppCadesImpl.reset();

    zend_object_std_dtor(object);
}

static zend_object* oid_create_handler(zend_class_entry *ce ) {
    oid_obj *obj = (oid_obj *)emalloc(sizeof(oid_obj) + zend_object_properties_size(ce));
    memset(obj, 0, sizeof(oid_obj) + zend_object_properties_size(ce));
    
    zend_object_std_init(&obj->zobj, ce);
    object_properties_init(&obj->zobj, ce);
    obj->zobj.handlers = &oid_obj_handlers;

    return &obj->zobj;
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpoid_construct, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpoid_get_value, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpoid_set_value, 0, 0, 1)
 ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpoid_get_friendlyname, 0, 0, 0)
ZEND_END_ARG_INFO()

//связывание методов класса в function entry
zend_function_entry oid_methods[] = {
    PHP_ME(CPOID, __construct, arginfo_cpoid_construct, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
    PHP_ME(CPOID, get_Value, arginfo_cpoid_get_value, ZEND_ACC_PUBLIC)
    PHP_ME(CPOID, set_Value, arginfo_cpoid_set_value, ZEND_ACC_PUBLIC)
    PHP_ME(CPOID, get_FriendlyName, arginfo_cpoid_get_friendlyname, ZEND_ACC_PUBLIC)
    {NULL, NULL, NULL}};

void oid_init(void) {
    zend_class_entry ce;
    INIT_CLASS_ENTRY(ce, "CPOID", oid_methods);
    oid_ce = zend_register_internal_class(&ce );
    oid_ce->create_object = oid_create_handler;
    memcpy(&oid_obj_handlers, zend_get_std_object_handlers(),
           sizeof(zend_object_handlers));
    oid_obj_handlers.clone_obj = NULL;
    oid_obj_handlers.free_obj = oid_free;
    oid_obj_handlers.offset = XtOffsetOf(oid_obj, zobj);
}
