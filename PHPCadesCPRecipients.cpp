#include "stdafx.h"
#include "PHPCadesCPRecipients.h"
#include "PHPCadesCPCertificate.h"
using namespace CryptoPro::PKI::CAdES;

PHP_METHOD(CPRecipients, Add) {
    zval *recipients_zval;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "O", &recipients_zval,
                              cert_ce) == FAILURE)
        RETURN_WITH_EXCEPTION(E_INVALIDARG);

    zend_object *zobj = Z_OBJ_P(getThis());
    recipients_obj *obj =
        (recipients_obj *)((char *)zobj - XtOffsetOf(recipients_obj, zobj));

    zobj = Z_OBJ_P(recipients_zval);
    certificate_obj *Recipient =
        (certificate_obj *)((char *)zobj - XtOffsetOf(certificate_obj, zobj));
    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->Add(Recipient->m_pCppCadesImpl));
}

//ядро метода, которое будет работать на самом деле
PHP_METHOD(CPRecipients, get_Count) {
    unsigned int value;

    zend_object *zobj = Z_OBJ_P(getThis());
    recipients_obj *obj =
        (recipients_obj *)((char *)zobj - XtOffsetOf(recipients_obj, zobj));

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_Count(&value));

    RETURN_LONG(value);
}

//ядро метода, которое будет работать на самом деле
PHP_METHOD(CPRecipients, get_Item) {
    long index;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &index) ==
        FAILURE)
        RETURN_WITH_EXCEPTION(E_INVALIDARG);

    zend_object *zobj = Z_OBJ_P(getThis());
    recipients_obj *obj =
        (recipients_obj *)((char *)zobj - XtOffsetOf(recipients_obj, zobj));

    NS_SHARED_PTR::shared_ptr<CPPCadesCPCertificateObject> pVal;
    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_Item(index, pVal));

    object_init_ex(return_value, cert_ce);
    zobj = Z_OBJ_P(return_value);
    certificate_obj *Recipient =
        (certificate_obj *)((char *)zobj - XtOffsetOf(certificate_obj, zobj));
    Recipient->m_pCppCadesImpl = pVal;
}

PHP_METHOD(CPRecipients, Clear) {
    zend_object *zobj = Z_OBJ_P(getThis());
    recipients_obj *obj =
        (recipients_obj *)((char *)zobj - XtOffsetOf(recipients_obj, zobj));
    obj->m_pCppCadesImpl->Clear();
}

PHP_METHOD(CPRecipients, Remove) {
    long index;

    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &index) ==
        FAILURE)
        RETURN_WITH_EXCEPTION(E_INVALIDARG);

    zend_object *zobj = Z_OBJ_P(getThis());
    recipients_obj *obj =
        (recipients_obj *)((char *)zobj - XtOffsetOf(recipients_obj, zobj));

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->Remove(index));
}

zend_class_entry *recipients_ce;
zend_object_handlers recipients_obj_handlers;

static void recipients_free(zend_object *object ) {
    recipients_obj *obj = (recipients_obj *)((char *)object - XtOffsetOf(recipients_obj, zobj));
    obj->m_pCppCadesImpl.reset();

    zend_object_std_dtor(object);
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_cprecipients_add, 0, 0, 1)
 ZEND_ARG_INFO(0, item)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cprecipients_get_count, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cprecipients_get_item, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cprecipients_clear, 0, 0, 0)
ZEND_END_ARG_INFO()

zend_function_entry recipients_methods[] = {
    PHP_ME(CPRecipients, Add, arginfo_cprecipients_add, ZEND_ACC_PUBLIC)
    PHP_ME(CPRecipients, get_Count, arginfo_cprecipients_get_count, ZEND_ACC_PUBLIC)
    PHP_ME(CPRecipients, get_Item, arginfo_cprecipients_get_item, ZEND_ACC_PUBLIC)
    PHP_ME(CPRecipients, Clear, arginfo_cprecipients_clear, ZEND_ACC_PUBLIC)
    {NULL, NULL, NULL}};

static zend_object* recipients_create_handler(zend_class_entry *ce ) {
    recipients_obj *obj = (recipients_obj *)emalloc(sizeof(recipients_obj) + zend_object_properties_size(ce));
    memset(obj, 0, sizeof(recipients_obj) + zend_object_properties_size(ce));
    
    zend_object_std_init(&obj->zobj, ce);
    object_properties_init(&obj->zobj, ce);
    obj->zobj.handlers = &recipients_obj_handlers;

    return &obj->zobj;
}

void recipients_init(void) {
    zend_class_entry ce;
    INIT_CLASS_ENTRY(ce, "CPRecipients", recipients_methods);
    recipients_ce = zend_register_internal_class(&ce );
    recipients_ce->create_object = recipients_create_handler;
    memcpy(&recipients_obj_handlers, zend_get_std_object_handlers(),
           sizeof(zend_object_handlers));
    recipients_obj_handlers.clone_obj = NULL;
    recipients_obj_handlers.free_obj = recipients_free;
    recipients_obj_handlers.offset = XtOffsetOf(recipients_obj, zobj);
}
