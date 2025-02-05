#include "stdafx.h"
#include "PHPCadesCPEKU.h"
using namespace CryptoPro::PKI::CAdES;

//Методы
PHP_METHOD(CPEKU, __construct) {

    eku_obj *obj = (eku_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);
    NS_SHARED_PTR::shared_ptr<CPPCadesCPEKUObject> eku(new CPPCadesCPEKUObject());
    obj->m_pCppCadesImpl = eku;
}

PHP_METHOD(CPEKU, get_Name) {
    CAPICOM_EKU Name;

    eku_obj *obj = (eku_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_Name(&Name));

    RETURN_LONG(Name)
}

PHP_METHOD(CPEKU, set_Name) {
    long lName;
    CAPICOM_EKU Name;

    eku_obj *obj = (eku_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &lName) ==
        FAILURE)
        RETURN_WITH_EXCEPTION(E_INVALIDARG);

    Name = (CAPICOM_EKU)lName;

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->put_Name(Name));
}

PHP_METHOD(CPEKU, get_OID) {
    CAtlStringA OID;

    eku_obj *obj = (eku_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);
    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_OID(OID));

    RETURN_ATL_STRING_A(OID)
}

PHP_METHOD(CPEKU, set_OID) {
    CAtlStringA OIDw;
    char *OID;
    int len;

    eku_obj *obj = (eku_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &OID, &len) ==
        FAILURE)
        RETURN_WITH_EXCEPTION(E_INVALIDARG);

    OIDw = CAtlString(OID);
    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->put_OID(OIDw));
}

//Вспомогательные функции обертки
zend_object_handlers eku_obj_handlers;
zend_class_entry *eku_ce;

void eku_free_storage(void *object TSRMLS_DC) {
    eku_obj *obj = (eku_obj *)object;
    obj->m_pCppCadesImpl.reset();

    zend_hash_destroy(obj->zo.properties);
    FREE_HASHTABLE(obj->zo.properties);

    efree(obj);
}

zend_object_value eku_create_handler(zend_class_entry *type TSRMLS_DC) {
    zend_object_value retval;

    eku_obj *obj = (eku_obj *)emalloc(sizeof(eku_obj));
    memset(obj, 0, sizeof(eku_obj));
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
        zend_objects_store_put(obj, NULL, eku_free_storage, NULL TSRMLS_CC);
    retval.handlers = &eku_obj_handlers;

    return retval;
}

//связывание методов класса в function entry
zend_function_entry eku_methods[] = {
    PHP_ME(CPEKU, __construct, NULL, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
    PHP_ME(CPEKU, get_Name, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(CPEKU, set_Name, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(CPEKU, get_OID, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(CPEKU, set_OID, NULL, ZEND_ACC_PUBLIC){NULL, NULL, NULL}};

void eku_init(TSRMLS_D) {
    zend_class_entry ce;
    INIT_CLASS_ENTRY(ce, "CPEKU", eku_methods);
    eku_ce = zend_register_internal_class(&ce TSRMLS_CC);
    eku_ce->create_object = eku_create_handler;
    memcpy(&eku_obj_handlers, zend_get_std_object_handlers(),
           sizeof(zend_object_handlers));
    eku_obj_handlers.clone_obj = NULL;
}
