#include "stdafx.h"
#include "PHPCadesCPCertificateStatus.h"
#include "PHPCadesCPCertificates.h"
#include "PHPCadesCPOID.h"
#include "PHPCadesCPEKU.h"
using namespace CryptoPro::PKI::CAdES;

PHP_METHOD(CPCertificateStatus, __construct) {
    certstat_obj *obj =
        (certstat_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);
    obj->m_pCppCadesImpl = NS_SHARED_PTR::shared_ptr<CPPCadesCPCertificateStatusObject>(
        new CPPCadesCPCertificateStatusObject());
}

PHP_METHOD(CPCertificateStatus, get_Result) {
    BOOL res;
    certstat_obj *obj =
        (certstat_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_Result(&res));

    RETURN_LONG(res)
}

PHP_METHOD(CPCertificateStatus, get_CheckFlag) {
    CAPICOM_CHECK_FLAG flag;
    certstat_obj *obj =
        (certstat_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_CheckFlag(&flag));

    RETURN_LONG(flag)
}

PHP_METHOD(CPCertificateStatus, set_CheckFlag) {
    long lFlag;
    CAPICOM_CHECK_FLAG Flag;
    certstat_obj *obj =
        (certstat_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &lFlag) ==
        FAILURE)
        RETURN_WITH_EXCEPTION(E_INVALIDARG);

    Flag = (CAPICOM_CHECK_FLAG)lFlag;

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->put_CheckFlag(Flag));
}

PHP_METHOD(CPCertificateStatus, EKU) {
    NS_SHARED_PTR::shared_ptr<CPPCadesCPEKUObject> ptr(new CPPCadesCPEKUObject());
    certstat_obj *obj =
        (certstat_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->EKU(ptr));

    object_init_ex(return_value, eku_ce);
    eku_obj *eobj =
        (eku_obj *)zend_object_store_get_object(return_value TSRMLS_CC);

    eobj->m_pCppCadesImpl = ptr;
}

PHP_METHOD(CPCertificateStatus, get_VerificationTime) {
    CryptoPro::CDateTime time;
    CryptoPro::CStringProxy strpr;

    certstat_obj *obj =
        (certstat_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_VerificationTime(time));

    strpr = time.tostring();
    RETURN_PROXY_STRING(strpr)
}

PHP_METHOD(CPCertificateStatus, set_VerificationTime) {
    CryptoPro::CDateTime time;
    char *str;
    int len;

    certstat_obj *obj =
        (certstat_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &str, &len) ==
        FAILURE)
        RETURN_WITH_EXCEPTION(E_INVALIDARG);

    try {
        time = CryptoPro::CDateTime(str);
        HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->put_VerificationTime(time));
    } catch (...) {
        RETURN_WITH_EXCEPTION(E_INVALIDARG);
    }
}

PHP_METHOD(CPCertificateStatus, set_UrlRetrievalTimeout) {
    long urt;

    certstat_obj *obj =
        (certstat_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &urt) == FAILURE)
        RETURN_WITH_EXCEPTION(E_INVALIDARG);

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->put_UrlRetrievalTimeout(urt));
}

PHP_METHOD(CPCertificateStatus, get_UrlRetrievalTimeout) {
    long urt;

    certstat_obj *obj =
        (certstat_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_UrlRetrievalTimeout(&urt));

    RETURN_LONG(urt)
}

PHP_METHOD(CPCertificateStatus, CertificatePolicies) {
    NS_SHARED_PTR::shared_ptr<CPPCadesCPOIDsObject> oids(new CPPCadesCPOIDsObject());
    NS_SHARED_PTR::shared_ptr<CPPCadesCPOIDObject> oid;
    unsigned int count;
    zval *CPoid = new zval();

    certstat_obj *obj =
        (certstat_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->CertificatePolicies(oids));
    HR_ERRORCHECK_RETURN(oids->get_Count(&count));

    array_init(return_value);
    object_init_ex(CPoid, oid_ce);

    for (unsigned int i = 1; i <= count; i++) {
        HR_ERRORCHECK_RETURN(oids->get_Item(i, oid));
        oid_obj *arg = (oid_obj *)zend_object_store_get_object(CPoid TSRMLS_CC);
        arg->m_pCppCadesImpl = oid;
        add_next_index_zval(CPoid, return_value);
    }
}

