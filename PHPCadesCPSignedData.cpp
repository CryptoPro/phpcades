#include "stdafx.h"
#include "PHPCadesCPSignedData.h"
#include "PHPCadesCPSigners.h"
#include "PHPCadesCPSigner.h"
#include "PHPCadesCPHashedData.h"
#include "PHPCadesCPCertificates.h"
using namespace CryptoPro::PKI::CAdES;

PHP_METHOD(CPSignedData, __construct) {
    sig_dat_obj *obj =
        (sig_dat_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);
    obj->m_pCppCadesImpl = new CPPCadesSignedDataObject();
}

PHP_METHOD(CPSignedData, SignCades) {
    zval *zSigner;
    long lCadesType;
    CADESCOM_CADES_TYPE CadesType;
    long lDetached;
    BOOL Detached;
    long lEncodingType;
    CAPICOM_ENCODING_TYPE EncodingType;
    CryptoPro::CBlob bVal;

    char *sVal;
    int lVal;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "Olll", &zSigner,
                              sig_ce, &lCadesType, &lDetached,
                              &lEncodingType) == FAILURE)
        RETURN_WITH_EXCEPTION(E_INVALIDARG);

    CadesType = (CADESCOM_CADES_TYPE)lCadesType;
    Detached = (BOOL)lDetached;
    EncodingType = (CAPICOM_ENCODING_TYPE)lEncodingType;

    sig_obj *pSigner =
        (sig_obj *)zend_object_store_get_object(zSigner TSRMLS_CC);

    sig_dat_obj *obj =
        (sig_dat_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);
    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->SignCades(
        pSigner->m_pCppCadesImpl, CadesType, Detached, EncodingType, &bVal));

    lVal = bVal.cbData();
    sVal = (char *)ecalloc(lVal, sizeof(char));
    memcpy(sVal, bVal.pbData(), lVal);

    RETURN_STRINGL(sVal, lVal, 0)
}

PHP_METHOD(CPSignedData, SignHash) {
    zval *zSigner;
    zval *zHashedData;
    long lCadesType;
    CADESCOM_CADES_TYPE CadesType;
    long lEncodingType;
    CAPICOM_ENCODING_TYPE EncodingType;
    CryptoPro::CBlob bVal;

    char *sVal;
    int lVal;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "OOll", &zHashedData,
                              hash_dat_class_entry, &zSigner, sig_ce,
                              &lCadesType, &lEncodingType) == FAILURE)
        RETURN_WITH_EXCEPTION(E_INVALIDARG);

    CadesType = (CADESCOM_CADES_TYPE)lCadesType;
    EncodingType = (CAPICOM_ENCODING_TYPE)lEncodingType;

    sig_obj *pSigner =
        (sig_obj *)zend_object_store_get_object(zSigner TSRMLS_CC);
    hash_dat_obj *pHashedData =
        (hash_dat_obj *)zend_object_store_get_object(zHashedData TSRMLS_CC);

    sig_dat_obj *obj =
        (sig_dat_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);
    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->SignHash(
        pSigner->m_pCppCadesImpl, pHashedData->m_pCppCadesImpl, CadesType,
        EncodingType, &bVal));

    lVal = bVal.cbData();
    sVal = (char *)ecalloc(lVal, sizeof(char));
    memcpy(sVal, bVal.pbData(), lVal);

    RETURN_STRINGL(sVal, lVal, 0)
}

PHP_METHOD(CPSignedData, CoSignHash) {
    zval *zSigner;
    zval *zHashedData;
    long lCadesType;
    CADESCOM_CADES_TYPE CadesType;
    long lEncodingType;
    CAPICOM_ENCODING_TYPE EncodingType;
    CryptoPro::CBlob bVal;

    char *sVal;
    int lVal;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "OOll", &zSigner,
                              sig_ce, &zHashedData, hash_dat_class_entry,
                              &lCadesType, &lEncodingType) == FAILURE)
        RETURN_WITH_EXCEPTION(E_INVALIDARG);

    CadesType = (CADESCOM_CADES_TYPE)lCadesType;
    EncodingType = (CAPICOM_ENCODING_TYPE)lEncodingType;

    sig_obj *pSigner =
        (sig_obj *)zend_object_store_get_object(zSigner TSRMLS_CC);
    hash_dat_obj *pHashedData =
        (hash_dat_obj *)zend_object_store_get_object(zHashedData TSRMLS_CC);

    sig_dat_obj *obj =
        (sig_dat_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);
    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->CoSignHash(
        pSigner->m_pCppCadesImpl, pHashedData->m_pCppCadesImpl, CadesType,
        EncodingType, &bVal));

    lVal = bVal.cbData();
    sVal = (char *)ecalloc(lVal, sizeof(char));
    memcpy(sVal, bVal.pbData(), lVal);

    RETURN_STRINGL(sVal, lVal, 0)
}

