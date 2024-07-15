#include "stdafx.h"
#include "PHPCadesSymmetricAlgorithm.h"
#include "PHPCadesCPCertificate.h"
#include "Blob.h"
using namespace CryptoPro::PKI::CAdES;
using namespace CryptoPro;

PHP_METHOD(SymmetricAlgorithm, __construct) {
    symmetric_algorithm_obj *obj =
        (symmetric_algorithm_obj *)zend_object_store_get_object(getThis()
                                                                TSRMLS_CC);
    obj->m_pCppCadesImpl = boost::shared_ptr<CPPCadesSymmetricAlgorithmObject>(
        new CPPCadesSymmetricAlgorithmObject());
}

PHP_METHOD(SymmetricAlgorithm, get_DiversData) {
    CBlob value;

    symmetric_algorithm_obj *obj =
        (symmetric_algorithm_obj *)zend_object_store_get_object(getThis()
                                                                TSRMLS_CC);

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_DiversData(value));

    char *ret_str = (char *)ecalloc(value.cbData(), sizeof(char));
    strncpy(ret_str, (const char *)value.pbData(), value.cbData());
    RETURN_STRINGL(ret_str, value.cbData(), 0)
}

PHP_METHOD(SymmetricAlgorithm, set_DiversData) {
    char *str;
    unsigned int len;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &str, &len) ==
        FAILURE)
        RETURN_WITH_EXCEPTION(E_INVALIDARG);

    symmetric_algorithm_obj *obj =
        (symmetric_algorithm_obj *)zend_object_store_get_object(getThis()
                                                                TSRMLS_CC);

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->put_DiversData(str, len));
}

PHP_METHOD(SymmetricAlgorithm, get_IV) {
    CBlob value;

    symmetric_algorithm_obj *obj =
        (symmetric_algorithm_obj *)zend_object_store_get_object(getThis()
                                                                TSRMLS_CC);
    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_IV(value));

    char *ret_str = (char *)ecalloc(value.cbData(), sizeof(char));
    strncpy(ret_str, (const char *)value.pbData(), value.cbData());
    RETURN_STRINGL(ret_str, value.cbData(), 0)
}

PHP_METHOD(SymmetricAlgorithm, set_IV) {
    char *str;
    unsigned int len;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &str, &len) ==
        FAILURE)
        RETURN_WITH_EXCEPTION(E_INVALIDARG);

    symmetric_algorithm_obj *obj =
        (symmetric_algorithm_obj *)zend_object_store_get_object(getThis()
                                                                TSRMLS_CC);

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->put_IV(str, len));
}

PHP_METHOD(SymmetricAlgorithm, Encrypt) {
    long isFinal = 1;
    char *str;
    int len;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "sl", &str, &len,
                              &isFinal) == FAILURE)
        RETURN_WITH_EXCEPTION(E_INVALIDARG);

    symmetric_algorithm_obj *obj =
        (symmetric_algorithm_obj *)zend_object_store_get_object(getThis()
                                                                TSRMLS_CC);
    CStringProxy retval;
    HR_ERRORCHECK_RETURN(
        obj->m_pCppCadesImpl->Encrypt(str, len, isFinal, retval));

    RETURN_PROXY_STRING(retval)
}

PHP_METHOD(SymmetricAlgorithm, Decrypt) {
    long isFinal = 1;
    char *str;
    int len;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s|l", &str, &len,
                              &isFinal) == FAILURE)
        RETURN_WITH_EXCEPTION(E_INVALIDARG);

    symmetric_algorithm_obj *obj =
        (symmetric_algorithm_obj *)zend_object_store_get_object(getThis()
                                                                TSRMLS_CC);
    CBlob value;
    HR_ERRORCHECK_RETURN(
        obj->m_pCppCadesImpl->Decrypt(str, len, isFinal, value));

    char *ret_str = (char *)ecalloc(value.cbData(), sizeof(char));
    strncpy(ret_str, (const char *)value.pbData(), value.cbData());
    RETURN_STRINGL(ret_str, value.cbData(), 0)
}

PHP_METHOD(SymmetricAlgorithm, DiversifyKey) {
    boost::shared_ptr<CPPCadesSymmetricAlgorithmObject> pVal;

    symmetric_algorithm_obj *obj =
        (symmetric_algorithm_obj *)zend_object_store_get_object(getThis()
                                                                TSRMLS_CC);
    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->DiversifyKey(pVal));

    object_init_ex(return_value, symmetric_algorithm_ce);
    symmetric_algorithm_obj *psym_algo_obj =
        (symmetric_algorithm_obj *)zend_object_store_get_object(
            return_value TSRMLS_CC);
    psym_algo_obj->m_pCppCadesImpl = pVal;
}