PHP_METHOD(CPCertificateStatus, ApplicationPolicies) {
    NS_SHARED_PTR::shared_ptr<CPPCadesCPOIDsObject> oids(new CPPCadesCPOIDsObject());
    NS_SHARED_PTR::shared_ptr<CPPCadesCPOIDObject> oid;
    unsigned int count;
    zval *CPoid = new zval();

    certstat_obj *obj =
        (certstat_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->ApplicationPolicies(oids));
    HR_ERRORCHECK_RETURN(oids->get_Count(&count));

    array_init(return_value);
    object_init_ex(CPoid, oid_ce);

    for (unsigned int i = 1; i <= count; i++) {
        HR_ERRORCHECK_RETURN(oids->get_Item(i, oid));
        oid_obj *arg = (oid_obj *)zend_object_store_get_object(CPoid TSRMLS_CC);
        arg->m_pCppCadesImpl = oid;
        add_next_index_zval(CPoid, return_value);
    }
}

PHP_METHOD(CPCertificateStatus, get_ValidationCertificates) {
    NS_SHARED_PTR::shared_ptr<CPPCadesCPCertificatesObject> certs(
        new CPPCadesCPCertificatesObject());

    certstat_obj *obj =
        (certstat_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);

    HR_ERRORCHECK_RETURN(
        obj->m_pCppCadesImpl->get_ValidationCertificates(certs));

    object_init_ex(return_value, certs_ce);
    certs_obj *cobj =
        (certs_obj *)zend_object_store_get_object(return_value TSRMLS_CC);
    cobj->m_pCppCadesImpl = certs;
}

zend_object_handlers certstat_obj_handlers;
zend_class_entry *certstat_ce;

void certstat_free_storage(void *object TSRMLS_DC) {
    certstat_obj *obj = (certstat_obj *)object;
    obj->m_pCppCadesImpl.reset();

    zend_hash_destroy(obj->zo.properties);
    FREE_HASHTABLE(obj->zo.properties);

    efree(obj);
}

zend_object_value certstat_create_handler(zend_class_entry *type TSRMLS_DC) {
    zend_object_value retval;

    certstat_obj *obj = (certstat_obj *)emalloc(sizeof(certstat_obj));
    memset(obj, 0, sizeof(certstat_obj));
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

    retval.handle = zend_objects_store_put(obj, NULL, certstat_free_storage,
                                           NULL TSRMLS_CC);
    retval.handlers = &certstat_obj_handlers;

    return retval;
}

//связывание методов класса в function entry
zend_function_entry certstat_methods[] = {
    PHP_ME(CPCertificateStatus, __construct, NULL,
           ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
    PHP_ME(CPCertificateStatus, get_Result, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(CPCertificateStatus, get_CheckFlag, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(CPCertificateStatus, set_CheckFlag, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(CPCertificateStatus, EKU, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(CPCertificateStatus, get_VerificationTime, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(CPCertificateStatus, set_VerificationTime, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(CPCertificateStatus, get_UrlRetrievalTimeout, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(CPCertificateStatus, set_UrlRetrievalTimeout, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(CPCertificateStatus, CertificatePolicies, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(CPCertificateStatus, ApplicationPolicies, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(CPCertificateStatus, get_ValidationCertificates, NULL,
           ZEND_ACC_PUBLIC){NULL, NULL, NULL}};

void certstat_init(TSRMLS_D) {
    zend_class_entry ce;
    INIT_CLASS_ENTRY(ce, "CPCertificateStatus", certstat_methods);
    certstat_ce = zend_register_internal_class(&ce TSRMLS_CC);
    certstat_ce->create_object = certstat_create_handler;
    memcpy(&certstat_obj_handlers, zend_get_std_object_handlers(),
           sizeof(zend_object_handlers));
    certstat_obj_handlers.clone_obj = NULL;
}
