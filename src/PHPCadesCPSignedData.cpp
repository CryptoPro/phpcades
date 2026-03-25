#include "stdafx.h"
#include "PHPCadesCPSignedData.h"
#include "PHPCadesCPSigners.h"
#include "PHPCadesCPSigner.h"
#include "PHPCadesCPHashedData.h"
#include "PHPCadesCPCertificates.h"
using namespace CryptoPro::PKI::CAdES;

PHP_METHOD(CPSignedData, __construct) {
    zend_object *zobj = Z_OBJ_P(getThis());
    signed_data_obj *obj =
        (signed_data_obj *)((char *)zobj - XtOffsetOf(signed_data_obj, zobj));
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

    if (zend_parse_parameters(ZEND_NUM_ARGS() , "Olll", &zSigner,
                              signer_ce, &lCadesType, &lDetached,
                              &lEncodingType) == FAILURE)
        RETURN_WITH_EXCEPTION(E_INVALIDARG);

    CadesType = (CADESCOM_CADES_TYPE)lCadesType;
    Detached = (BOOL)lDetached;
    EncodingType = (CAPICOM_ENCODING_TYPE)lEncodingType;

    zend_object *zobj = Z_OBJ_P(getThis());
    signed_data_obj *obj =
        (signed_data_obj *)((char *)zobj - XtOffsetOf(signed_data_obj, zobj));

    zobj = Z_OBJ_P(zSigner);
    signer_obj *pSigner =
        (signer_obj *)((char *)zobj - XtOffsetOf(signer_obj, zobj));

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->SignCades(
        pSigner->m_pCppCadesImpl, CadesType, Detached, EncodingType, &bVal));

    lVal = bVal.cbData();
    sVal = (char *)ecalloc(lVal, sizeof(char));
    memcpy(sVal, bVal.pbData(), lVal);

    RETURN_STRINGL(sVal, lVal);
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

    if (zend_parse_parameters(ZEND_NUM_ARGS() , "OOll", &zHashedData,
                              hashed_data_ce, &zSigner, signer_ce,
                              &lCadesType, &lEncodingType) == FAILURE)
        RETURN_WITH_EXCEPTION(E_INVALIDARG);

    CadesType = (CADESCOM_CADES_TYPE)lCadesType;
    EncodingType = (CAPICOM_ENCODING_TYPE)lEncodingType;
    
    zend_object *zobj = Z_OBJ_P(getThis());
    signed_data_obj *obj =
        (signed_data_obj *)((char *)zobj - XtOffsetOf(signed_data_obj, zobj));

    zobj = Z_OBJ_P(zSigner);
    signer_obj *pSigner =
        (signer_obj *)((char *)zobj - XtOffsetOf(signer_obj, zobj));

    zobj = Z_OBJ_P(zHashedData);
    hashed_data_obj *pHashedData =
        (hashed_data_obj *)((char *)zobj - XtOffsetOf(hashed_data_obj, zobj));


    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->SignHash(
        pSigner->m_pCppCadesImpl, pHashedData->m_pCppCadesImpl, CadesType,
        EncodingType, &bVal));

    lVal = bVal.cbData();
    sVal = (char *)ecalloc(lVal, sizeof(char));
    memcpy(sVal, bVal.pbData(), lVal);

    RETURN_STRINGL(sVal, lVal);
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

    if (zend_parse_parameters(ZEND_NUM_ARGS() , "OOll", &zSigner,
                              signer_ce, &zHashedData, hashed_data_ce,
                              &lCadesType, &lEncodingType) == FAILURE)
        RETURN_WITH_EXCEPTION(E_INVALIDARG);

    CadesType = (CADESCOM_CADES_TYPE)lCadesType;
    EncodingType = (CAPICOM_ENCODING_TYPE)lEncodingType;

    zend_object *zobj = Z_OBJ_P(getThis());
    signed_data_obj *obj =
        (signed_data_obj *)((char *)zobj - XtOffsetOf(signed_data_obj, zobj));

    zobj = Z_OBJ_P(zSigner);
    signer_obj *pSigner =
        (signer_obj *)((char *)zobj - XtOffsetOf(signer_obj, zobj));

    zobj = Z_OBJ_P(zHashedData);
    hashed_data_obj *pHashedData =
        (hashed_data_obj *)((char *)zobj - XtOffsetOf(hashed_data_obj, zobj));

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->CoSignHash(
        pSigner->m_pCppCadesImpl, pHashedData->m_pCppCadesImpl, CadesType,
        EncodingType, &bVal));

    lVal = bVal.cbData();
    sVal = (char *)ecalloc(lVal, sizeof(char));
    memcpy(sVal, bVal.pbData(), lVal);

    RETURN_STRINGL(sVal, lVal);
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

    if (zend_parse_parameters(ZEND_NUM_ARGS() , "Oll", &zSigner,
                              signer_ce, &lDetached, &lEncodingType) == FAILURE)
        RETURN_WITH_EXCEPTION(E_INVALIDARG);

    Detached = (BOOL)lDetached;
    EncodingType = (CAPICOM_ENCODING_TYPE)lEncodingType;

    zend_object *zobj = Z_OBJ_P(getThis());
    signed_data_obj *obj =
        (signed_data_obj *)((char *)zobj - XtOffsetOf(signed_data_obj, zobj));

    zobj = Z_OBJ_P(zSigner);
    signer_obj *pSigner =
        (signer_obj *)((char *)zobj - XtOffsetOf(signer_obj, zobj));

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->Sign(
        pSigner->m_pCppCadesImpl, Detached, EncodingType, &bVal));

    lVal = bVal.cbData();
    sVal = (char *)ecalloc(lVal, sizeof(char));
    memcpy(sVal, bVal.pbData(), lVal);

    RETURN_STRINGL(sVal, lVal);
}

