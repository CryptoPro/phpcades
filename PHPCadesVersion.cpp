#include "stdafx.h"
#include "PHPCadesVersion.h"
using namespace CryptoPro::PKI::CAdES;

//Полное объявление структуры

//Методы
PHP_METHOD(Version, __construct) {
    version_obj *obj =
        (version_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);
    obj->m_pCppCadesImpl =
        boost::shared_ptr<CPPVersionObject>(new CPPVersionObject());
}

PHP_METHOD(Version, get_MajorVersion) {
    unsigned int version;
    version_obj *obj =
        (version_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);
    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_MajorVersion(&version));

    RETURN_LONG(version);
}

PHP_METHOD(Version, get_MinorVersion) {
    unsigned int version;

    version_obj *obj =
        (version_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);
    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_MinorVersion(&version));

    RETURN_LONG(version);
}

PHP_METHOD(Version, get_BuildVersion) {
    unsigned int version;

    version_obj *obj =
        (version_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);
    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_BuildVersion(&version));

    RETURN_LONG(version);
}

PHP_METHOD(Version, toString) {
    CAtlString AtlVersion;

    version_obj *obj =
        (version_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);
    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->toString(AtlVersion));

    RETURN_ATL_STRING(AtlVersion);
}

//Вспомогательные функции обертки
zend_object_handlers version_obj_handlers;
zend_class_entry *version_ce;

void version_free_storage(void *object TSRMLS_DC) {
    version_obj *obj = (version_obj *)object;
    obj->m_pCppCadesImpl.reset();

    zend_hash_destroy(obj->zo.properties);
    FREE_HASHTABLE(obj->zo.properties);

    efree(obj);
}

zend_object_value version_create_handler(zend_class_entry *type TSRMLS_DC) {
    zend_object_value retval;

    version_obj *obj = (version_obj *)emalloc(sizeof(version_obj));
    memset(obj, 0, sizeof(version_obj));
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
        zend_objects_store_put(obj, NULL, version_free_storage, NULL TSRMLS_CC);
    retval.handlers = &version_obj_handlers;

    return retval;
}

//связывание методов класса в function entry
zend_function_entry version_methods[] = {
    PHP_ME(Version, __construct, NULL, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
    PHP_ME(Version, get_MajorVersion, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(Version, get_MinorVersion, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(Version, get_BuildVersion, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(Version, toString, NULL, ZEND_ACC_PUBLIC){NULL, NULL, NULL}};

void version_init(TSRMLS_D) {
    zend_class_entry ce;
    INIT_CLASS_ENTRY(ce, "Version", version_methods);
    version_ce = zend_register_internal_class(&ce TSRMLS_CC);
    version_ce->create_object = version_create_handler;
    memcpy(&version_obj_handlers, zend_get_std_object_handlers(),
           sizeof(zend_object_handlers));
    version_obj_handlers.clone_obj = NULL;
}
