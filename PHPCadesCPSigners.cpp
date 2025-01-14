#include "stdafx.h"
#include "PHPCadesCPSigners.h"
#include "PHPCadesCPSigner.h"
using namespace CryptoPro::PKI::CAdES;

PHP_METHOD(CPSigners, get_Count) {
    unsigned int value;

    signers_obj *obj =
        (signers_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_Count(&value));

    RETURN_LONG(value)
}

PHP_METHOD(CPSigners, get_Item) {
    long index;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &index) ==
        FAILURE)
        RETURN_WITH_EXCEPTION(E_INVALIDARG);

    NS_SHARED_PTR::shared_ptr<CPPCadesCPSignerObject> pVal;

    signers_obj *obj =
        (signers_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);
    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_Item(index, pVal));

    object_init_ex(return_value, sig_ce);
    sig_obj *Signer =
        (sig_obj *)zend_object_store_get_object(return_value TSRMLS_CC);
    Signer->m_pCppCadesImpl = pVal;
}

void signers_free_storage(void *object TSRMLS_DC) {
    signers_obj *obj = (signers_obj *)object;
    obj->m_pCppCadesImpl.reset();

    zend_hash_destroy(obj->zo.properties);
    FREE_HASHTABLE(obj->zo.properties);

    efree(obj);
}

zend_class_entry *signers_ce;
zend_object_handlers signers_obj_handlers;

zend_function_entry CPSigners_methods[] = {
    PHP_ME(CPSigners, get_Count, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(CPSigners, get_Item, NULL, ZEND_ACC_PUBLIC){NULL, NULL, NULL}};

zend_object_value signers_create_handler(zend_class_entry *type TSRMLS_DC) {
    zend_object_value retval;

    signers_obj *obj = (signers_obj *)emalloc(sizeof(signers_obj));
    memset(obj, 0, sizeof(signers_obj));

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
        zend_objects_store_put(obj, NULL, signers_free_storage, NULL TSRMLS_CC);
    retval.handlers = &signers_obj_handlers;

    return retval;
}

void signers_init(TSRMLS_D) {
    zend_class_entry ce;
    INIT_CLASS_ENTRY(ce, "CPSigners", CPSigners_methods);
    signers_ce = zend_register_internal_class(&ce TSRMLS_CC);
    signers_ce->create_object = signers_create_handler;
    memcpy(&signers_obj_handlers, zend_get_std_object_handlers(),
           sizeof(zend_object_handlers));
    signers_obj_handlers.clone_obj = NULL;
}