PHP_METHOD(CPSignedData, CoSign) {
    zval *zSigner;
    long lEncodingType;
    CAPICOM_ENCODING_TYPE EncodingType;
    CryptoPro::CBlob bVal;

    char *sVal;
    int lVal;

    if (zend_parse_parameters(ZEND_NUM_ARGS() , "Ol", &zSigner, signer_ce,
                              &lEncodingType) == FAILURE)
        RETURN_WITH_EXCEPTION(E_INVALIDARG);

    EncodingType = (CAPICOM_ENCODING_TYPE)lEncodingType;

    zend_object *zobj = Z_OBJ_P(getThis());
    signed_data_obj *obj =
        (signed_data_obj *)((char *)zobj - XtOffsetOf(signed_data_obj, zobj));

    zobj = Z_OBJ_P(zSigner);
    signer_obj *pSigner =
        (signer_obj *)((char *)zobj - XtOffsetOf(signer_obj, zobj));

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->CoSign(pSigner->m_pCppCadesImpl,
                                                      EncodingType, &bVal));

    lVal = bVal.cbData();
    sVal = (char *)ecalloc(lVal, sizeof(char));
    memcpy(sVal, bVal.pbData(), lVal);

    RETURN_STRINGL(sVal, lVal);
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

    if (zend_parse_parameters(ZEND_NUM_ARGS() , "Oll", &zSigner,
                              signer_ce, &lCadesType, &lEncodingType) == FAILURE)
        RETURN_WITH_EXCEPTION(E_INVALIDARG);

    CadesType = (CADESCOM_CADES_TYPE)lCadesType;
    EncodingType = (CAPICOM_ENCODING_TYPE)lEncodingType;

    zend_object *zobj = Z_OBJ_P(getThis());
    signed_data_obj *obj =
        (signed_data_obj *)((char *)zobj - XtOffsetOf(signed_data_obj, zobj));

    zobj = Z_OBJ_P(zSigner);
    signer_obj *pSigner =
        (signer_obj *)((char *)zobj - XtOffsetOf(signer_obj, zobj));

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->CoSignCades(
        pSigner->m_pCppCadesImpl, CadesType, EncodingType, &bVal));

    lVal = bVal.cbData();
    sVal = (char *)ecalloc(lVal, sizeof(char));
    memcpy(sVal, bVal.pbData(), lVal);

    RETURN_STRINGL(sVal, lVal);
}

