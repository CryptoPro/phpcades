#include "stdafx.h"
#include "PHPCadesCPSignedXML.h"
#include "PHPCadesCPSigner.h"
#include "PHPCadesCPSigners.h"
using namespace CryptoPro::PKI::CAdES;

PHP_METHOD(CPSignedXML, __construct) {
    sig_xml_obj *obj =
        (sig_xml_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);
    obj->m_pCppCadesImpl = NS_SHARED_PTR::shared_ptr<CPPCadesSignedXMLObject>(
        new CPPCadesSignedXMLObject());
}

PHP_METHOD(CPSignedXML, set_Content) {
    char *str;
    int len;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &str, &len) ==
        FAILURE)
        RETURN_WITH_EXCEPTION(E_INVALIDARG);

    sig_xml_obj *obj =
        (sig_xml_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);
    CStringBlob content(str);

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->put_Content(content));
}

PHP_METHOD(CPSignedXML, get_Content) {
    CStringBlob content;

    sig_xml_obj *obj =
        (sig_xml_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);
    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_Content(content));

    RETURN_ATL_STRING_A(content)
}

PHP_METHOD(CPSignedXML, set_SignatureType) {
    CADESCOM_XML_SIGNATURE_TYPE type;
    long ltype;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &ltype) ==
        FAILURE)
        RETURN_WITH_EXCEPTION(E_INVALIDARG);

    type = (CADESCOM_XML_SIGNATURE_TYPE)ltype;

    sig_xml_obj *obj =
        (sig_xml_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->put_SignatureType(type));
}

PHP_METHOD(CPSignedXML, set_DigestMethod) {
    char *str;
    int len;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &str, &len) ==
        FAILURE)
        RETURN_WITH_EXCEPTION(E_INVALIDARG);

    sig_xml_obj *obj =
        (sig_xml_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);
    CStringBlob method(str);

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->put_DigestMethod(method));
}

PHP_METHOD(CPSignedXML, set_SignatureMethod) {
    char *str;
    int len;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &str, &len) ==
        FAILURE)
        RETURN_WITH_EXCEPTION(E_INVALIDARG);

    sig_xml_obj *obj =
        (sig_xml_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);
    CStringBlob method(str);

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->put_SignatureMethod(method));
}

PHP_METHOD(CPSignedXML, get_Signers) {
    sig_xml_obj *obj =
        (sig_xml_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);

    object_init_ex(return_value, signers_ce);
    signers_obj *pSigners =
        (signers_obj *)zend_object_store_get_object(return_value TSRMLS_CC);

    HR_ERRORCHECK_RETURN(
        obj->m_pCppCadesImpl->get_Signers(pSigners->m_pCppCadesImpl));
}

PHP_METHOD(CPSignedXML, Sign) {
    zval *zsigner;
    CStringBlob sign;
    char *data_str;
    int data_len = 0;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "Os", &zsigner, sig_ce,
                              &data_str, &data_len) == FAILURE)
        RETURN_WITH_EXCEPTION(E_INVALIDARG);

    sig_xml_obj *obj =
        (sig_xml_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);
    sig_obj *signer =
        (sig_obj *)zend_object_store_get_object(zsigner TSRMLS_CC);
    CStringBlob path(data_str);

    HR_ERRORCHECK_RETURN(
        obj->m_pCppCadesImpl->Sign(signer->m_pCppCadesImpl, path, sign));

    RETURN_ATL_STRING_A(sign)
}

PHP_METHOD(CPSignedXML, Verify) {
    char *str_mes, *str_path;
    int len_mes, len_path;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ss", &str_mes,
                              &len_mes, &str_path, &len_path) == FAILURE)
        RETURN_WITH_EXCEPTION(E_INVALIDARG);

    CStringBlob mes(str_mes, len_mes);
    CStringBlob path(str_path, len_path);
    sig_xml_obj *obj =
        (sig_xml_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->Verify(mes, path));
}

zend_object_handlers sig_xml_obj_handlers;
zend_class_entry *sig_xml_ce;

void sig_xml_free_storage(void *object TSRMLS_DC) {
    sig_xml_obj *obj = (sig_xml_obj *)object;
    obj->m_pCppCadesImpl.reset();

    zend_hash_destroy(obj->zo.properties);
    FREE_HASHTABLE(obj->zo.properties);

    efree(obj);
}

zend_object_value sig_xml_create_handler(zend_class_entry *type TSRMLS_DC) {
    zend_object_value retval;

    sig_xml_obj *obj = (sig_xml_obj *)emalloc(sizeof(sig_xml_obj));
    memset(obj, 0, sizeof(sig_xml_obj));
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
        zend_objects_store_put(obj, NULL, sig_xml_free_storage, NULL TSRMLS_CC);
    retval.handlers = &sig_xml_obj_handlers;

    return retval;
}

//связывание методов класса в function entry
zend_function_entry sig_xml_methods[] = {
    PHP_ME(CPSignedXML, __construct, NULL, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
    PHP_ME(CPSignedXML, set_Content, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(CPSignedXML, get_Content, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(CPSignedXML, set_SignatureType, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(CPSignedXML, set_DigestMethod, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(CPSignedXML, set_SignatureMethod, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(CPSignedXML, get_Signers, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(CPSignedXML, Sign, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(CPSignedXML, Verify, NULL, ZEND_ACC_PUBLIC){NULL, NULL, NULL}};

void sig_xml_init(TSRMLS_D) {
    zend_class_entry ce;
    INIT_CLASS_ENTRY(ce, "CPSignedXML", sig_xml_methods);
    sig_xml_ce = zend_register_internal_class(&ce TSRMLS_CC);
    sig_xml_ce->create_object = sig_xml_create_handler;
    memcpy(&sig_xml_obj_handlers, zend_get_std_object_handlers(),
           sizeof(zend_object_handlers));
    sig_xml_obj_handlers.clone_obj = NULL;
}
