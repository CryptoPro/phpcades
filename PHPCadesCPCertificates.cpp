#include "stdafx.h"
#include "CPPCadesCPCertificates.h"
#include "PHPCadesCPCertificates.h"
#include "PHPCadesCPCertificate.h"
using namespace CryptoPro::PKI::CAdES;

PHP_METHOD(CPCertificates, __construct) {
    certs_obj *obj =
        (certs_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);
    obj->m_pCppCadesImpl = boost::shared_ptr<CPPCadesCPCertificatesObject>(
        new CPPCadesCPCertificatesObject());
}

PHP_METHOD(CPCertificates, Find) {
    FindCriteria findCriteria;
    long lType;
    CAPICOM_CERTIFICATE_FIND_TYPE Type;
    zval *query;
    long lValidOnly;
    BOOL bValidOnly;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "lzl", &lType, &query,
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

        findCriteria.str = CAtlString(query->value.str.val);
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
            findCriteria.str = CAtlString(query->value.str.val);
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

    certs_obj *obj =
        (certs_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);

    object_init_ex(return_value, certs_ce);
    certs_obj *cobj =
        (certs_obj *)zend_object_store_get_object(return_value TSRMLS_CC);

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->Find(
        Type, &findCriteria, bValidOnly, cobj->m_pCppCadesImpl));
}

PHP_METHOD(CPCertificates, Item) {
    unsigned long lIdx;
    unsigned int Idx;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &lIdx) == FAILURE)
        RETURN_WITH_EXCEPTION(E_INVALIDARG);

    Idx = (unsigned int)lIdx;

    certs_obj *obj =
        (certs_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);

    boost::shared_ptr<CPPCadesCPCertificateObject> context;
    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->Item(Idx, context));

    object_init_ex(return_value, cert_ce);
    cert_obj *cobj =
        (cert_obj *)zend_object_store_get_object(return_value TSRMLS_CC);
    cobj->m_pCppCadesImpl = context;
}

PHP_METHOD(CPCertificates, Count) {
    unsigned int count;

    certs_obj *obj =
        (certs_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->Count(&count));

    RETURN_LONG(count)
}

zend_object_handlers certs_obj_handlers;
zend_class_entry *certs_ce;

void certs_free_storage(void *object TSRMLS_DC) {
    certs_obj *obj = (certs_obj *)object;
    obj->m_pCppCadesImpl.reset();

    zend_hash_destroy(obj->zo.properties);
    FREE_HASHTABLE(obj->zo.properties);

    efree(obj);
}

zend_object_value certs_create_handler(zend_class_entry *type TSRMLS_DC) {
    zend_object_value retval;

    certs_obj *obj = (certs_obj *)emalloc(sizeof(certs_obj));
    memset(obj, 0, sizeof(certs_obj));
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
        zend_objects_store_put(obj, NULL, certs_free_storage, NULL TSRMLS_CC);
    retval.handlers = &certs_obj_handlers;

    return retval;
}

//связывание методов класса в function entry
zend_function_entry certs_methods[] = {
    PHP_ME(CPCertificates, __construct, NULL, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
    PHP_ME(CPCertificates, Find, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(CPCertificates, Item, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(CPCertificates, Count, NULL, ZEND_ACC_PUBLIC){NULL, NULL, NULL}};

void certs_init(TSRMLS_D) {
    zend_class_entry ce;
    INIT_CLASS_ENTRY(ce, "CPCertificates", certs_methods);
    certs_ce = zend_register_internal_class(&ce TSRMLS_CC);
    certs_ce->create_object = certs_create_handler;
    memcpy(&certs_obj_handlers, zend_get_std_object_handlers(),
           sizeof(zend_object_handlers));
    certs_obj_handlers.clone_obj = NULL;
}