PHP_METHOD(CPSignedData, Sign) {
    zval *zSigner;
    long lDetached;
    BOOL Detached;
    long lEncodingType;
    CAPICOM_ENCODING_TYPE EncodingType;
    CryptoPro::CBlob bVal;

    char *sVal;
    int lVal;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "Oll", &zSigner,
                              sig_ce, &lDetached, &lEncodingType) == FAILURE)
        RETURN_WITH_EXCEPTION(E_INVALIDARG);

    Detached = (BOOL)lDetached;
    EncodingType = (CAPICOM_ENCODING_TYPE)lEncodingType;

    sig_obj *pSigner =
        (sig_obj *)zend_object_store_get_object(zSigner TSRMLS_CC);

    sig_dat_obj *obj =
        (sig_dat_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);
    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->Sign(
        pSigner->m_pCppCadesImpl, Detached, EncodingType, &bVal));

    lVal = bVal.cbData();
    sVal = (char *)ecalloc(lVal, sizeof(char));
    memcpy(sVal, bVal.pbData(), lVal);

    RETURN_STRINGL(sVal, lVal, 0)
}

PHP_METHOD(CPSignedData, CoSign) {
    zval *zSigner;
    long lEncodingType;
    CAPICOM_ENCODING_TYPE EncodingType;
    CryptoPro::CBlob bVal;

    char *sVal;
    int lVal;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "Ol", &zSigner, sig_ce,
                              &lEncodingType) == FAILURE)
        RETURN_WITH_EXCEPTION(E_INVALIDARG);

    EncodingType = (CAPICOM_ENCODING_TYPE)lEncodingType;

    sig_obj *pSigner =
        (sig_obj *)zend_object_store_get_object(zSigner TSRMLS_CC);

    sig_dat_obj *obj =
        (sig_dat_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);
    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->CoSign(pSigner->m_pCppCadesImpl,
                                                      EncodingType, &bVal));

    lVal = bVal.cbData();
    sVal = (char *)ecalloc(lVal, sizeof(char));
    memcpy(sVal, bVal.pbData(), lVal);

    RETURN_STRINGL(sVal, lVal, 0)
}

PHP_METHOD(CPSignedData, CoSignCades) {
    zval *zSigner;
    long lCadesType;
    CADESCOM_CADES_TYPE CadesType;
    long lEncodingType;
    CAPICOM_ENCODING_TYPE EncodingType;
    CryptoPro::CBlob bVal;

    char *sVal;
    int lVal;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "Oll", &zSigner,
                              sig_ce, &lCadesType, &lEncodingType) == FAILURE)
        RETURN_WITH_EXCEPTION(E_INVALIDARG);

    CadesType = (CADESCOM_CADES_TYPE)lCadesType;
    EncodingType = (CAPICOM_ENCODING_TYPE)lEncodingType;

    sig_obj *pSigner =
        (sig_obj *)zend_object_store_get_object(zSigner TSRMLS_CC);

    sig_dat_obj *obj =
        (sig_dat_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);
    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->CoSignCades(
        pSigner->m_pCppCadesImpl, CadesType, EncodingType, &bVal));

    lVal = bVal.cbData();
    sVal = (char *)ecalloc(lVal, sizeof(char));
    memcpy(sVal, bVal.pbData(), lVal);

    RETURN_STRINGL(sVal, lVal, 0)
}

