#include "stdafx.h"
#include "CPPCadesCPCertificates.h"
#include "PHPCadesCPCertificates.h"
#include "PHPCadesCPCertificate.h"
using namespace CryptoPro::PKI::CAdES;

PHP_METHOD(CPCertificates, __construct) {
    zend_object *zobj = Z_OBJ_P(getThis());
    certs_obj *obj =
        (certs_obj *)((char *)zobj - XtOffsetOf(certs_obj, zobj));
    obj->m_pCppCadesImpl = NS_SHARED_PTR::shared_ptr<CPPCadesCPCertificatesObject>(
        new CPPCadesCPCertificatesObject());
}

PHP_METHOD(CPCertificates, Find) {
    FindCriteria findCriteria;
    long lType;
    CAPICOM_CERTIFICATE_FIND_TYPE Type;
    zval *query;
    long lValidOnly;
    BOOL bValidOnly;

    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lzl", &lType, &query,
                              &lValidOnly) == FAILURE)
        RETURN_WITH_EXCEPTION(E_INVALIDARG);

    Type = (CAPICOM_CERTIFICATE_FIND_TYPE)lType;
    bValidOnly = (BOOL)lValidOnly;

    switch (Type) {
    case CAPICOM_CERTIFICATE_FIND_SHA1_HASH:
    case CAPICOM_CERTIFICATE_FIND_SUBJECT_NAME:
    case CAPICOM_CERTIFICATE_FIND_ISSUER_NAME:
    case CAPICOM_CERTIFICATE_FIND_ROOT_NAME:
    case CAPICOM_CERTIFICATE_FIND_TEMPLATE_NAME:
    case CAPICOM_CERTIFICATE_FIND_CERTIFICATE_POLICY: {
        if (Z_TYPE_P(query) != IS_STRING) {
            RETURN_WITH_EXCEPTION(E_INVALIDARG);
        }

        findCriteria.str = CAtlString(query->value.str->val);
        findCriteria.dwCriteriaFlag = FIND_CRITERIA_STRING;
        break;
    }
    case CAPICOM_CERTIFICATE_FIND_EXTENDED_PROPERTY:
    case CAPICOM_CERTIFICATE_FIND_KEY_USAGE: {
        if (Z_TYPE_P(query) != IS_LONG) {
            RETURN_WITH_EXCEPTION(E_INVALIDARG);
        }
        findCriteria.dwCriteriaFlag = FIND_CRITERIA_DWORD;
        findCriteria.dword = static_cast<DWORD>(Z_LVAL_P(query));
        break;
    }
    case CAPICOM_CERTIFICATE_FIND_EXTENSION:
    case CAPICOM_CERTIFICATE_FIND_APPLICATION_POLICY: {
        if (Z_TYPE_P(query) == IS_STRING) {
            findCriteria.str = CAtlString(query->value.str->val);
            findCriteria.dwCriteriaFlag = FIND_CRITERIA_STRING;
        } else {
            if (Z_TYPE_P(query) != IS_LONG) {
                RETURN_WITH_EXCEPTION(E_INVALIDARG);
            }
            findCriteria.dwCriteriaFlag = FIND_CRITERIA_DWORD;
            findCriteria.dword = static_cast<DWORD>(Z_LVAL_P(query));
        }
        break;
    }
    case CAPICOM_CERTIFICATE_FIND_TIME_VALID:
    case CAPICOM_CERTIFICATE_FIND_TIME_NOT_YET_VALID:
    case CAPICOM_CERTIFICATE_FIND_TIME_EXPIRED: {
        if (Z_TYPE_P(query) != IS_STRING) {
            RETURN_WITH_EXCEPTION(E_INVALIDARG);
        }
        CryptoPro::CDateTime *utcDate;
        try {
            utcDate = new CryptoPro::CDateTime(Z_STRVAL_P(query));
        } catch (...) {
            RETURN_WITH_EXCEPTION(E_INVALIDARG);
        }
        findCriteria.dwCriteriaFlag = FIND_CRITERIA_DATE;
        findCriteria.date = *utcDate;
        break;
    }
    default:
        RETURN_WITH_EXCEPTION(E_INVALIDARG);
    }

    zend_object *zobj = Z_OBJ_P(getThis());
    certs_obj *obj =
        (certs_obj *)((char *)zobj - XtOffsetOf(certs_obj, zobj));

    object_init_ex(return_value, certs_ce);
    zobj = Z_OBJ_P(return_value);
    certs_obj *cobj =
        (certs_obj *)((char *)zobj - XtOffsetOf(certs_obj, zobj));

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->Find(
        Type, &findCriteria, bValidOnly, cobj->m_pCppCadesImpl));
}

