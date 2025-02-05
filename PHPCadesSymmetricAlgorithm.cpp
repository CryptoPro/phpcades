#include "stdafx.h"
#include "PHPCadesSymmetricAlgorithm.h"
#include "PHPCadesCPCertificate.h"
#include "Blob.h"
using namespace CryptoPro::PKI::CAdES;
using namespace CryptoPro;

PHP_METHOD(SymmetricAlgorithm, __construct) {
    zend_object *zobj = Z_OBJ_P(getThis());
    symmetric_algorithm_obj *obj =
        (symmetric_algorithm_obj *)((char *)zobj - XtOffsetOf(symmetric_algorithm_obj, zobj));

    obj->m_pCppCadesImpl = NS_SHARED_PTR::shared_ptr<CPPCadesSymmetricAlgorithmObject>(
        new CPPCadesSymmetricAlgorithmObject());
}

PHP_METHOD(SymmetricAlgorithm, get_DiversData) {
    CBlob value;

    zend_object *zobj = Z_OBJ_P(getThis());
    symmetric_algorithm_obj *obj =
        (symmetric_algorithm_obj *)((char *)zobj - XtOffsetOf(symmetric_algorithm_obj, zobj));


    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_DiversData(value));

    char *ret_str = (char *)ecalloc(value.cbData(), sizeof(char));
    strncpy(ret_str, (const char *)value.pbData(), value.cbData());
    RETURN_STRINGL(ret_str, value.cbData());
}

PHP_METHOD(SymmetricAlgorithm, set_DiversData) {
    char *str;
    size_t len;

    if (zend_parse_parameters(ZEND_NUM_ARGS() , "s", &str, &len) ==
        FAILURE)
        RETURN_WITH_EXCEPTION(E_INVALIDARG);

    zend_object *zobj = Z_OBJ_P(getThis());
    symmetric_algorithm_obj *obj =
        (symmetric_algorithm_obj *)((char *)zobj - XtOffsetOf(symmetric_algorithm_obj, zobj));


    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->put_DiversData(str, len));
}

PHP_METHOD(SymmetricAlgorithm, get_IV) {
    CBlob value;

    zend_object *zobj = Z_OBJ_P(getThis());
    symmetric_algorithm_obj *obj =
        (symmetric_algorithm_obj *)((char *)zobj - XtOffsetOf(symmetric_algorithm_obj, zobj));

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_IV(value));

    char *ret_str = (char *)ecalloc(value.cbData(), sizeof(char));
    strncpy(ret_str, (const char *)value.pbData(), value.cbData());
    RETURN_STRINGL(ret_str, value.cbData());
}

PHP_METHOD(SymmetricAlgorithm, set_IV) {
    char *str;
    size_t len;

    if (zend_parse_parameters(ZEND_NUM_ARGS() , "s", &str, &len) ==
        FAILURE)
        RETURN_WITH_EXCEPTION(E_INVALIDARG);

    zend_object *zobj = Z_OBJ_P(getThis());
    symmetric_algorithm_obj *obj =
        (symmetric_algorithm_obj *)((char *)zobj - XtOffsetOf(symmetric_algorithm_obj, zobj));


    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->put_IV(str, len));
}

PHP_METHOD(SymmetricAlgorithm, Encrypt) {
    long isFinal = 1;
    char *str;
    size_t len;

    if (zend_parse_parameters(ZEND_NUM_ARGS() , "sl", &str, &len,
                              &isFinal) == FAILURE)
        RETURN_WITH_EXCEPTION(E_INVALIDARG);

    zend_object *zobj = Z_OBJ_P(getThis());
    symmetric_algorithm_obj *obj =
        (symmetric_algorithm_obj *)((char *)zobj - XtOffsetOf(symmetric_algorithm_obj, zobj));

    CStringProxy retval;
    HR_ERRORCHECK_RETURN(
        obj->m_pCppCadesImpl->Encrypt(str, len, isFinal, retval));

    RETURN_PROXY_STRING(retval);
}

PHP_METHOD(SymmetricAlgorithm, Decrypt) {
    long isFinal = 1;
    char *str;
    size_t len;

    if (zend_parse_parameters(ZEND_NUM_ARGS() , "s|l", &str, &len,
                              &isFinal) == FAILURE)
        RETURN_WITH_EXCEPTION(E_INVALIDARG);

    zend_object *zobj = Z_OBJ_P(getThis());
    symmetric_algorithm_obj *obj =
        (symmetric_algorithm_obj *)((char *)zobj - XtOffsetOf(symmetric_algorithm_obj, zobj));

    CBlob value;
    HR_ERRORCHECK_RETURN(
        obj->m_pCppCadesImpl->Decrypt(str, len, isFinal, value));

    char *ret_str = (char *)ecalloc(value.cbData(), sizeof(char));
    strncpy(ret_str, (const char *)value.pbData(), value.cbData());
    RETURN_STRINGL(ret_str, value.cbData());
}

