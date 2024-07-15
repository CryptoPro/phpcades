#include "stdafx.h"
#include "PHPCadesCPSigner.h"
#include "PHPCadesCPCertificate.h"
#include "PHPCadesCPAttribute.h"
#include "PHPCadesCPAttributes.h"
using namespace CryptoPro::PKI::CAdES;

//Методы
PHP_METHOD(CPSigner, __construct) {
    sig_obj *obj = (sig_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);
    boost::shared_ptr<CPPCadesCPSignerObject> ptr(new CPPCadesCPSignerObject());
    obj->m_pCppCadesImpl = ptr;
}

PHP_METHOD(CPSigner, get_Certificate) {
    boost::shared_ptr<CPPCadesCPCertificateObject> ctxt;
    sig_obj *obj = (sig_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_Certificate(ctxt));

    object_init_ex(return_value, cert_ce);
    cert_obj *cobj =
        (cert_obj *)zend_object_store_get_object(return_value TSRMLS_CC);
    cobj->m_pCppCadesImpl = ctxt;
}

PHP_METHOD(CPSigner, set_Certificate) {
    zval *cert;
    CCertContext ctxt;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "O", &cert, cert_ce) ==
        FAILURE)
        RETURN_WITH_EXCEPTION(E_INVALIDARG);

    sig_obj *obj = (sig_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);
    cert_obj *cobj = (cert_obj *)zend_object_store_get_object(cert TSRMLS_CC);

    HR_ERRORCHECK_RETURN(cobj->m_pCppCadesImpl->get_CertContext(ctxt));
    boost::shared_ptr<CPPCadesCPCertificateObject> pCert(
        new CPPCadesCPCertificateObject());
    pCert->put_CertContext(ctxt);
    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->put_Certificate(pCert));
}

PHP_METHOD(CPSigner, get_Options) {
    CAPICOM_CERTIFICATE_INCLUDE_OPTION opt;

    sig_obj *obj = (sig_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);
    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_Options(&opt));

    RETURN_LONG(opt)
}

PHP_METHOD(CPSigner, set_Options) {
    long lOpt;
    CAPICOM_CERTIFICATE_INCLUDE_OPTION Opt;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &lOpt) == FAILURE)
        RETURN_WITH_EXCEPTION(E_INVALIDARG);

    Opt = (CAPICOM_CERTIFICATE_INCLUDE_OPTION)lOpt;

    sig_obj *obj = (sig_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);
    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->put_Options(Opt));
}

PHP_METHOD(CPSigner, get_AuthenticatedAttributes) {
    sig_obj *obj = (sig_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);

    object_init_ex(return_value, attr_col_ce);
    attr_col *aobj =
        (attr_col *)zend_object_store_get_object(return_value TSRMLS_CC);
    aobj->type = attr_ce;

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_AuthenticatedAttributes(
        aobj->m_pCppCadesImpl));
}

PHP_METHOD(CPSigner, get_UnauthenticatedAttributes) {
    sig_obj *obj = (sig_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);

    object_init_ex(return_value, attr_col_ce);
    attr_col *aobj =
        (attr_col *)zend_object_store_get_object(return_value TSRMLS_CC);
    aobj->type = attr_ce;

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_UnauthenticatedAttributes(
        aobj->m_pCppCadesImpl));
}

PHP_METHOD(CPSigner, get_TSAAddress) {
    CAtlString adrs;

    sig_obj *obj = (sig_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_TSAAddress(adrs));

    RETURN_ATL_STRING(adrs)
}

PHP_METHOD(CPSigner, set_TSAAddress) {
    char *str;
    int len;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &str, &len) ==
        FAILURE)
        RETURN_WITH_EXCEPTION(E_INVALIDARG);

    sig_obj *obj = (sig_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->put_TSAAddress(CAtlString(str)));
}

PHP_METHOD(CPSigner, get_CRLs) {
    unsigned int count;
    unsigned int len;
    char *str = NULL;
    boost::shared_ptr<CryptoPro::CBlob> pBlob;
    boost::shared_ptr<CPPCadesCPBlobsObject> ptr;

    sig_obj *obj = (sig_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);
    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_CRLs(ptr));

    HR_ERRORCHECK_RETURN(ptr->get_Count(&count));

    array_init(return_value);
    for (unsigned int i = 1; i <= count; i++) {
        ptr->get_Item(i, pBlob);
        len = pBlob->cbData();
        str = (char *)ecalloc(len, sizeof(char));
        memcpy(str, pBlob->pbData(), len);
        add_next_index_stringl(return_value, str, len, 0);
        str = NULL;
    }
}