PHP_METHOD(CPSignedData, EnhanceCades) {
    long lCadesType;
    CADESCOM_CADES_TYPE CadesType;
    char *TSAAddress;
    size_t AddressLen;
    long lEncodingType;
    CAPICOM_ENCODING_TYPE EncodingType;
    CryptoPro::CBlob bVal;

    char *sVal;
    int lVal;

    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lsl", &lCadesType,
                              &TSAAddress, &AddressLen,
                              &lEncodingType) == FAILURE)
        RETURN_WITH_EXCEPTION(E_INVALIDARG);

    CadesType = (CADESCOM_CADES_TYPE)lCadesType;
    EncodingType = (CAPICOM_ENCODING_TYPE)lEncodingType;

    zend_object *zobj = Z_OBJ_P(getThis());
    signed_data_obj *obj =
        (signed_data_obj *)((char *)zobj - XtOffsetOf(signed_data_obj, zobj));
    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->EnhanceCades(
        CadesType, CAtlString(TSAAddress), EncodingType, &bVal));

    lVal = bVal.cbData();
    sVal = (char *)ecalloc(lVal, sizeof(char));
    memcpy(sVal, bVal.pbData(), lVal);

    RETURN_STRINGL(sVal, lVal);
}

PHP_METHOD(CPSignedData, Verify) {
    CryptoPro::CBlob bSignedMessage;
    unsigned char *sSignedMessage;
    size_t lSignedMessage;
    long lDetached;
    BOOL Detached;
    long lVerifyFlag;
    CAPICOM_SIGNED_DATA_VERIFY_FLAG VerifyFlag;

    if (zend_parse_parameters(ZEND_NUM_ARGS() , "sll", &sSignedMessage,
                              &lSignedMessage, &lDetached,
                              &lVerifyFlag) == FAILURE)
        RETURN_WITH_EXCEPTION(E_INVALIDARG);

    Detached = (BOOL)lDetached;
    VerifyFlag = (CAPICOM_SIGNED_DATA_VERIFY_FLAG)lVerifyFlag;

    bSignedMessage.assign(sSignedMessage, lSignedMessage);

    zend_object *zobj = Z_OBJ_P(getThis());
    signed_data_obj *obj =
        (signed_data_obj *)((char *)zobj - XtOffsetOf(signed_data_obj, zobj));
    HR_ERRORCHECK_RETURN(
        obj->m_pCppCadesImpl->Verify(bSignedMessage, Detached, VerifyFlag));
}

PHP_METHOD(CPSignedData, VerifyCades) {
    CryptoPro::CBlob bSignedMessage;
    unsigned char *sSignedMessage;
    size_t lSignedMessage;
    long lCadesType = CADESCOM_CADES_DEFAULT;
    CADESCOM_CADES_TYPE CadesType;
    long lDetached = 0;
    BOOL Detached;

    if (zend_parse_parameters(ZEND_NUM_ARGS() , "s|ll",
                              &sSignedMessage, &lSignedMessage, &lCadesType,
                              &lDetached) == FAILURE)
        RETURN_WITH_EXCEPTION(E_INVALIDARG);

    CadesType = (CADESCOM_CADES_TYPE)lCadesType;
    Detached = (BOOL)lDetached;

    bSignedMessage.assign(sSignedMessage, lSignedMessage);

    zend_object *zobj = Z_OBJ_P(getThis());
    signed_data_obj *obj =
        (signed_data_obj *)((char *)zobj - XtOffsetOf(signed_data_obj, zobj));
    HR_ERRORCHECK_RETURN(
        obj->m_pCppCadesImpl->VerifyCades(bSignedMessage, CadesType, Detached));
}

PHP_METHOD(CPSignedData, VerifyHash) {
    CryptoPro::CBlob bSignedMessage;
    zval *zHashedData;
    unsigned char *sSignedMessage;
    size_t lSignedMessage;
    long lCadesType = CADESCOM_CADES_DEFAULT;
    CADESCOM_CADES_TYPE CadesType;

    if (zend_parse_parameters(ZEND_NUM_ARGS() , "Os|l", &zHashedData,
                              hashed_data_ce, &sSignedMessage,
                              &lSignedMessage, &lCadesType) == FAILURE)
        RETURN_WITH_EXCEPTION(E_INVALIDARG);

    CadesType = (CADESCOM_CADES_TYPE)lCadesType;

    bSignedMessage.assign(sSignedMessage, lSignedMessage);

    zend_object *zobj = Z_OBJ_P(getThis());
    signed_data_obj *obj =
        (signed_data_obj *)((char *)zobj - XtOffsetOf(signed_data_obj, zobj));

    zobj = Z_OBJ_P(zHashedData);
    hashed_data_obj *pHashedData =
        (hashed_data_obj *)((char *)zobj - XtOffsetOf(hashed_data_obj, zobj));

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->VerifyHash(
        pHashedData->m_pCppCadesImpl, bSignedMessage, CadesType));
}

