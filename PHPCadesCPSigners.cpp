#include "stdafx.h"
#include "PHPCadesCPSigners.h"
#include "PHPCadesCPSigner.h"
using namespace CryptoPro::PKI::CAdES;

PHP_METHOD(CPSigners, get_Count) {
    unsigned int value;

    zend_object *zobj = Z_OBJ_P(getThis());
    signers_obj *obj =
        (signers_obj *)((char *)zobj - XtOffsetOf(signers_obj, zobj));

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_Count(&value));

    RETURN_LONG(value);
}

PHP_METHOD(CPSigners, get_Item) {
    long index;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &index) ==
        FAILURE)
        RETURN_WITH_EXCEPTION(E_INVALIDARG);

    NS_SHARED_PTR::shared_ptr<CPPCadesCPSignerObject> pVal;

    zend_object *zobj = Z_OBJ_P(getThis());
    signers_obj *obj =
        (signers_obj *)((char *)zobj - XtOffsetOf(signers_obj, zobj));
    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_Item(index, pVal));

    object_init_ex(return_value, signer_ce);
    zobj = Z_OBJ_P(return_value);
    signer_obj *Signer =
        (signer_obj *)((char *)zobj - XtOffsetOf(signer_obj, zobj));
    Signer->m_pCppCadesImpl = pVal;
}

static void signers_free(zend_object* object) {
    signers_obj *obj = (signers_obj *)((char *)object - XtOffsetOf(signers_obj, zobj));
    obj->m_pCppCadesImpl.reset();

    zend_object_std_dtor(object);
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpsigners_get_count, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpsigners_get_item, 0, 0, 0)
ZEND_END_ARG_INFO()

zend_class_entry *signers_ce;
zend_object_handlers signers_obj_handlers;

zend_function_entry CPSigners_methods[] = {
    PHP_ME(CPSigners, get_Count, arginfo_cpsigners_get_count, ZEND_ACC_PUBLIC)
    PHP_ME(CPSigners, get_Item, arginfo_cpsigners_get_item, ZEND_ACC_PUBLIC)
    {NULL, NULL, NULL}};

static zend_object* signers_create_handler(zend_class_entry *ce ) {
    signers_obj *obj = (signers_obj *)emalloc(sizeof(signers_obj) + zend_object_properties_size(ce));
    memset(obj, 0, sizeof(signers_obj) + zend_object_properties_size(ce));
    
    zend_object_std_init(&obj->zobj, ce);
    object_properties_init(&obj->zobj, ce);
    obj->zobj.handlers = &signers_obj_handlers;

    return &obj->zobj;
}

void signers_init(void) {
    zend_class_entry ce;
    INIT_CLASS_ENTRY(ce, "CPSigners", CPSigners_methods);
    signers_ce = zend_register_internal_class(&ce );
    signers_ce->create_object = signers_create_handler;
    memcpy(&signers_obj_handlers, zend_get_std_object_handlers(),
           sizeof(zend_object_handlers));
    signers_obj_handlers.clone_obj = NULL;
    signers_obj_handlers.free_obj = signers_free;
    signers_obj_handlers.offset = XtOffsetOf(signers_obj, zobj);
}
