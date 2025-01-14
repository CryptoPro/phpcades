#include "stdafx.h"
#include "PHPCadesCPPrivateKey.h"
#include "PHPCadesCPCardholderData.h"
using namespace CryptoPro::PKI::CAdES;

PHP_METHOD(CPPrivateKey, __construct) {
    private_key_obj *obj =
        (private_key_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);
    obj->m_pCppCadesImpl = NS_SHARED_PTR::shared_ptr<CPPCadesCPPrivateKeyObject>(
        new CPPCadesCPPrivateKeyObject());
}

PHP_METHOD(CPPrivateKey, get_ContainerName) {
    CAtlString atlstr;

    private_key_obj *obj =
        (private_key_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_ContainerName(atlstr));

    RETURN_ATL_STRING(atlstr)
}

PHP_METHOD(CPPrivateKey, get_UniqueContainerName) {
    CAtlString atlstr;

    private_key_obj *obj =
        (private_key_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_UniqueContainerName(atlstr));

    RETURN_ATL_STRING(atlstr)
}

PHP_METHOD(CPPrivateKey, get_ProviderName) {
    CAtlString atlstr;

    private_key_obj *obj =
        (private_key_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_ProviderName(atlstr));

    RETURN_ATL_STRING(atlstr)
}

PHP_METHOD(CPPrivateKey, get_ProviderType) {
    CAPICOM_PROV_TYPE type;

    private_key_obj *obj =
        (private_key_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_ProviderType(&type));

    RETURN_LONG(type)
}

PHP_METHOD(CPPrivateKey, get_KeySpec) {
    CAPICOM_KEY_SPEC spec;

    private_key_obj *obj =
        (private_key_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_KeySpec(&spec));

    RETURN_LONG(spec)
}

zend_object_handlers private_key_obj_handlers;
zend_class_entry *private_key_ce;

void private_key_free_storage(void *object TSRMLS_DC) {
    private_key_obj *obj = (private_key_obj *)object;
    obj->m_pCppCadesImpl.reset();

    zend_hash_destroy(obj->zo.properties);
    FREE_HASHTABLE(obj->zo.properties);

    efree(obj);
}

zend_object_value private_key_create_handler(zend_class_entry *type TSRMLS_DC) {
    zend_object_value retval;

    private_key_obj *obj = (private_key_obj *)emalloc(sizeof(private_key_obj));
    memset(obj, 0, sizeof(private_key_obj));
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

    retval.handle = zend_objects_store_put(obj, NULL, private_key_free_storage,
                                           NULL TSRMLS_CC);
    retval.handlers = &private_key_obj_handlers;

    return retval;
}

//���������� ������� ������ � function entry
zend_function_entry private_key_methods[] = {
    PHP_ME(CPPrivateKey, __construct, NULL, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
    PHP_ME(CPPrivateKey, get_ContainerName, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(CPPrivateKey, get_UniqueContainerName, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(CPPrivateKey, get_ProviderName, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(CPPrivateKey, get_ProviderType, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(CPPrivateKey, get_KeySpec, NULL, ZEND_ACC_PUBLIC)
    // PHP_ME(CPPrivateKey, get_UECardholderData,    NULL, ZEND_ACC_PUBLIC)
    // PHP_ME(CPPrivateKey, get_UECardWelcomeText,   NULL, ZEND_ACC_PUBLIC)
    {NULL, NULL, NULL}};

void private_key_init(TSRMLS_D) {
    zend_class_entry ce;
    INIT_CLASS_ENTRY(ce, "CPPrivateKey", private_key_methods);
    private_key_ce = zend_register_internal_class(&ce TSRMLS_CC);
    private_key_ce->create_object = private_key_create_handler;
    memcpy(&private_key_obj_handlers, zend_get_std_object_handlers(),
           sizeof(zend_object_handlers));
    private_key_obj_handlers.clone_obj = NULL;
}