PHP_METHOD(CPSignedData, set_ContentEncoding) {
    long lType;
    CADESCOM_CONTENT_ENCODING_TYPE Type;

    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &lType) ==
        FAILURE)
        RETURN_WITH_EXCEPTION(E_INVALIDARG);

    Type = (CADESCOM_CONTENT_ENCODING_TYPE)lType;

    zend_object *zobj = Z_OBJ_P(getThis());
    signed_data_obj *obj =
        (signed_data_obj *)((char *)zobj - XtOffsetOf(signed_data_obj, zobj));
    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->put_ContentEncoding(Type));
}

PHP_METHOD(CPSignedData, get_ContentEncoding) {
    CADESCOM_CONTENT_ENCODING_TYPE type;

    zend_object *zobj = Z_OBJ_P(getThis());
    signed_data_obj *obj =
        (signed_data_obj *)((char *)zobj - XtOffsetOf(signed_data_obj, zobj));
    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_ContentEncoding(&type));

    RETURN_LONG(type);
}

PHP_METHOD(CPSignedData, set_Content) {
    char *sVal;
    size_t lVal;

    if (zend_parse_parameters(ZEND_NUM_ARGS() , "s", &sVal, &lVal) ==
        FAILURE)
        RETURN_WITH_EXCEPTION(E_INVALIDARG);

    zend_object *zobj = Z_OBJ_P(getThis());
    signed_data_obj *obj =
        (signed_data_obj *)((char *)zobj - XtOffsetOf(signed_data_obj, zobj));
    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->put_Content(sVal, lVal));
}

PHP_METHOD(CPSignedData, get_Content) {
    CStringBlob Val;
    char *sVal;
    int lVal;

    zend_object *zobj = Z_OBJ_P(getThis());
    signed_data_obj *obj =
        (signed_data_obj *)((char *)zobj - XtOffsetOf(signed_data_obj, zobj));
    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_Content(Val));

    lVal = Val.GetLength();
    sVal = (char *)ecalloc(lVal, sizeof(char));
    memcpy(sVal, Val, lVal);

    RETURN_STRINGL(sVal, lVal);
}

PHP_METHOD(CPSignedData, get_Signers) {
    zend_object *zobj = Z_OBJ_P(getThis());
    signed_data_obj *obj =
        (signed_data_obj *)((char *)zobj - XtOffsetOf(signed_data_obj, zobj));

    object_init_ex(return_value, signers_ce);
    zobj = Z_OBJ_P(return_value);
    signers_obj *pSigners =
        (signers_obj *)((char *)zobj - XtOffsetOf(signers_obj, zobj));
    HR_ERRORCHECK_RETURN(
        obj->m_pCppCadesImpl->get_Signers(pSigners->m_pCppCadesImpl));

    return;
}

PHP_METHOD(CPSignedData, get_Certificates) {
    NS_SHARED_PTR::shared_ptr<CPPCadesCPCertificatesObject> pVal;

    zend_object *zobj = Z_OBJ_P(getThis());
    signed_data_obj *obj =
        (signed_data_obj *)((char *)zobj - XtOffsetOf(signed_data_obj, zobj));
    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_Certificates(pVal));

    object_init_ex(return_value, certs_ce);
    zobj = Z_OBJ_P(return_value);
    certs_obj *pCertificates =
        (certs_obj *)((char *)zobj - XtOffsetOf(certs_obj, zobj));
    pCertificates->m_pCppCadesImpl = pVal;
}

#if IS_CADES_VERSION_GREATER_EQUAL(2, 0, 15260)
PHP_METHOD(CPSignedData, GetMsgType) {
    char *sVal;
    size_t lVal;

    if (zend_parse_parameters(ZEND_NUM_ARGS() , "s", &sVal, &lVal) ==
        FAILURE)
        RETURN_WITH_EXCEPTION(E_INVALIDARG);

    zend_object *zobj = Z_OBJ_P(getThis());
    signed_data_obj *obj =
        (signed_data_obj *)((char *)zobj - XtOffsetOf(signed_data_obj, zobj));
    CStringBlob msg(sVal);
    DWORD result = 0;
    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->GetMsgType(msg, &result));
    RETURN_LONG(result);
}

