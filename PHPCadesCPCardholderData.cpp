#include "stdafx.h"
#include "PHPCadesCPCardholderData.h"
using namespace CryptoPro::PKI::CAdES;

PHP_METHOD(CPCardholderData, __construct) {
    CPPCadesCardholderDataObject *chd;
    chd_obj *obj = (chd_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);
    chd = new CPPCadesCardholderDataObject();
    obj->m_pCppCadesImpl = chd;
}

PHP_METHOD(CPCardholderData, get_SocialAccountNumber) {
    CAtlString atlstr;

    chd_obj *obj = (chd_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);
    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_SocialAccountNumber(atlstr));

    RETURN_ATL_STRING(atlstr)
}

PHP_METHOD(CPCardholderData, get_OMSNumber) {
    CAtlString atlstr;

    chd_obj *obj = (chd_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);
    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_OMSNumber(atlstr));

    RETURN_ATL_STRING(atlstr)
}

PHP_METHOD(CPCardholderData, get_Name) {
    CAtlString atlstr;

    chd_obj *obj = (chd_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);
    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_Name(atlstr));

    RETURN_ATL_STRING(atlstr)
}

PHP_METHOD(CPCardholderData, get_FirstName) {
    CAtlString atlstr;

    chd_obj *obj = (chd_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);
    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_FirstName(atlstr));

    RETURN_ATL_STRING(atlstr)
}

PHP_METHOD(CPCardholderData, get_LastName) {
    CAtlString atlstr;

    chd_obj *obj = (chd_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);
    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_LastName(atlstr));

    RETURN_ATL_STRING(atlstr)
}

PHP_METHOD(CPCardholderData, get_SecondName) {
    CAtlString atlstr;

    chd_obj *obj = (chd_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);
    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_SecondName(atlstr));

    RETURN_ATL_STRING(atlstr)
}

PHP_METHOD(CPCardholderData, get_CardIssuerAddress) {
    CAtlString atlstr;

    chd_obj *obj = (chd_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);
    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_CardIssuerAddress(atlstr));

    RETURN_ATL_STRING(atlstr)
}

PHP_METHOD(CPCardholderData, get_DateOfBirth) {
    CAtlString atlstr;

    chd_obj *obj = (chd_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);
    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_DateOfBirth(atlstr));

    RETURN_ATL_STRING(atlstr)
}

PHP_METHOD(CPCardholderData, get_PlaceOfBirth) {
    CAtlString atlstr;

    chd_obj *obj = (chd_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);
    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_PlaceOfBirth(atlstr));

    RETURN_ATL_STRING(atlstr)
}

PHP_METHOD(CPCardholderData, get_SexString) {
    CAtlString atlstr;

    chd_obj *obj = (chd_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);
    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_SexString(atlstr));

    RETURN_ATL_STRING(atlstr)
}

PHP_METHOD(CPCardholderData, get_Sex) {
    CADESCOM_HUMAN_SEXES sex;

    chd_obj *obj = (chd_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);
    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_Sex(&sex));

    RETURN_LONG(sex)
}

zend_object_handlers chd_obj_handlers;
zend_class_entry *chd_ce;

void chd_free_storage(void *object TSRMLS_DC) {
    chd_obj *obj = (chd_obj *)object;
    delete obj->m_pCppCadesImpl;

    zend_hash_destroy(obj->zo.properties);
    FREE_HASHTABLE(obj->zo.properties);

    efree(obj);
}

zend_object_value chd_create_handler(zend_class_entry *type TSRMLS_DC) {
    zend_object_value retval;

    chd_obj *obj = (chd_obj *)emalloc(sizeof(chd_obj));
    memset(obj, 0, sizeof(chd_obj));
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
        zend_objects_store_put(obj, NULL, chd_free_storage, NULL TSRMLS_CC);
    retval.handlers = &chd_obj_handlers;

    return retval;
}

//связывание методов класса в function entry
zend_function_entry chd_methods[] = {
    PHP_ME(CPCardholderData, __construct, NULL, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
    PHP_ME(CPCardholderData, get_SocialAccountNumber, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(CPCardholderData, get_OMSNumber, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(CPCardholderData, get_Name, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(CPCardholderData, get_FirstName, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(CPCardholderData, get_LastName, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(CPCardholderData, get_SecondName, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(CPCardholderData, get_CardIssuerAddress, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(CPCardholderData, get_DateOfBirth, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(CPCardholderData, get_PlaceOfBirth, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(CPCardholderData, get_SexString, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(CPCardholderData, get_Sex, NULL, ZEND_ACC_PUBLIC){NULL, NULL, NULL}};

void chd_init(TSRMLS_D) {
    zend_class_entry ce;
    INIT_CLASS_ENTRY(ce, "CPCardholderData", chd_methods);
    chd_ce = zend_register_internal_class(&ce TSRMLS_CC);
    chd_ce->create_object = chd_create_handler;
    memcpy(&chd_obj_handlers, zend_get_std_object_handlers(),
           sizeof(zend_object_handlers));
    chd_obj_handlers.clone_obj = NULL;
}
