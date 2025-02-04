#include "stdafx.h"
#include "PHPCadesCPOID.h"
using namespace CryptoPro::PKI::CAdES;

PHP_METHOD(CPOID, __construct) {
    oid_obj *obj = (oid_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);
    obj->m_pCppCadesImpl =
        NS_SHARED_PTR::shared_ptr<CPPCadesCPOIDObject>(new CPPCadesCPOIDObject());
}

PHP_METHOD(CPOID, get_Value) {
    NS_SHARED_PTR::shared_ptr<CAtlStringA> atl;

    oid_obj *obj = (oid_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_Value(atl));

    RETURN_ATL_STRING_A((*atl))
}

PHP_METHOD(CPOID, set_Value) {
    char *str;
    int len;

    oid_obj *obj = (oid_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &str, &len) ==
        FAILURE)
        RETURN_WITH_EXCEPTION(E_INVALIDARG);

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->put_Value(CAtlStringA(str)));
}

PHP_METHOD(CPOID, get_FriendlyName) {
    CAtlString atlstr;

    oid_obj *obj = (oid_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_FriendlyName(atlstr));

    RETURN_ATL_STRING(atlstr)
}

zend_object_handlers oid_obj_handlers;
zend_class_entry *oid_ce;

void oid_free_storage(void *object TSRMLS_DC) {
    oid_obj *obj = (oid_obj *)object;
    obj->m_pCppCadesImpl.reset();

    zend_hash_destroy(obj->zo.properties);
    FREE_HASHTABLE(obj->zo.properties);

    efree(obj);
}

zend_object_value oid_create_handler(zend_class_entry *type TSRMLS_DC) {
    zend_object_value retval;

    oid_obj *obj = (oid_obj *)emalloc(sizeof(oid_obj));
    memset(obj, 0, sizeof(oid_obj));
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
        zend_objects_store_put(obj, NULL, oid_free_storage, NULL TSRMLS_CC);
    retval.handlers = &oid_obj_handlers;

    return retval;
}

//связывание методов класса в function entry
zend_function_entry oid_methods[] = {
    PHP_ME(CPOID, __construct, NULL, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
    PHP_ME(CPOID, get_Value, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(CPOID, set_Value, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(CPOID, get_FriendlyName, NULL, ZEND_ACC_PUBLIC){NULL, NULL, NULL}};

void oid_init(TSRMLS_D) {
    zend_class_entry ce;
    INIT_CLASS_ENTRY(ce, "CPOID", oid_methods);
    oid_ce = zend_register_internal_class(&ce TSRMLS_CC);
    oid_ce->create_object = oid_create_handler;
    memcpy(&oid_obj_handlers, zend_get_std_object_handlers(),
           sizeof(zend_object_handlers));
    oid_obj_handlers.clone_obj = NULL;
}