PHP_METHOD(SymmetricAlgorithm, GenerateKey) {
    long lAlgo = -1;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "|l", &lAlgo) ==
        FAILURE)
        RETURN_WITH_EXCEPTION(E_INVALIDARG);

    CADESCOM_ENCRYPTION_ALGORITHM algorithm =
        CADESCOM_ENCRYPTION_ALGORITHM_GOST_28147_89;
    if (lAlgo != -1)
        algorithm = (CADESCOM_ENCRYPTION_ALGORITHM)lAlgo;

    symmetric_algorithm_obj *obj =
        (symmetric_algorithm_obj *)zend_object_store_get_object(getThis()
                                                                TSRMLS_CC);
    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->GenerateKey(algorithm));
}

PHP_METHOD(SymmetricAlgorithm, ExportKey) {
    zval *z_recipient;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "O", &z_recipient,
                              cert_ce) == FAILURE)
        RETURN_WITH_EXCEPTION(E_INVALIDARG);

    symmetric_algorithm_obj *obj =
        (symmetric_algorithm_obj *)zend_object_store_get_object(getThis()
                                                                TSRMLS_CC);
    cert_obj *pCert =
        (cert_obj *)zend_object_store_get_object(z_recipient TSRMLS_CC);

    CBlob value;
    HR_ERRORCHECK_RETURN(
        obj->m_pCppCadesImpl->ExportKey(pCert->m_pCppCadesImpl, value));

    char *ret_str = (char *)ecalloc(value.cbData(), sizeof(char));
    strncpy(ret_str, (const char *)value.pbData(), value.cbData());
    RETURN_STRINGL(ret_str, value.cbData(), 0)
}

PHP_METHOD(SymmetricAlgorithm, ImportKey) {
    zval *z_recipient;
    char *data_str;
    long ldata_str = 0;
    char *pin_str;
    long lpin_str = 0;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "sO|s", &data_str,
                              &ldata_str, &z_recipient, cert_ce, &pin_str,
                              &lpin_str) == FAILURE)
        RETURN_WITH_EXCEPTION(E_INVALIDARG);

    symmetric_algorithm_obj *obj =
        (symmetric_algorithm_obj *)zend_object_store_get_object(getThis()
                                                                TSRMLS_CC);
    cert_obj *pCert =
        (cert_obj *)zend_object_store_get_object(z_recipient TSRMLS_CC);

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->ImportKey(
        data_str, ldata_str, pCert->m_pCppCadesImpl, pin_str, lpin_str));
}

zend_object_handlers symmetric_algorithm_obj_handlers;
zend_class_entry *symmetric_algorithm_ce;

void symmetric_algorithm_free_storage(void *object TSRMLS_DC) {
    symmetric_algorithm_obj *obj = (symmetric_algorithm_obj *)object;
    obj->m_pCppCadesImpl.reset();

    zend_hash_destroy(obj->zo.properties);
    FREE_HASHTABLE(obj->zo.properties);

    efree(obj);
}

zend_object_value symmetric_algorithm_create_handler(zend_class_entry *type
                                                         TSRMLS_DC) {
    zend_object_value retval;

    symmetric_algorithm_obj *obj =
        (symmetric_algorithm_obj *)emalloc(sizeof(symmetric_algorithm_obj));
    memset(obj, 0, sizeof(symmetric_algorithm_obj));
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

    retval.handle = zend_objects_store_put(
        obj, NULL, symmetric_algorithm_free_storage, NULL TSRMLS_CC);
    retval.handlers = &symmetric_algorithm_obj_handlers;

    return retval;
}

//связывание методов класса в function entry
zend_function_entry symmetric_algorithm_methods[] = {
    PHP_ME(SymmetricAlgorithm, __construct, NULL,
           ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
    PHP_ME(SymmetricAlgorithm, get_DiversData, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(SymmetricAlgorithm, set_DiversData, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(SymmetricAlgorithm, get_IV, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(SymmetricAlgorithm, set_IV, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(SymmetricAlgorithm, Encrypt, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(SymmetricAlgorithm, Decrypt, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(SymmetricAlgorithm, GenerateKey, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(SymmetricAlgorithm, DiversifyKey, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(SymmetricAlgorithm, ImportKey, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(SymmetricAlgorithm, ExportKey, NULL, ZEND_ACC_PUBLIC){NULL, NULL,
                                                                 NULL}};

void symmetric_algorithm_init(TSRMLS_D) {
    zend_class_entry ce;
    INIT_CLASS_ENTRY(ce, "SymmetricAlgorithm", symmetric_algorithm_methods);
    symmetric_algorithm_ce = zend_register_internal_class(&ce TSRMLS_CC);
    symmetric_algorithm_ce->create_object = symmetric_algorithm_create_handler;
    memcpy(&symmetric_algorithm_obj_handlers, zend_get_std_object_handlers(),
           sizeof(zend_object_handlers));
    symmetric_algorithm_obj_handlers.clone_obj = NULL;
}
