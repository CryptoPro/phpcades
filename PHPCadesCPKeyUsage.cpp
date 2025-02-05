#include "stdafx.h"
#include "PHPCadesCPKeyUsage.h"
using namespace CryptoPro::PKI::CAdES;

PHP_METHOD(CPKeyUsage, __construct) {
    zend_object *zobj = Z_OBJ_P(getThis());
    ku_obj *obj = (ku_obj *)((char *)zobj - XtOffsetOf(ku_obj, zobj));
    obj->m_pCppCadesImpl = NS_SHARED_PTR::shared_ptr<CPPCadesCPKeyUsageObject>(
        new CPPCadesCPKeyUsageObject());
}

PHP_METHOD(CPKeyUsage, get_IsPresent) {
    BOOL val;

    zend_object *zobj = Z_OBJ_P(getThis());
    ku_obj *obj = (ku_obj *)((char *)zobj - XtOffsetOf(ku_obj, zobj));

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_IsPresent(&val));
    if (val) {
        RETURN_TRUE;
    } else {
        RETURN_FALSE;
    }
}

PHP_METHOD(CPKeyUsage, get_IsCritical) {
    BOOL val;

    zend_object *zobj = Z_OBJ_P(getThis());
    ku_obj *obj = (ku_obj *)((char *)zobj - XtOffsetOf(ku_obj, zobj));

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_IsCritical(&val));
    if (val) {
        RETURN_TRUE;
    } else {
        RETURN_FALSE;
    }
}

PHP_METHOD(CPKeyUsage, get_IsDigitalSignatureEnabled) {
    BOOL val;

    zend_object *zobj = Z_OBJ_P(getThis());
    ku_obj *obj = (ku_obj *)((char *)zobj - XtOffsetOf(ku_obj, zobj));

    HR_ERRORCHECK_RETURN(
        obj->m_pCppCadesImpl->get_IsDigitalSignatureEnabled(&val));
    if (val) {
        RETURN_TRUE;
    } else {
        RETURN_FALSE;
    }
}

PHP_METHOD(CPKeyUsage, get_IsNonRepudiationEnabled) {
    BOOL val;

    zend_object *zobj = Z_OBJ_P(getThis());
    ku_obj *obj = (ku_obj *)((char *)zobj - XtOffsetOf(ku_obj, zobj));

    HR_ERRORCHECK_RETURN(
        obj->m_pCppCadesImpl->get_IsNonRepudiationEnabled(&val));
    if (val) {
        RETURN_TRUE;
    } else {
        RETURN_FALSE;
    }
}

PHP_METHOD(CPKeyUsage, get_IsKeyEnciphermentEnabled) {
    BOOL val;

    zend_object *zobj = Z_OBJ_P(getThis());
    ku_obj *obj = (ku_obj *)((char *)zobj - XtOffsetOf(ku_obj, zobj));

    HR_ERRORCHECK_RETURN(
        obj->m_pCppCadesImpl->get_IsKeyEnciphermentEnabled(&val));
    if (val) {
        RETURN_TRUE;
    } else {
        RETURN_FALSE;
    }
}

PHP_METHOD(CPKeyUsage, get_IsDataEnciphermentEnabled) {
    BOOL val;

    zend_object *zobj = Z_OBJ_P(getThis());
    ku_obj *obj = (ku_obj *)((char *)zobj - XtOffsetOf(ku_obj, zobj));

    HR_ERRORCHECK_RETURN(
        obj->m_pCppCadesImpl->get_IsDataEnciphermentEnabled(&val));
    if (val) {
        RETURN_TRUE;
    } else {
        RETURN_FALSE;
    }
}

PHP_METHOD(CPKeyUsage, get_IsKeyAgreementEnabled) {
    BOOL val;

    zend_object *zobj = Z_OBJ_P(getThis());
    ku_obj *obj = (ku_obj *)((char *)zobj - XtOffsetOf(ku_obj, zobj));

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_IsKeyAgreementEnabled(&val));
    if (val) {
        RETURN_TRUE;
    } else {
        RETURN_FALSE;
    }
}

PHP_METHOD(CPKeyUsage, get_IsKeyCertSignEnabled) {
    BOOL val;

    zend_object *zobj = Z_OBJ_P(getThis());
    ku_obj *obj = (ku_obj *)((char *)zobj - XtOffsetOf(ku_obj, zobj));

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_IsKeyCertSignEnabled(&val));
    if (val) {
        RETURN_TRUE;
    } else {
        RETURN_FALSE;
    }
}

PHP_METHOD(CPKeyUsage, get_IsCRLSignEnabled) {
    BOOL val;

    zend_object *zobj = Z_OBJ_P(getThis());
    ku_obj *obj = (ku_obj *)((char *)zobj - XtOffsetOf(ku_obj, zobj));

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_IsCRLSignEnabled(&val));
    if (val) {
        RETURN_TRUE;
    } else {
        RETURN_FALSE;
    }
}

