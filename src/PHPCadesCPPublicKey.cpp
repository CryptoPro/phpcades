#include "stdafx.h"
#include "PHPCadesCPPublicKey.h"
#include "PHPCadesCPEncodedData.h"
#include "PHPCadesCPOID.h"
using namespace CryptoPro::PKI::CAdES;

PHP_METHOD(CPPublicKey, __construct) {
    zend_object *zobj = Z_OBJ_P(getThis());
    public_key_obj *obj =
        (public_key_obj *)((char *)zobj - XtOffsetOf(public_key_obj, zobj));
    obj->m_pCppCadesImpl = NS_SHARED_PTR::shared_ptr<CPPCadesCPPublicKeyObject>(
        new CPPCadesCPPublicKeyObject());
}

PHP_METHOD(CPPublicKey, get_Algorithm) {
    zend_object *zobj = Z_OBJ_P(getThis());
    public_key_obj *obj =
        (public_key_obj *)((char *)zobj - XtOffsetOf(public_key_obj, zobj));

    object_init_ex(return_value, oid_ce);
    zobj = Z_OBJ_P(return_value);
    oid_obj *oobj =
        (oid_obj *)((char *)zobj - XtOffsetOf(oid_obj, zobj));
    oobj->m_pCppCadesImpl =
        NS_SHARED_PTR::shared_ptr<CPPCadesCPOIDObject>(new CPPCadesCPOIDObject());

    HR_ERRORCHECK_RETURN(
        obj->m_pCppCadesImpl->get_Algorithm(oobj->m_pCppCadesImpl));
}

PHP_METHOD(CPPublicKey, get_Length) {
    DWORD len;

    zend_object *zobj = Z_OBJ_P(getThis());
    public_key_obj *obj =
        (public_key_obj *)((char *)zobj - XtOffsetOf(public_key_obj, zobj));
    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_Length(&len));

    RETURN_LONG(len);
}

PHP_METHOD(CPPublicKey, get_EncodedKey) {
    zend_object *zobj = Z_OBJ_P(getThis());
    public_key_obj *obj =
        (public_key_obj *)((char *)zobj - XtOffsetOf(public_key_obj, zobj));

    object_init_ex(return_value, encoded_data_ce);
    zobj = Z_OBJ_P(return_value);
    encoded_data_obj *dobj = (encoded_data_obj *)((char *)zobj - XtOffsetOf(encoded_data_obj, zobj));

    HR_ERRORCHECK_RETURN(
        obj->m_pCppCadesImpl->get_EncodedKey(dobj->m_pCppCadesImpl));
}

PHP_METHOD(CPPublicKey, get_EncodedParameters) {
    zend_object *zobj = Z_OBJ_P(getThis());
    public_key_obj *obj =
        (public_key_obj *)((char *)zobj - XtOffsetOf(public_key_obj, zobj));

    object_init_ex(return_value, encoded_data_ce);
    zobj = Z_OBJ_P(return_value);
    encoded_data_obj *dobj = (encoded_data_obj *)((char *)zobj - XtOffsetOf(encoded_data_obj, zobj));


    HR_ERRORCHECK_RETURN(
        obj->m_pCppCadesImpl->get_EncodedParameters(dobj->m_pCppCadesImpl));
}

zend_object_handlers public_key_obj_handlers;
zend_class_entry *public_key_ce;

static void public_key_free(zend_object *object ) {
    public_key_obj *obj = (public_key_obj *)((char *)object - XtOffsetOf(public_key_obj, zobj));
    obj->m_pCppCadesImpl.reset();

    zend_object_std_dtor(object);
}

static zend_object* public_key_create_handler(zend_class_entry *ce ) {
    public_key_obj *obj = (public_key_obj *)emalloc(sizeof(public_key_obj) + zend_object_properties_size(ce));
    memset(obj, 0, sizeof(public_key_obj) + zend_object_properties_size(ce));
    
    zend_object_std_init(&obj->zobj, ce);
    object_properties_init(&obj->zobj, ce);
    obj->zobj.handlers = &public_key_obj_handlers;

    return &obj->zobj;
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_cppublickey_construct, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cppublickey_get_algorithm, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cppublickey_get_length, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cppublickey_get_encodedkey, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cppublickey_get_encodedparameters, 0, 0, 0)
ZEND_END_ARG_INFO()

//связывание методов класса в function entry
zend_function_entry public_key_methods[] = {
    PHP_ME(CPPublicKey, __construct, arginfo_cppublickey_construct, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
    PHP_ME(CPPublicKey, get_Algorithm, arginfo_cppublickey_get_algorithm, ZEND_ACC_PUBLIC)
    PHP_ME(CPPublicKey, get_Length, arginfo_cppublickey_get_length, ZEND_ACC_PUBLIC)
    PHP_ME(CPPublicKey, get_EncodedKey, arginfo_cppublickey_get_encodedkey, ZEND_ACC_PUBLIC)
    PHP_ME(CPPublicKey, get_EncodedParameters, arginfo_cppublickey_get_encodedparameters, ZEND_ACC_PUBLIC)
    {NULL, NULL, NULL}};

void public_key_init(void) {
    zend_class_entry ce;
    INIT_CLASS_ENTRY(ce, "CPPublicKey", public_key_methods);
    public_key_ce = zend_register_internal_class(&ce );
    public_key_ce->create_object = public_key_create_handler;
    memcpy(&public_key_obj_handlers, zend_get_std_object_handlers(),
           sizeof(zend_object_handlers));
    public_key_obj_handlers.clone_obj = NULL;
    public_key_obj_handlers.free_obj = public_key_free;
    public_key_obj_handlers.offset = XtOffsetOf(public_key_obj, zobj);
}