PHP_METHOD(CPSignedData, EnhanceCades) {
    long lCadesType;
    CADESCOM_CADES_TYPE CadesType;
    char *TSAAddress;
    int AddressLen;
    long lEncodingType;
    CAPICOM_ENCODING_TYPE EncodingType;
    CryptoPro::CBlob bVal;

    char *sVal;
    int lVal;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "lsl", &lCadesType,
                              &TSAAddress, &AddressLen,
                              &lEncodingType) == FAILURE)
        RETURN_WITH_EXCEPTION(E_INVALIDARG);

    CadesType = (CADESCOM_CADES_TYPE)lCadesType;
    EncodingType = (CAPICOM_ENCODING_TYPE)lEncodingType;

    sig_dat_obj *obj =
        (sig_dat_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);
    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->EnhanceCades(
        CadesType, CAtlString(TSAAddress), EncodingType, &bVal));

    lVal = bVal.cbData();
    sVal = (char *)ecalloc(lVal, sizeof(char));
    memcpy(sVal, bVal.pbData(), lVal);

    RETURN_STRINGL(sVal, lVal, 0)
}

PHP_METHOD(CPSignedData, Verify) {
    CryptoPro::CBlob bSignedMessage;
    unsigned char *sSignedMessage;
    int lSignedMessage;
    long lDetached;
    BOOL Detached;
    long lVerifyFlag;
    CAPICOM_SIGNED_DATA_VERIFY_FLAG VerifyFlag;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "sll", &sSignedMessage,
                              &lSignedMessage, &lDetached,
                              &lVerifyFlag) == FAILURE)
        RETURN_WITH_EXCEPTION(E_INVALIDARG);

    Detached = (BOOL)lDetached;
    VerifyFlag = (CAPICOM_SIGNED_DATA_VERIFY_FLAG)lVerifyFlag;

    bSignedMessage.assign(sSignedMessage, lSignedMessage);

    sig_dat_obj *obj =
        (sig_dat_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);
    HR_ERRORCHECK_RETURN(
        obj->m_pCppCadesImpl->Verify(bSignedMessage, Detached, VerifyFlag));
}

PHP_METHOD(CPSignedData, VerifyCades) {
    CryptoPro::CBlob bSignedMessage;
    unsigned char *sSignedMessage;
    int lSignedMessage;
    long lCadesType = CADESCOM_CADES_DEFAULT;
    CADESCOM_CADES_TYPE CadesType;
    long lDetached = 0;
    BOOL Detached;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s|ll",
                              &sSignedMessage, &lSignedMessage, &lCadesType,
                              &lDetached) == FAILURE)
        RETURN_WITH_EXCEPTION(E_INVALIDARG);

    CadesType = (CADESCOM_CADES_TYPE)lCadesType;
    Detached = (BOOL)lDetached;

    bSignedMessage.assign(sSignedMessage, lSignedMessage);

    sig_dat_obj *obj =
        (sig_dat_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);
    HR_ERRORCHECK_RETURN(
        obj->m_pCppCadesImpl->VerifyCades(bSignedMessage, CadesType, Detached));
}

PHP_METHOD(CPSignedData, VerifyHash) {
    CryptoPro::CBlob bSignedMessage;
    zval *zHashedData;
    unsigned char *sSignedMessage;
    int lSignedMessage;
    long lCadesType = CADESCOM_CADES_DEFAULT;
    CADESCOM_CADES_TYPE CadesType;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "Os|l", &zHashedData,
                              hash_dat_class_entry, &sSignedMessage,
                              &lSignedMessage, &lCadesType) == FAILURE)
        RETURN_WITH_EXCEPTION(E_INVALIDARG);

    CadesType = (CADESCOM_CADES_TYPE)lCadesType;

    bSignedMessage.assign(sSignedMessage, lSignedMessage);

    sig_dat_obj *obj =
        (sig_dat_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);

    hash_dat_obj *pHashedData =
        (hash_dat_obj *)zend_object_store_get_object(zHashedData TSRMLS_CC);

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->VerifyHash(
        pHashedData->m_pCppCadesImpl, bSignedMessage, CadesType));
}

PHP_METHOD(CPSignedData, set_ContentEncoding) {
    long lType;
    CADESCOM_CONTENT_ENCODING_TYPE Type;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &lType) ==
        FAILURE)
        RETURN_WITH_EXCEPTION(E_INVALIDARG);

    Type = (CADESCOM_CONTENT_ENCODING_TYPE)lType;

    sig_dat_obj *obj =
        (sig_dat_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);
    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->put_ContentEncoding(Type));
}