PHP_METHOD(SymmetricAlgorithm, DiversifyKey) {
    NS_SHARED_PTR::shared_ptr<CPPCadesSymmetricAlgorithmObject> pVal;

    zend_object *zobj = Z_OBJ_P(getThis());
    symmetric_algorithm_obj *obj =
        (symmetric_algorithm_obj *)((char *)zobj - XtOffsetOf(symmetric_algorithm_obj, zobj));

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->DiversifyKey(pVal));

    object_init_ex(return_value, symmetric_algorithm_ce);
    zobj = Z_OBJ_P(return_value);
    symmetric_algorithm_obj *psym_algo_obj =
        (symmetric_algorithm_obj *)((char *)zobj - XtOffsetOf(symmetric_algorithm_obj, zobj));
    psym_algo_obj->m_pCppCadesImpl = pVal;
}

PHP_METHOD(SymmetricAlgorithm, GenerateKey) {
    long lAlgo = -1;

    if (zend_parse_parameters(ZEND_NUM_ARGS() , "|l", &lAlgo) ==
        FAILURE)
        RETURN_WITH_EXCEPTION(E_INVALIDARG);

    CADESCOM_ENCRYPTION_ALGORITHM algorithm =
        CADESCOM_ENCRYPTION_ALGORITHM_GOST_28147_89;
    if (lAlgo != -1)
        algorithm = (CADESCOM_ENCRYPTION_ALGORITHM)lAlgo;

    zend_object *zobj = Z_OBJ_P(getThis());
    symmetric_algorithm_obj *obj =
        (symmetric_algorithm_obj *)((char *)zobj - XtOffsetOf(symmetric_algorithm_obj, zobj));

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->GenerateKey(algorithm));
}

PHP_METHOD(SymmetricAlgorithm, ExportKey) {
    zval *z_recipient;

    if (zend_parse_parameters(ZEND_NUM_ARGS() , "O", &z_recipient,
                              cert_ce) == FAILURE)
        RETURN_WITH_EXCEPTION(E_INVALIDARG);

    zend_object *zobj = Z_OBJ_P(getThis());
    symmetric_algorithm_obj *obj =
        (symmetric_algorithm_obj *)((char *)zobj - XtOffsetOf(symmetric_algorithm_obj, zobj));
    
    zobj = Z_OBJ_P(z_recipient);   
    certificate_obj *pCert =
        (certificate_obj *)((char *)zobj - XtOffsetOf(certificate_obj, zobj));

    CBlob value;
    HR_ERRORCHECK_RETURN(
        obj->m_pCppCadesImpl->ExportKey(pCert->m_pCppCadesImpl, value));

    char *ret_str = (char *)ecalloc(value.cbData(), sizeof(char));
    strncpy(ret_str, (const char *)value.pbData(), value.cbData());
    RETURN_STRINGL(ret_str, value.cbData());
}

PHP_METHOD(SymmetricAlgorithm, ImportKey) {
    zval *z_recipient;
    char *data_str;
    size_t ldata_str = 0;
    char *pin_str;
    size_t lpin_str = 0;

    if (zend_parse_parameters(ZEND_NUM_ARGS() , "sO|s", &data_str,
                              &ldata_str, &z_recipient, cert_ce, &pin_str,
                              &lpin_str) == FAILURE)
        RETURN_WITH_EXCEPTION(E_INVALIDARG);

    zend_object *zobj = Z_OBJ_P(getThis());
    symmetric_algorithm_obj *obj =
        (symmetric_algorithm_obj *)((char *)zobj - XtOffsetOf(symmetric_algorithm_obj, zobj));

    zobj = Z_OBJ_P(z_recipient);   
    certificate_obj *pCert =
        (certificate_obj *)((char *)zobj - XtOffsetOf(certificate_obj, zobj));

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->ImportKey(
        data_str, ldata_str, pCert->m_pCppCadesImpl, pin_str, lpin_str));
}

zend_object_handlers symmetric_algorithm_obj_handlers;
zend_class_entry *symmetric_algorithm_ce;

static void symmetric_algorithm_free(zend_object *object ) {
    symmetric_algorithm_obj *obj = (symmetric_algorithm_obj *)((char *)object - XtOffsetOf(symmetric_algorithm_obj, zobj));
    obj->m_pCppCadesImpl.reset();

    zend_object_std_dtor(object);
}

