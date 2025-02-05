#include "stdafx.h"
#include "CPPCadesCPStore.h"
#include "PHPCadesCPStore.h"
#include "CPPCadesCPCertificates.h"
#include "PHPCadesCPCertificates.h"

using namespace CryptoPro::PKI::CAdES;

PHP_METHOD(CPStore, __construct) {
    zend_object *zobj = Z_OBJ_P(getThis());
    store_obj *obj =
        (store_obj *)((char *)zobj - XtOffsetOf(store_obj, zobj));
    obj->m_pCppCadesImpl =
        NS_SHARED_PTR::shared_ptr<CPPCadesCPStoreObject>(new CPPCadesCPStoreObject());
}

PHP_METHOD(CPStore, Open) {
    wchar_t *wname;
    char *name;

    long lLocation;
    long lMode;
    CADESCOM_STORE_LOCATION Location;
    size_t len;
    CAPICOM_STORE_OPEN_MODE Mode;

    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lsl", &lLocation,
                              &name, &len, &lMode) == FAILURE) {
        RETURN_WITH_EXCEPTION(E_INVALIDARG);
    }

    Location = (CADESCOM_STORE_LOCATION)lLocation;
    Mode = (CAPICOM_STORE_OPEN_MODE)lMode;

    wname = (wchar_t *)ecalloc(len + 1, sizeof(wchar_t));
    mbstowcs(wname, name, len);

    zend_object *zobj = Z_OBJ_P(getThis());
    store_obj *obj =
        (store_obj *)((char *)zobj - XtOffsetOf(store_obj, zobj));
    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->Open(Location, wname, Mode));
}

PHP_METHOD(CPStore, Close) {
    zend_object *zobj = Z_OBJ_P(getThis());
    store_obj *obj =
        (store_obj *)((char *)zobj - XtOffsetOf(store_obj, zobj));
    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->Close());
}

PHP_METHOD(CPStore, get_Certificates) {
    zend_object *zobj = Z_OBJ_P(getThis());
    store_obj *obj =
        (store_obj *)((char *)zobj - XtOffsetOf(store_obj, zobj));

    object_init_ex(return_value, certs_ce);
    zobj = Z_OBJ_P(return_value);
    certs_obj *cobj =
        (certs_obj *)((char *)zobj - XtOffsetOf(certs_obj, zobj));

    HR_ERRORCHECK_RETURN(
        obj->m_pCppCadesImpl->get_Certificates(cobj->m_pCppCadesImpl));
}

PHP_METHOD(CPStore, get_Location) {
    zend_object *zobj = Z_OBJ_P(getThis());
    store_obj *obj =
        (store_obj *)((char *)zobj - XtOffsetOf(store_obj, zobj));

    CADESCOM_STORE_LOCATION this_loc;
    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_Location(&this_loc));

    RETURN_LONG(this_loc);
}

PHP_METHOD(CPStore, get_Name) {
    zend_object *zobj = Z_OBJ_P(getThis());
    store_obj *obj =
        (store_obj *)((char *)zobj - XtOffsetOf(store_obj, zobj));

    CAtlString wname;
    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_Name(wname));

    RETURN_ATL_STRING(wname);
}

zend_object_handlers store_obj_handlers;
zend_class_entry *store_ce;

static void store_free(zend_object *object ) {
    store_obj *obj = (store_obj *)((char *)object - XtOffsetOf(store_obj, zobj));
    obj->m_pCppCadesImpl.reset();

    zend_object_std_dtor(object);
}

static zend_object* store_create_handler(zend_class_entry *ce ) {
    store_obj *obj = (store_obj *)emalloc(sizeof(store_obj) + zend_object_properties_size(ce));
    memset(obj, 0, sizeof(store_obj) + zend_object_properties_size(ce));
    
    zend_object_std_init(&obj->zobj, ce);
    object_properties_init(&obj->zobj, ce);
    obj->zobj.handlers = &store_obj_handlers;

    return &obj->zobj;
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpstore_construct, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpstore_open, 0, 0, 3)
 ZEND_ARG_INFO(0, location)
 ZEND_ARG_INFO(0, name)
 ZEND_ARG_INFO(0, mode)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpstore_close, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpstore_get_certificates, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpstore_get_location, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpstore_get_name, 0, 0, 0)
ZEND_END_ARG_INFO()

//связывание методов класса в function entry
zend_function_entry store_methods[] = {
    PHP_ME(CPStore, __construct, arginfo_cpstore_construct, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
    PHP_ME(CPStore, Open, arginfo_cpstore_open, ZEND_ACC_PUBLIC)
    PHP_ME(CPStore, Close, arginfo_cpstore_close, ZEND_ACC_PUBLIC)
    PHP_ME(CPStore, get_Certificates, arginfo_cpstore_get_certificates, ZEND_ACC_PUBLIC)
    PHP_ME(CPStore, get_Location, arginfo_cpstore_get_location, ZEND_ACC_PUBLIC)
    PHP_ME(CPStore, get_Name, arginfo_cpstore_get_name, ZEND_ACC_PUBLIC)
    {NULL, NULL, NULL}};

void store_init(void) {
    zend_class_entry ce;
    INIT_CLASS_ENTRY(ce, "CPStore", store_methods);
    store_ce = zend_register_internal_class(&ce );
    store_ce->create_object = store_create_handler;
    memcpy(&store_obj_handlers, zend_get_std_object_handlers(),
           sizeof(zend_object_handlers));
    store_obj_handlers.clone_obj = NULL;
    store_obj_handlers.free_obj = store_free;
    store_obj_handlers.offset = XtOffsetOf(store_obj, zobj);
}