PHP_METHOD(CPSigner, get_OCSPResponses) {
    unsigned int count;
    unsigned int len;
    char *str = NULL;
    boost::shared_ptr<CryptoPro::CBlob> pBlob;
    boost::shared_ptr<CPPCadesCPBlobsObject> ptr;

    sig_obj *obj = (sig_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);
    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_OCSPResponses(ptr));

    HR_ERRORCHECK_RETURN(ptr->get_Count(&count));

    array_init(return_value);
    for (unsigned int i = 1; i <= count; i++) {
        ptr->get_Item(i, pBlob);
        len = pBlob->cbData();
        str = (char *)ecalloc(len, sizeof(char));
        memcpy(str, pBlob->pbData(), len);
        add_next_index_stringl(return_value, str, len, 0);
        str = NULL;
    }
}

PHP_METHOD(CPSigner, get_SigningTime) {
    CryptoPro::CDateTime time;
    CryptoPro::CStringProxy strpr;

    sig_obj *obj = (sig_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_SigningTime(time));

    strpr = time.tostring();
    RETURN_PROXY_STRING(strpr)
}

PHP_METHOD(CPSigner, get_SignatureTimeStampTime) {
    CryptoPro::CDateTime time;
    CryptoPro::CStringProxy strpr;

    sig_obj *obj = (sig_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);

    HR_ERRORCHECK_RETURN(
        obj->m_pCppCadesImpl->get_SignatureTimeStampTime(time));

    strpr = time.tostring();
    RETURN_PROXY_STRING(strpr);
}

PHP_METHOD(CPSigner, set_KeyPin) {
    char *str;
    int len;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &str, &len) ==
        FAILURE)
        RETURN_WITH_EXCEPTION(E_INVALIDARG);

    sig_obj *obj = (sig_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);
    CAtlStringA pin(CA2CA(CAtlStringA(str), CP_UTF8));
    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->put_KeyPin(pin));
}

//Вспомогательные функции обертки
zend_object_handlers sig_obj_handlers;
zend_class_entry *sig_ce;

void sig_free_storage(void *object TSRMLS_DC) {
    sig_obj *obj = (sig_obj *)object;
    obj->m_pCppCadesImpl.reset();

    zend_hash_destroy(obj->zo.properties);
    FREE_HASHTABLE(obj->zo.properties);

    efree(obj);
}

zend_object_value sig_create_handler(zend_class_entry *type TSRMLS_DC) {
    zend_object_value retval;

    sig_obj *obj = (sig_obj *)emalloc(sizeof(sig_obj));
    memset(obj, 0, sizeof(sig_obj));
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
        zend_objects_store_put(obj, NULL, sig_free_storage, NULL TSRMLS_CC);
    retval.handlers = &sig_obj_handlers;

    return retval;
}

zend_function_entry sig_methods[] = {
    PHP_ME(CPSigner, __construct, NULL, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
    PHP_ME(CPSigner, get_Certificate, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(CPSigner, set_Certificate, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(CPSigner, get_Options, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(CPSigner, set_Options, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(CPSigner, get_AuthenticatedAttributes, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(CPSigner, get_UnauthenticatedAttributes, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(CPSigner, get_TSAAddress, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(CPSigner, set_TSAAddress, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(CPSigner, get_CRLs, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(CPSigner, get_OCSPResponses, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(CPSigner, get_SigningTime, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(CPSigner, get_SignatureTimeStampTime, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(CPSigner, set_KeyPin, NULL, ZEND_ACC_PUBLIC){NULL, NULL, NULL}};

void sig_init(TSRMLS_D) {
    zend_class_entry ce;
    INIT_CLASS_ENTRY(ce, "CPSigner", sig_methods);
    sig_ce = zend_register_internal_class(&ce TSRMLS_CC);
    sig_ce->create_object = sig_create_handler;
    memcpy(&sig_obj_handlers, zend_get_std_object_handlers(),
           sizeof(zend_object_handlers));
    sig_obj_handlers.clone_obj = NULL;
}