PHP_METHOD(CPSignedData, get_ContentEncoding) {
    CADESCOM_CONTENT_ENCODING_TYPE type;

    sig_dat_obj *obj =
        (sig_dat_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);
    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_ContentEncoding(&type));

    RETURN_LONG(type)
}

PHP_METHOD(CPSignedData, set_Content) {
    char *sVal;
    int lVal;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &sVal, &lVal) ==
        FAILURE)
        RETURN_WITH_EXCEPTION(E_INVALIDARG);

    sig_dat_obj *obj =
        (sig_dat_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);
    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->put_Content(sVal, lVal));
}

PHP_METHOD(CPSignedData, get_Content) {
    CStringBlob Val;
    char *sVal;
    int lVal;

    sig_dat_obj *obj =
        (sig_dat_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);
    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_Content(Val));

    lVal = Val.GetLength();
    sVal = (char *)ecalloc(lVal, sizeof(char));
    memcpy(sVal, Val, lVal);

    RETURN_STRINGL(sVal, lVal, 0)
}

PHP_METHOD(CPSignedData, get_Signers) {
    object_init_ex(return_value, signers_ce);
    signers_obj *pSigners =
        (signers_obj *)zend_object_store_get_object(return_value TSRMLS_CC);

    sig_dat_obj *obj =
        (sig_dat_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);
    HR_ERRORCHECK_RETURN(
        obj->m_pCppCadesImpl->get_Signers(pSigners->m_pCppCadesImpl));

    return;
}

PHP_METHOD(CPSignedData, get_Certificates) {
    NS_SHARED_PTR::shared_ptr<CPPCadesCPCertificatesObject> pVal;

    sig_dat_obj *obj =
        (sig_dat_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);
    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_Certificates(pVal));

    object_init_ex(return_value, certs_ce);
    certs_obj *pCertificates =
        (certs_obj *)zend_object_store_get_object(return_value TSRMLS_CC);
    pCertificates->m_pCppCadesImpl = pVal;
}

zend_class_entry *sig_dat_class_entry;
zend_object_handlers sig_dat_handlers;

zend_function_entry sig_dat_methods[] = {
    PHP_ME(CPSignedData, __construct, NULL, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
    PHP_ME(CPSignedData, SignCades, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(CPSignedData, SignHash, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(CPSignedData, Sign, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(CPSignedData, CoSign, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(CPSignedData, CoSignCades, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(CPSignedData, CoSignHash, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(CPSignedData, EnhanceCades, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(CPSignedData, VerifyCades, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(CPSignedData, VerifyHash, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(CPSignedData, Verify, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(CPSignedData, set_ContentEncoding, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(CPSignedData, get_ContentEncoding, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(CPSignedData, set_Content, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(CPSignedData, get_Content, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(CPSignedData, get_Signers, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(CPSignedData, get_Certificates, NULL, ZEND_ACC_PUBLIC){NULL, NULL,
                                                                  NULL}};

void sig_dat_free_storage(void *object TSRMLS_DC) {
    sig_dat_obj *obj = (sig_dat_obj *)object;
    delete obj->m_pCppCadesImpl;

    zend_hash_destroy(obj->zo.properties);
    FREE_HASHTABLE(obj->zo.properties);

    efree(obj);
}

zend_object_value sig_dat_create_handler(zend_class_entry *type TSRMLS_DC) {
    zend_object_value retval;

    sig_dat_obj *obj = (sig_dat_obj *)emalloc(sizeof(sig_dat_obj));
    memset(obj, 0, sizeof(sig_dat_obj));
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
        zend_objects_store_put(obj, NULL, sig_dat_free_storage, NULL TSRMLS_CC);
    retval.handlers = &sig_dat_handlers;

    return retval;
}

void sig_dat_init(TSRMLS_D) {
    zend_class_entry ce;
    INIT_CLASS_ENTRY(ce, "CPSignedData", sig_dat_methods);
    sig_dat_class_entry = zend_register_internal_class(&ce TSRMLS_CC);
    sig_dat_class_entry->create_object = sig_dat_create_handler;
    memcpy(&sig_dat_handlers, zend_get_std_object_handlers(),
           sizeof(zend_object_handlers));
    sig_dat_handlers.clone_obj = NULL;
}
