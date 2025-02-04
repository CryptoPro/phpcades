#include "stdafx.h"
#include "PHPCadesCPCertificate.h"
#include "PHPCadesCPCertificates.h"
#include "PHPCadesCPKeyUsage.h"
#include "PHPCadesCPExtendedKeyUsage.h"
#include "PHPCadesCPPrivateKey.h"
#include "PHPCadesCPPublicKey.h"
#include "PHPCadesCPBasicConstraints.h"
#include "PHPCadesCPCertificateStatus.h"
using namespace CryptoPro::PKI::CAdES;

//Методы
PHP_METHOD(CPCertificate, __construct) {
    cert_obj *obj =
        (cert_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);
    NS_SHARED_PTR::shared_ptr<CPPCadesCPCertificateObject> cert(
        new CPPCadesCPCertificateObject());
    obj->m_pCppCadesImpl = cert;
}

PHP_METHOD(CPCertificate, GetInfo) {
    CAtlString infoW;
    long lType;
    CAPICOM_CERT_INFO_TYPE Type;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &lType) ==
        FAILURE)
        RETURN_WITH_EXCEPTION(E_INVALIDARG);

    Type = (CAPICOM_CERT_INFO_TYPE)lType;

    cert_obj *obj =
        (cert_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);
    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->GetInfo(Type, infoW));

    RETURN_ATL_STRING(infoW);
}

PHP_METHOD(CPCertificate, FindPrivateKey) {
    int len;
    char *str;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "|s", &str, &len) ==
        FAILURE) {
        RETURN_WITH_EXCEPTION(E_INVALIDARG);
    }

    cert_obj *obj =
        (cert_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->FindPrivateKey(CAtlString(str, len)));
}

PHP_METHOD(CPCertificate, HasPrivateKey) {
    BOOL has;

    cert_obj *obj =
        (cert_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->HasPrivateKey(&has));
    if (has)
        RETURN_TRUE
    else
        RETURN_FALSE
}

PHP_METHOD(CPCertificate, IsValid) {
    NS_SHARED_PTR::shared_ptr<CPPCadesCPCertificateStatusObject> stat(
        new CPPCadesCPCertificateStatusObject());

    cert_obj *obj =
        (cert_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->IsValid(stat));

    object_init_ex(return_value, certstat_ce);
    certstat_obj *cstat =
        (certstat_obj *)zend_object_store_get_object(return_value TSRMLS_CC);
    cstat->m_pCppCadesImpl = stat;
}

PHP_METHOD(CPCertificate, KeyUsage) {
    cert_obj *obj =
        (cert_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);

    object_init_ex(return_value, ku_ce);
    ku_obj *kobj =
        (ku_obj *)zend_object_store_get_object(return_value TSRMLS_CC);

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->KeyUsage(kobj->m_pCppCadesImpl));
}

PHP_METHOD(CPCertificate, ExtendedKeyUsage) {
    cert_obj *obj =
        (cert_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);

    object_init_ex(return_value, exku_ce);
    exku_obj *exkobj =
        (exku_obj *)zend_object_store_get_object(return_value TSRMLS_CC);

    HR_ERRORCHECK_RETURN(
        obj->m_pCppCadesImpl->ExtendedKeyUsage(exkobj->m_pCppCadesImpl));
}

PHP_METHOD(CPCertificate, Export) {
    CryptoPro::CBlob value;
    int len;
    char *str;
    long lType;
    CAPICOM_ENCODING_TYPE Type;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &lType) ==
        FAILURE) {
        RETURN_WITH_EXCEPTION(E_INVALIDARG);
    }

    Type = (CAPICOM_ENCODING_TYPE)lType;

    cert_obj *obj =
        (cert_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->Export(Type, value));

    len = value.cbData();
    str = (char *)ecalloc(len, sizeof(char));
    memcpy(str, value.pbData(), len);

    RETURN_STRINGL(str, len - 2 , 0); //удаляем перевод строки иначе php будет мусор оставлять в переменных
}

PHP_METHOD(CPCertificate, Import) {
    CryptoPro::CBlob value;
    int len;
    char *str;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &str, &len) ==
        FAILURE) {
        RETURN_WITH_EXCEPTION(E_INVALIDARG);
    }

    value.assign((unsigned char *)str, len);

    cert_obj *obj =
        (cert_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->Import(value));
}

PHP_METHOD(CPCertificate, get_SerialNumber) {
    CAtlString numberW;

    cert_obj *obj =
        (cert_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_SerialNumber(numberW));
    RETURN_ATL_STRING(numberW)
}

PHP_METHOD(CPCertificate, get_Thumbprint) {
    CAtlString thumbprW;

    cert_obj *obj =
        (cert_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_Thumbprint(thumbprW));
    RETURN_ATL_STRING(thumbprW)
}

