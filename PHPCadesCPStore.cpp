#include "stdafx.h"
#include "CPPCadesCPStore.h"
#include "PHPCadesCPStore.h"
#include "CPPCadesCPCertificates.h"
#include "PHPCadesCPCertificates.h"

using namespace CryptoPro::PKI::CAdES;

PHP_METHOD(CPStore, __construct) {
    store_obj *obj =
        (store_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);
    obj->m_pCppCadesImpl =
        NS_SHARED_PTR::shared_ptr<CPPCadesCPStoreObject>(new CPPCadesCPStoreObject());
}

PHP_METHOD(CPStore, Open) {
    wchar_t *wname;
    char *name;

    long lLocation;
    long lMode;
    CADESCOM_STORE_LOCATION Location;
    int len;
    CAPICOM_STORE_OPEN_MODE Mode;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "lsl", &lLocation,
                              &name, &len, &lMode) == FAILURE) {
        RETURN_WITH_EXCEPTION(E_INVALIDARG);
    }

    Location = (CADESCOM_STORE_LOCATION)lLocation;
    Mode = (CAPICOM_STORE_OPEN_MODE)lMode;

    wname = (wchar_t *)ecalloc(len + 1, sizeof(wchar_t));
    mbstowcs(wname, name, len);

    store_obj *obj =
        (store_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);
    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->Open(Location, wname, Mode));
}

PHP_METHOD(CPStore, Close) {
    store_obj *obj =
        (store_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);
    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->Close());
}

PHP_METHOD(CPStore, get_Certificates) {
    store_obj *obj =
        (store_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);

    object_init_ex(return_value, certs_ce);
    certs_obj *cobj =
        (certs_obj *)zend_object_store_get_object(return_value TSRMLS_CC);

    HR_ERRORCHECK_RETURN(
        obj->m_pCppCadesImpl->get_Certificates(cobj->m_pCppCadesImpl));
}

PHP_METHOD(CPStore, get_Location) {
    store_obj *obj =
        (store_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);

    CADESCOM_STORE_LOCATION this_loc;
    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_Location(&this_loc));

    RETURN_LONG(this_loc)
}

PHP_METHOD(CPStore, get_Name) {
    store_obj *obj =
        (store_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);

    CAtlString wname;
    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_Name(wname));

    RETURN_ATL_STRING(wname)
}

zend_object_handlers store_obj_handlers;
zend_class_entry *store_ce;

void store_free_storage(void *object TSRMLS_DC) {
    store_obj *obj = (store_obj *)object;
    obj->m_pCppCadesImpl.reset();

    zend_hash_destroy(obj->zo.properties);
    FREE_HASHTABLE(obj->zo.properties);

    efree(obj);
}

zend_object_value store_create_handler(zend_class_entry *type TSRMLS_DC) {
    zend_object_value retval;

    store_obj *obj = (store_obj *)emalloc(sizeof(store_obj));
    memset(obj, 0, sizeof(store_obj));
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
        zend_objects_store_put(obj, NULL, store_free_storage, NULL TSRMLS_CC);
    retval.handlers = &store_obj_handlers;

    return retval;
}

//���������� ������� ������ � function entry
zend_function_entry store_methods[] = {
    PHP_ME(CPStore, __construct, NULL, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
    PHP_ME(CPStore, Open, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(CPStore, Close, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(CPStore, get_Certificates, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(CPStore, get_Location, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(CPStore, get_Name, NULL, ZEND_ACC_PUBLIC){NULL, NULL, NULL}};

void store_init(TSRMLS_D) {
    zend_class_entry ce;
    INIT_CLASS_ENTRY(ce, "CPStore", store_methods);
    store_ce = zend_register_internal_class(&ce TSRMLS_CC);
    store_ce->create_object = store_create_handler;
    memcpy(&store_obj_handlers, zend_get_std_object_handlers(),
           sizeof(zend_object_handlers));
    store_obj_handlers.clone_obj = NULL;
}