PHP_METHOD(CPSignedData, IsMsgType) {
    long type = 1;
    char *str;
    size_t len;

    if (zend_parse_parameters(ZEND_NUM_ARGS() , "sl", &str, &len,
                              &type) == FAILURE)
        RETURN_WITH_EXCEPTION(E_INVALIDARG);

    zend_object *zobj = Z_OBJ_P(getThis());
    signed_data_obj *obj =
        (signed_data_obj *)((char *)zobj - XtOffsetOf(signed_data_obj, zobj));
    CStringBlob msg(str);
    BOOL res = 0;
    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->IsMsgType(msg, type, &res));
    RETURN_LONG(res);
}
#endif

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpsigneddata_construct, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpsigneddata_signcades, 0, 0, 4)
 ZEND_ARG_INFO(0, signer)
 ZEND_ARG_INFO(0, cadestype)
 ZEND_ARG_INFO(0, detached)
 ZEND_ARG_INFO(0, encodingtype)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpsigneddata_signhash, 0, 0, 4)
 ZEND_ARG_INFO(0, hasheddata)
 ZEND_ARG_INFO(0, signer)
 ZEND_ARG_INFO(0, cadestype)
 ZEND_ARG_INFO(0, encodingtype)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpsigneddata_sign, 0, 0, 3)
 ZEND_ARG_INFO(0, signer)
 ZEND_ARG_INFO(0, detached)
 ZEND_ARG_INFO(0, encodingtype)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpsigneddata_cosign, 0, 0, 2)
 ZEND_ARG_INFO(0, signer)
 ZEND_ARG_INFO(0, encodingtype)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpsigneddata_cosigncades, 0, 0, 3)
 ZEND_ARG_INFO(0, signer)
 ZEND_ARG_INFO(0, cadestype)
 ZEND_ARG_INFO(0, encodingtype)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpsigneddata_cosignhash, 0, 0, 4)
 ZEND_ARG_INFO(0, signer)
 ZEND_ARG_INFO(0, hasheddata)
 ZEND_ARG_INFO(0, cadestype)
 ZEND_ARG_INFO(0, encodingtype)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpsigneddata_enhancecades, 0, 0, 3)
 ZEND_ARG_INFO(0, cadestype)
 ZEND_ARG_INFO(0, tsaaddress)
 ZEND_ARG_INFO(0, encodingtype)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpsigneddata_verifycades, 0, 0, 1)
 ZEND_ARG_INFO(0, message)
 ZEND_ARG_INFO(0, cadestype)
 ZEND_ARG_INFO(0, detached)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpsigneddata_verifyhash, 0, 0, 2)
 ZEND_ARG_INFO(0, hasheddata)
 ZEND_ARG_INFO(0, message)
 ZEND_ARG_INFO(0, cadestype)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpsigneddata_verify, 0, 0, 3)
 ZEND_ARG_INFO(0, message)
 ZEND_ARG_INFO(0, detached)
 ZEND_ARG_INFO(0, verifyflag)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpsigneddata_set_contentencoding, 0, 0, 1)
 ZEND_ARG_INFO(0, contentencoding)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpsigneddata_get_contentencoding, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpsigneddata_set_content, 0, 0, 1)
 ZEND_ARG_INFO(0, content)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpsigneddata_get_content, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpsigneddata_get_signers, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpsigneddata_get_certificates, 0, 0, 0)
ZEND_END_ARG_INFO()

#if IS_CADES_VERSION_GREATER_EQUAL(2, 0, 15260)
ZEND_BEGIN_ARG_INFO_EX(arginfo_cpsigneddata_getmsgtype, 0, 0, 1)
 ZEND_ARG_INFO(0, message)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpsigneddata_ismsgtype, 0, 0, 2)
 ZEND_ARG_INFO(0, message)
 ZEND_ARG_INFO(0, type)
ZEND_END_ARG_INFO()
#endif

zend_class_entry *signed_data_ce;
zend_object_handlers signed_data_obj_handlers;