PHP_METHOD(CPKeyUsage, get_IsEncipherOnlyEnabled) {
    BOOL val;

    zend_object *zobj = Z_OBJ_P(getThis());
    ku_obj *obj = (ku_obj *)((char *)zobj - XtOffsetOf(ku_obj, zobj));

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_IsEncipherOnlyEnabled(&val));
    if (val) {
        RETURN_TRUE;
    } else {
        RETURN_FALSE;
    }
}

PHP_METHOD(CPKeyUsage, get_IsDecipherOnlyEnabled) {
    BOOL val;

    zend_object *zobj = Z_OBJ_P(getThis());
    ku_obj *obj = (ku_obj *)((char *)zobj - XtOffsetOf(ku_obj, zobj));

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_IsDecipherOnlyEnabled(&val));
    if (val) {
        RETURN_TRUE;
    } else {
        RETURN_FALSE;
    }
}

zend_object_handlers ku_obj_handlers;
zend_class_entry *ku_ce;

static void ku_free (zend_object *object ) {
    ku_obj *obj = (ku_obj *)((char *)object - XtOffsetOf(ku_obj, zobj));
    obj->m_pCppCadesImpl.reset();

    zend_object_std_dtor(object);
}

static zend_object* ku_create_handler(zend_class_entry *ce ) {
    ku_obj *obj = (ku_obj *)emalloc(sizeof(ku_obj) + zend_object_properties_size(ce));
    memset(obj, 0, sizeof(ku_obj) + zend_object_properties_size(ce));
    
    zend_object_std_init(&obj->zobj, ce);
    object_properties_init(&obj->zobj, ce);
    obj->zobj.handlers = &ku_obj_handlers;

    return &obj->zobj;
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpkeyusage_construct, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpkeyusage_get_ispresent, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpkeyusage_get_iscritical, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpkeyusage_get_isdigitalsignatureenabled, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpkeyusage_get_isnonrepudationenabled, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpkeyusage_get_iskeyenciphermentenabled, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpkeyusage_get_isdataenciphermentenabled, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpkeyusage_get_iskeyagreementenabled, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpkeyusage_get_iskeycertsignenabled, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpkeyusage_get_iscrlcertsignenabled, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpkeyusage_get_isencipheronlyenabled, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpkeyusage_get_isdecipheronlyenabled, 0, 0, 0)
ZEND_END_ARG_INFO()

//связывание методов класса в function entry
zend_function_entry ku_methods[] = {
    PHP_ME(CPKeyUsage, __construct, arginfo_cpkeyusage_construct, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
    PHP_ME(CPKeyUsage, get_IsPresent, arginfo_cpkeyusage_get_ispresent, ZEND_ACC_PUBLIC)
    PHP_ME(CPKeyUsage, get_IsCritical, arginfo_cpkeyusage_get_iscritical, ZEND_ACC_PUBLIC)
    PHP_ME(CPKeyUsage, get_IsDigitalSignatureEnabled, arginfo_cpkeyusage_get_isdigitalsignatureenabled, ZEND_ACC_PUBLIC)
    PHP_ME(CPKeyUsage, get_IsNonRepudiationEnabled, arginfo_cpkeyusage_get_isnonrepudationenabled, ZEND_ACC_PUBLIC)
    PHP_ME(CPKeyUsage, get_IsKeyEnciphermentEnabled, arginfo_cpkeyusage_get_iskeyenciphermentenabled, ZEND_ACC_PUBLIC)
    PHP_ME(CPKeyUsage, get_IsDataEnciphermentEnabled, arginfo_cpkeyusage_get_isdataenciphermentenabled, ZEND_ACC_PUBLIC)
    PHP_ME(CPKeyUsage, get_IsKeyAgreementEnabled, arginfo_cpkeyusage_get_iskeyagreementenabled, ZEND_ACC_PUBLIC)
    PHP_ME(CPKeyUsage, get_IsKeyCertSignEnabled, arginfo_cpkeyusage_get_iskeycertsignenabled, ZEND_ACC_PUBLIC)
    PHP_ME(CPKeyUsage, get_IsCRLSignEnabled, arginfo_cpkeyusage_get_iscrlcertsignenabled, ZEND_ACC_PUBLIC)
    PHP_ME(CPKeyUsage, get_IsEncipherOnlyEnabled, arginfo_cpkeyusage_get_isencipheronlyenabled, ZEND_ACC_PUBLIC)
    PHP_ME(CPKeyUsage, get_IsDecipherOnlyEnabled, arginfo_cpkeyusage_get_isdecipheronlyenabled, ZEND_ACC_PUBLIC)
    {NULL, NULL, NULL}};

void ku_init(void) {
    zend_class_entry ce;
    INIT_CLASS_ENTRY(ce, "CPKeyUsage", ku_methods);
    ku_ce = zend_register_internal_class(&ce );
    ku_ce->create_object = ku_create_handler;
    memcpy(&ku_obj_handlers, zend_get_std_object_handlers(),
           sizeof(zend_object_handlers));
    ku_obj_handlers.clone_obj = NULL;
    ku_obj_handlers.free_obj = ku_free;
    ku_obj_handlers.offset = XtOffsetOf(ku_obj, zobj);
}