PHP_METHOD(CPCertificate, get_SubjectName) {
    CAtlString nameW;

    cert_obj *obj =
        (cert_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_SubjectName(nameW));
    RETURN_ATL_STRING(nameW)
}

PHP_METHOD(CPCertificate, get_IssuerName) {
    CAtlString nameW;

    cert_obj *obj =
        (cert_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_IssuerName(nameW));
    RETURN_ATL_STRING(nameW)
}

PHP_METHOD(CPCertificate, get_Version) {
    DWORD version;

    cert_obj *obj =
        (cert_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_Version(&version));
    RETURN_LONG(version)
}

PHP_METHOD(CPCertificate, get_ValidToDate) {
    CryptoPro::CDateTime date;
    CryptoPro::CStringProxy strpr;

    cert_obj *obj =
        (cert_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_ValidToDate(date));
    strpr = date.tostring();
    RETURN_PROXY_STRING(strpr)
}

PHP_METHOD(CPCertificate, get_ValidFromDate) {
    CryptoPro::CDateTime date;
    CryptoPro::CStringProxy strpr;

    cert_obj *obj =
        (cert_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_ValidFromDate(date));
    strpr = date.tostring();
    RETURN_PROXY_STRING(strpr)
}

PHP_METHOD(CPCertificate, PrivateKey) {
    cert_obj *obj =
        (cert_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);

    object_init_ex(return_value, private_key_ce);
    private_key_obj *kobj =
        (private_key_obj *)zend_object_store_get_object(return_value TSRMLS_CC);

    HR_ERRORCHECK_RETURN(
        obj->m_pCppCadesImpl->PrivateKey(kobj->m_pCppCadesImpl));
}

PHP_METHOD(CPCertificate, PublicKey) {
    cert_obj *obj =
        (cert_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);

    object_init_ex(return_value, public_key_ce);
    public_key_obj *kobj =
        (public_key_obj *)zend_object_store_get_object(return_value TSRMLS_CC);

    HR_ERRORCHECK_RETURN(
        obj->m_pCppCadesImpl->PublicKey(kobj->m_pCppCadesImpl));
}

PHP_METHOD(CPCertificate, BasicConstraints) {
    cert_obj *obj =
        (cert_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);

    object_init_ex(return_value, basic_constr_ce);
    basic_constr_obj *bcobj = (basic_constr_obj *)zend_object_store_get_object(
        return_value TSRMLS_CC);

    HR_ERRORCHECK_RETURN(
        obj->m_pCppCadesImpl->BasicConstraints(bcobj->m_pCppCadesImpl));
}

//Вспомогательные функции обертки
zend_object_handlers cert_obj_handlers;
zend_class_entry *cert_ce;

void cert_free_storage(void *object TSRMLS_DC) {
    cert_obj *obj = (cert_obj *)object;
    obj->m_pCppCadesImpl.reset();

    zend_hash_destroy(obj->zo.properties);
    FREE_HASHTABLE(obj->zo.properties);

    efree(obj);
}

zend_object_value cert_create_handler(zend_class_entry *type TSRMLS_DC) {
    zend_object_value retval;

    cert_obj *obj = (cert_obj *)emalloc(sizeof(cert_obj));
    memset(obj, 0, sizeof(cert_obj));
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
        zend_objects_store_put(obj, NULL, cert_free_storage, NULL TSRMLS_CC);
    retval.handlers = &cert_obj_handlers;

    return retval;
}

//связывание методов класса в function entry
zend_function_entry cert_methods[] = {
    PHP_ME(CPCertificate, __construct, NULL, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
    PHP_ME(CPCertificate, GetInfo, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(CPCertificate, FindPrivateKey, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(CPCertificate, HasPrivateKey, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(CPCertificate, IsValid, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(CPCertificate, ExtendedKeyUsage, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(CPCertificate, KeyUsage, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(CPCertificate, Export, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(CPCertificate, Import, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(CPCertificate, get_SerialNumber, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(CPCertificate, get_Thumbprint, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(CPCertificate, get_SubjectName, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(CPCertificate, get_IssuerName, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(CPCertificate, get_Version, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(CPCertificate, get_ValidToDate, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(CPCertificate, get_ValidFromDate, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(CPCertificate, BasicConstraints, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(CPCertificate, PublicKey, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(CPCertificate, PrivateKey, NULL, ZEND_ACC_PUBLIC){NULL, NULL, NULL}};

void cert_init(TSRMLS_D) {
    zend_class_entry ce;
    INIT_CLASS_ENTRY(ce, "CPcertificate", cert_methods);
    cert_ce = zend_register_internal_class(&ce TSRMLS_CC);
    cert_ce->create_object = cert_create_handler;
    memcpy(&cert_obj_handlers, zend_get_std_object_handlers(),
           sizeof(zend_object_handlers));
    cert_obj_handlers.clone_obj = NULL;
}