PHP_METHOD(CPCertificates, Item) {
    unsigned long lIdx;
    unsigned int Idx;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &lIdx) == FAILURE)
        RETURN_WITH_EXCEPTION(E_INVALIDARG);

    Idx = (unsigned int)lIdx;

    zend_object *zobj = Z_OBJ_P(getThis());
    certs_obj *obj =
        (certs_obj *)((char *)zobj - XtOffsetOf(certs_obj, zobj));

    NS_SHARED_PTR::shared_ptr<CPPCadesCPCertificateObject> context;
    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->Item(Idx, context));

    object_init_ex(return_value, cert_ce);
    zobj = Z_OBJ_P(return_value);
    certificate_obj *cobj =
        (certificate_obj *)((char *)zobj - XtOffsetOf(certificate_obj, zobj));
    cobj->m_pCppCadesImpl = context;
}

PHP_METHOD(CPCertificates, Count) {
    unsigned int count;

    zend_object *zobj = Z_OBJ_P(getThis());
    certs_obj *obj =
        (certs_obj *)((char *)zobj - XtOffsetOf(certs_obj, zobj));

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->Count(&count));

    RETURN_LONG(count);
}

zend_object_handlers certs_obj_handlers;
zend_class_entry *certs_ce;

static void certs_free(zend_object *object ) {
    certs_obj *obj = (certs_obj *)((char *)object - XtOffsetOf(certs_obj, zobj));
    obj->m_pCppCadesImpl.reset();

    zend_object_std_dtor(object);
}

static zend_object* certs_create_handler(zend_class_entry *ce ) {
    certs_obj *obj = (certs_obj *)emalloc(sizeof(certs_obj) + zend_object_properties_size(ce));
    memset(obj, 0, sizeof(certs_obj) + zend_object_properties_size(ce));
    
    zend_object_std_init(&obj->zobj, ce);
    object_properties_init(&obj->zobj, ce);
    obj->zobj.handlers = &certs_obj_handlers;

    return &obj->zobj;
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpcertificates_construct, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpcertificates_find, 0, 0, 3)
 ZEND_ARG_INFO(0, findtype)
 ZEND_ARG_INFO(0, criteria)
 ZEND_ARG_INFO(0, validonly)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpcertificates_item, 0, 0, 1)
 ZEND_ARG_INFO(0, index)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpcertificates_count, 0, 0, 0)
ZEND_END_ARG_INFO()

//связывание методов класса в function entry
zend_function_entry certs_methods[] = {
    PHP_ME(CPCertificates, __construct, arginfo_cpcertificates_construct, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
    PHP_ME(CPCertificates, Find, arginfo_cpcertificates_find, ZEND_ACC_PUBLIC)
    PHP_ME(CPCertificates, Item, arginfo_cpcertificates_item, ZEND_ACC_PUBLIC)
    PHP_ME(CPCertificates, Count, arginfo_cpcertificates_count, ZEND_ACC_PUBLIC)
    {NULL, NULL, NULL}};

void certs_init(void) {
    zend_class_entry ce;
    INIT_CLASS_ENTRY(ce, "CPCertificates", certs_methods);
    certs_ce = zend_register_internal_class(&ce );
    certs_ce->create_object = certs_create_handler;
    memcpy(&certs_obj_handlers, zend_get_std_object_handlers(),
           sizeof(zend_object_handlers));
    certs_obj_handlers.clone_obj = NULL;
    certs_obj_handlers.free_obj = certs_free;
    certs_obj_handlers.offset = XtOffsetOf(certs_obj, zobj);
}