static zend_object* symmetric_algorithm_create_handler(zend_class_entry *ce
                                                         ) {
    symmetric_algorithm_obj *obj = (symmetric_algorithm_obj *)emalloc(sizeof(symmetric_algorithm_obj) + zend_object_properties_size(ce));
    memset(obj, 0, sizeof(symmetric_algorithm_obj) + zend_object_properties_size(ce));
    
    zend_object_std_init(&obj->zobj, ce);
    object_properties_init(&obj->zobj, ce);
    obj->zobj.handlers = &symmetric_algorithm_obj_handlers;

    return &obj->zobj;
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpsymmetricalgorithm_construct, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpsymmetricalgorithm_get_diversdata, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpsymmetricalgorithm_set_diversdata, 0, 0, 1)
 ZEND_ARG_INFO(0, data)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpsymmetricalgorithm_get_iv, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpsymmetricalgorithm_set_iv, 0, 0, 1)
 ZEND_ARG_INFO(0, iv)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpsymmetricalgorithm_encrypt, 0, 0, 2)
 ZEND_ARG_INFO(0, data)
 ZEND_ARG_INFO(0, isfinal)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpsymmetricalgorithm_decrypt, 0, 0, 1)
 ZEND_ARG_INFO(0, message)
 ZEND_ARG_INFO(0, isfinal)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpsymmetricalgorithm_generatekey, 0, 0, 0)
 ZEND_ARG_INFO(0, algorithm)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpsymmetricalgorithm_diversifykey, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpsymmetricalgorithm_importkey, 0, 0, 2)
 ZEND_ARG_INFO(0, data)
 ZEND_ARG_INFO(0, certificate)
 ZEND_ARG_INFO(0, pin)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpsymmetricalgorithm_exportkey, 0, 0, 1)
 ZEND_ARG_INFO(0, certificate)
ZEND_END_ARG_INFO()

//связывание методов класса в function entry
zend_function_entry symmetric_algorithm_methods[] = {
    PHP_ME(SymmetricAlgorithm, __construct, arginfo_cpsymmetricalgorithm_construct, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
    PHP_ME(SymmetricAlgorithm, get_DiversData, arginfo_cpsymmetricalgorithm_get_diversdata, ZEND_ACC_PUBLIC)
    PHP_ME(SymmetricAlgorithm, set_DiversData, arginfo_cpsymmetricalgorithm_set_diversdata, ZEND_ACC_PUBLIC)
    PHP_ME(SymmetricAlgorithm, get_IV, arginfo_cpsymmetricalgorithm_get_iv, ZEND_ACC_PUBLIC)
    PHP_ME(SymmetricAlgorithm, set_IV, arginfo_cpsymmetricalgorithm_set_iv, ZEND_ACC_PUBLIC)
    PHP_ME(SymmetricAlgorithm, Encrypt, arginfo_cpsymmetricalgorithm_encrypt, ZEND_ACC_PUBLIC)
    PHP_ME(SymmetricAlgorithm, Decrypt, arginfo_cpsymmetricalgorithm_decrypt, ZEND_ACC_PUBLIC)
    PHP_ME(SymmetricAlgorithm, GenerateKey, arginfo_cpsymmetricalgorithm_generatekey, ZEND_ACC_PUBLIC)
    PHP_ME(SymmetricAlgorithm, DiversifyKey, arginfo_cpsymmetricalgorithm_diversifykey, ZEND_ACC_PUBLIC)
    PHP_ME(SymmetricAlgorithm, ImportKey, arginfo_cpsymmetricalgorithm_importkey, ZEND_ACC_PUBLIC)
    PHP_ME(SymmetricAlgorithm, ExportKey, arginfo_cpsymmetricalgorithm_exportkey, ZEND_ACC_PUBLIC)
    {NULL, NULL, NULL}};

void symmetric_algorithm_init(void) {
    zend_class_entry ce;
    INIT_CLASS_ENTRY(ce, "SymmetricAlgorithm", symmetric_algorithm_methods);
    symmetric_algorithm_ce = zend_register_internal_class(&ce );
    symmetric_algorithm_ce->create_object = symmetric_algorithm_create_handler;
    memcpy(&symmetric_algorithm_obj_handlers, zend_get_std_object_handlers(),
           sizeof(zend_object_handlers));
    symmetric_algorithm_obj_handlers.clone_obj = NULL;
    symmetric_algorithm_obj_handlers.free_obj = symmetric_algorithm_free;
    symmetric_algorithm_obj_handlers.offset = XtOffsetOf(symmetric_algorithm_obj, zobj);
}
