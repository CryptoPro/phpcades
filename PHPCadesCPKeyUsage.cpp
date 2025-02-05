#include "stdafx.h"
#include "PHPCadesCPKeyUsage.h"
using namespace CryptoPro::PKI::CAdES;

PHP_METHOD(CPKeyUsage, __construct) {
    ku_obj *obj = (ku_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);
    obj->m_pCppCadesImpl = NS_SHARED_PTR::shared_ptr<CPPCadesCPKeyUsageObject>(
        new CPPCadesCPKeyUsageObject());
}

PHP_METHOD(CPKeyUsage, get_IsPresent) {
    BOOL val;

    ku_obj *obj = (ku_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_IsPresent(&val));
    if (val) {
        RETURN_TRUE
    } else {
        RETURN_FALSE
    }
}

PHP_METHOD(CPKeyUsage, get_IsCritical) {
    BOOL val;

    ku_obj *obj = (ku_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_IsCritical(&val));
    if (val) {
        RETURN_TRUE
    } else {
        RETURN_FALSE
    }
}

PHP_METHOD(CPKeyUsage, get_IsDigitalSignatureEnabled) {
    BOOL val;

    ku_obj *obj = (ku_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);

    HR_ERRORCHECK_RETURN(
        obj->m_pCppCadesImpl->get_IsDigitalSignatureEnabled(&val));
    if (val) {
        RETURN_TRUE
    } else {
        RETURN_FALSE
    }
}

PHP_METHOD(CPKeyUsage, get_IsNonRepudiationEnabled) {
    BOOL val;

    ku_obj *obj = (ku_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);

    HR_ERRORCHECK_RETURN(
        obj->m_pCppCadesImpl->get_IsNonRepudiationEnabled(&val));
    if (val) {
        RETURN_TRUE
    } else {
        RETURN_FALSE
    }
}

PHP_METHOD(CPKeyUsage, get_IsKeyEnciphermentEnabled) {
    BOOL val;

    ku_obj *obj = (ku_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);

    HR_ERRORCHECK_RETURN(
        obj->m_pCppCadesImpl->get_IsKeyEnciphermentEnabled(&val));
    if (val) {
        RETURN_TRUE
    } else {
        RETURN_FALSE
    }
}

PHP_METHOD(CPKeyUsage, get_IsDataEnciphermentEnabled) {
    BOOL val;

    ku_obj *obj = (ku_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);

    HR_ERRORCHECK_RETURN(
        obj->m_pCppCadesImpl->get_IsDataEnciphermentEnabled(&val));
    if (val) {
        RETURN_TRUE
    } else {
        RETURN_FALSE
    }
}

PHP_METHOD(CPKeyUsage, get_IsKeyAgreementEnabled) {
    BOOL val;

    ku_obj *obj = (ku_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_IsKeyAgreementEnabled(&val));
    if (val) {
        RETURN_TRUE
    } else {
        RETURN_FALSE
    }
}

PHP_METHOD(CPKeyUsage, get_IsKeyCertSignEnabled) {
    BOOL val;

    ku_obj *obj = (ku_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_IsKeyCertSignEnabled(&val));
    if (val) {
        RETURN_TRUE
    } else {
        RETURN_FALSE
    }
}

PHP_METHOD(CPKeyUsage, get_IsCRLSignEnabled) {
    BOOL val;

    ku_obj *obj = (ku_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_IsCRLSignEnabled(&val));
    if (val) {
        RETURN_TRUE
    } else {
        RETURN_FALSE
    }
}

PHP_METHOD(CPKeyUsage, get_IsEncipherOnlyEnabled) {
    BOOL val;

    ku_obj *obj = (ku_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_IsEncipherOnlyEnabled(&val));
    if (val) {
        RETURN_TRUE
    } else {
        RETURN_FALSE
    }
}

PHP_METHOD(CPKeyUsage, get_IsDecipherOnlyEnabled) {
    BOOL val;

    ku_obj *obj = (ku_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_IsDecipherOnlyEnabled(&val));
    if (val) {
        RETURN_TRUE
    } else {
        RETURN_FALSE
    }
}

zend_object_handlers ku_obj_handlers;
zend_class_entry *ku_ce;

void ku_free_storage(void *object TSRMLS_DC) {
    ku_obj *obj = (ku_obj *)object;
    obj->m_pCppCadesImpl.reset();

    zend_hash_destroy(obj->zo.properties);
    FREE_HASHTABLE(obj->zo.properties);

    efree(obj);
}

zend_object_value ku_create_handler(zend_class_entry *type TSRMLS_DC) {
    zend_object_value retval;

    ku_obj *obj = (ku_obj *)emalloc(sizeof(ku_obj));
    memset(obj, 0, sizeof(ku_obj));
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
        zend_objects_store_put(obj, NULL, ku_free_storage, NULL TSRMLS_CC);
    retval.handlers = &ku_obj_handlers;

    return retval;
}

//связывание методов класса в function entry
zend_function_entry ku_methods[] = {
    PHP_ME(CPKeyUsage, __construct, NULL, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
    PHP_ME(CPKeyUsage, get_IsPresent, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(CPKeyUsage, get_IsCritical, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(CPKeyUsage, get_IsDigitalSignatureEnabled, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(CPKeyUsage, get_IsNonRepudiationEnabled, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(CPKeyUsage, get_IsKeyEnciphermentEnabled, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(CPKeyUsage, get_IsDataEnciphermentEnabled, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(CPKeyUsage, get_IsKeyAgreementEnabled, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(CPKeyUsage, get_IsKeyCertSignEnabled, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(CPKeyUsage, get_IsCRLSignEnabled, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(CPKeyUsage, get_IsEncipherOnlyEnabled, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(CPKeyUsage, get_IsDecipherOnlyEnabled, NULL,
           ZEND_ACC_PUBLIC){NULL, NULL, NULL}};

void ku_init(TSRMLS_D) {
    zend_class_entry ce;
    INIT_CLASS_ENTRY(ce, "CPKeyUsage", ku_methods);
    ku_ce = zend_register_internal_class(&ce TSRMLS_CC);
    ku_ce->create_object = ku_create_handler;
    memcpy(&ku_obj_handlers, zend_get_std_object_handlers(),
           sizeof(zend_object_handlers));
    ku_obj_handlers.clone_obj = NULL;
}