zend_function_entry signed_data_methods[] = {
    PHP_ME(CPSignedData, __construct, arginfo_cpsigneddata_construct, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
    PHP_ME(CPSignedData, SignCades, arginfo_cpsigneddata_signcades, ZEND_ACC_PUBLIC)
    PHP_ME(CPSignedData, SignHash, arginfo_cpsigneddata_signhash, ZEND_ACC_PUBLIC)
    PHP_ME(CPSignedData, Sign, arginfo_cpsigneddata_sign, ZEND_ACC_PUBLIC)
    PHP_ME(CPSignedData, CoSign, arginfo_cpsigneddata_cosign, ZEND_ACC_PUBLIC)
    PHP_ME(CPSignedData, CoSignCades, arginfo_cpsigneddata_cosigncades, ZEND_ACC_PUBLIC)
    PHP_ME(CPSignedData, CoSignHash, arginfo_cpsigneddata_cosignhash, ZEND_ACC_PUBLIC)
    PHP_ME(CPSignedData, EnhanceCades, arginfo_cpsigneddata_enhancecades, ZEND_ACC_PUBLIC)
    PHP_ME(CPSignedData, VerifyCades, arginfo_cpsigneddata_verifycades, ZEND_ACC_PUBLIC)
    PHP_ME(CPSignedData, VerifyHash, arginfo_cpsigneddata_verifyhash, ZEND_ACC_PUBLIC)
    PHP_ME(CPSignedData, Verify, arginfo_cpsigneddata_verify, ZEND_ACC_PUBLIC)
    PHP_ME(CPSignedData, set_ContentEncoding, arginfo_cpsigneddata_set_contentencoding, ZEND_ACC_PUBLIC)
    PHP_ME(CPSignedData, get_ContentEncoding, arginfo_cpsigneddata_get_contentencoding, ZEND_ACC_PUBLIC)
    PHP_ME(CPSignedData, set_Content, arginfo_cpsigneddata_set_content, ZEND_ACC_PUBLIC)
    PHP_ME(CPSignedData, get_Content, arginfo_cpsigneddata_get_content, ZEND_ACC_PUBLIC)
    PHP_ME(CPSignedData, get_Signers, arginfo_cpsigneddata_get_signers, ZEND_ACC_PUBLIC)
    PHP_ME(CPSignedData, get_Certificates, arginfo_cpsigneddata_get_certificates, ZEND_ACC_PUBLIC)
#if IS_CADES_VERSION_GREATER_EQUAL(2, 0, 15260)
    PHP_ME(CPSignedData, GetMsgType, arginfo_cpsigneddata_getmsgtype, ZEND_ACC_PUBLIC)
    PHP_ME(CPSignedData, IsMsgType, arginfo_cpsigneddata_ismsgtype, ZEND_ACC_PUBLIC)
#endif
    {NULL, NULL, NULL}};

static void signed_data_free(zend_object *object ) {
    signed_data_obj *obj = (signed_data_obj *)((char *)object - XtOffsetOf(signed_data_obj, zobj));
    delete(obj->m_pCppCadesImpl);

    zend_object_std_dtor(object);
}

static zend_object* signed_data_create_handler(zend_class_entry *ce ) {
    signed_data_obj *obj = (signed_data_obj *)emalloc(sizeof(signed_data_obj) + zend_object_properties_size(ce));
    memset(obj, 0, sizeof(signed_data_obj) + zend_object_properties_size(ce));
    
    zend_object_std_init(&obj->zobj, ce);
    object_properties_init(&obj->zobj, ce);
    obj->zobj.handlers = &signed_data_obj_handlers;

    return &obj->zobj;
}

void signed_data_init(void) {
    zend_class_entry ce;
    INIT_CLASS_ENTRY(ce, "CPSignedData", signed_data_methods);
    signed_data_ce = zend_register_internal_class(&ce );
    signed_data_ce->create_object = signed_data_create_handler;
    memcpy(&signed_data_obj_handlers, zend_get_std_object_handlers(),
           sizeof(zend_object_handlers));
    signed_data_obj_handlers.clone_obj = NULL;
    signed_data_obj_handlers.free_obj = signed_data_free;
    signed_data_obj_handlers.offset = XtOffsetOf(signed_data_obj, zobj);
}
