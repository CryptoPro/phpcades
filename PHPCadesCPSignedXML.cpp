#include "stdafx.h"
#include "PHPCadesCPSignedXML.h"
#include "PHPCadesCPSigner.h"
#include "PHPCadesCPSigners.h"
using namespace CryptoPro::PKI::CAdES;

PHP_METHOD(CPSignedXML, __construct) {
    zend_object *zobj = Z_OBJ_P(getThis());
    signed_xml_obj *obj =
        (signed_xml_obj *)((char *)zobj - XtOffsetOf(signed_xml_obj, zobj));
    obj->m_pCppCadesImpl = NS_SHARED_PTR::shared_ptr<CPPCadesSignedXMLObject>(
        new CPPCadesSignedXMLObject());
}

PHP_METHOD(CPSignedXML, set_Content) {
    char *str;
    size_t len;

    if (zend_parse_parameters(ZEND_NUM_ARGS() , "s", &str, &len) ==
        FAILURE)
        RETURN_WITH_EXCEPTION(E_INVALIDARG);

    zend_object *zobj = Z_OBJ_P(getThis());
    signed_xml_obj *obj =
        (signed_xml_obj *)((char *)zobj - XtOffsetOf(signed_xml_obj, zobj));
    CStringBlob content(str);

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->put_Content(content));
}

PHP_METHOD(CPSignedXML, get_Content) {
    CStringBlob content;

    zend_object *zobj = Z_OBJ_P(getThis());
    signed_xml_obj *obj =
        (signed_xml_obj *)((char *)zobj - XtOffsetOf(signed_xml_obj, zobj));
    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_Content(content));

    RETURN_ATL_STRING_A(content)
}

PHP_METHOD(CPSignedXML, set_SignatureType) {
    CADESCOM_XML_SIGNATURE_TYPE type;
    long ltype;

    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &ltype) ==
        FAILURE)
        RETURN_WITH_EXCEPTION(E_INVALIDARG);

    type = (CADESCOM_XML_SIGNATURE_TYPE)ltype;

    zend_object *zobj = Z_OBJ_P(getThis());
    signed_xml_obj *obj =
        (signed_xml_obj *)((char *)zobj - XtOffsetOf(signed_xml_obj, zobj));

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->put_SignatureType(type));
}

PHP_METHOD(CPSignedXML, set_DigestMethod) {
    char *str;
    size_t len;

    if (zend_parse_parameters(ZEND_NUM_ARGS() , "s", &str, &len) ==
        FAILURE)
        RETURN_WITH_EXCEPTION(E_INVALIDARG);

    zend_object *zobj = Z_OBJ_P(getThis());
    signed_xml_obj *obj =
        (signed_xml_obj *)((char *)zobj - XtOffsetOf(signed_xml_obj, zobj));
    CStringBlob method(str);

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->put_DigestMethod(method));
}

PHP_METHOD(CPSignedXML, set_SignatureMethod) {
    char *str;
    size_t len;

    if (zend_parse_parameters(ZEND_NUM_ARGS() , "s", &str, &len) ==
        FAILURE)
        RETURN_WITH_EXCEPTION(E_INVALIDARG);

    zend_object *zobj = Z_OBJ_P(getThis());
    signed_xml_obj *obj =
        (signed_xml_obj *)((char *)zobj - XtOffsetOf(signed_xml_obj, zobj));
    CStringBlob method(str);

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->put_SignatureMethod(method));
}

PHP_METHOD(CPSignedXML, get_Signers) {
    zend_object *zobj = Z_OBJ_P(getThis());
    signed_xml_obj *obj =
        (signed_xml_obj *)((char *)zobj - XtOffsetOf(signed_xml_obj, zobj));

    object_init_ex(return_value, signers_ce);
    zobj = Z_OBJ_P(return_value);
    signers_obj *pSigners =
        (signers_obj *)((char *)zobj - XtOffsetOf(signers_obj, zobj));

    HR_ERRORCHECK_RETURN(
        obj->m_pCppCadesImpl->get_Signers(pSigners->m_pCppCadesImpl));
}

PHP_METHOD(CPSignedXML, Sign) {
    zval *zsigned_xml;
    CStringBlob sign;
    char *data_str;
    size_t data_len = 0;

    if (zend_parse_parameters(ZEND_NUM_ARGS() , "Os", &zsigned_xml, signer_ce,
                              &data_str, &data_len) == FAILURE)
        RETURN_WITH_EXCEPTION(E_INVALIDARG);

    zend_object *zobj = Z_OBJ_P(getThis());
    signed_xml_obj *obj =
        (signed_xml_obj *)((char *)zobj - XtOffsetOf(signed_xml_obj, zobj));
    zobj = Z_OBJ_P(zsigned_xml);
    signer_obj *signed_xml =
        (signer_obj *)((char *)zobj - XtOffsetOf(signer_obj, zobj));
    CStringBlob path(data_str);

    HR_ERRORCHECK_RETURN(
        obj->m_pCppCadesImpl->Sign(signed_xml->m_pCppCadesImpl, path, sign));

    RETURN_ATL_STRING_A(sign)
}

PHP_METHOD(CPSignedXML, Verify) {
    char *str_mes, *str_path;
    size_t len_mes, len_path;

    if (zend_parse_parameters(ZEND_NUM_ARGS() , "ss", &str_mes,
                              &len_mes, &str_path, &len_path) == FAILURE)
        RETURN_WITH_EXCEPTION(E_INVALIDARG);

    CStringBlob mes(str_mes, len_mes);
    CStringBlob path(str_path, len_path);
    zend_object *zobj = Z_OBJ_P(getThis());
    signed_xml_obj *obj =
        (signed_xml_obj *)((char *)zobj - XtOffsetOf(signed_xml_obj, zobj));

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->Verify(mes, path));
}

zend_object_handlers signed_xml_obj_handlers;
zend_class_entry *signed_xml_ce;

static void signed_xml_free(zend_object *object ) {
    signed_xml_obj *obj = (signed_xml_obj *)((char *)object - XtOffsetOf(signed_xml_obj, zobj));
    obj->m_pCppCadesImpl.reset();

    zend_object_std_dtor(object);
}

static zend_object* signed_xml_create_handler(zend_class_entry *ce ) {
    signed_xml_obj *obj = (signed_xml_obj *)emalloc(sizeof(signed_xml_obj) + zend_object_properties_size(ce));
    memset(obj, 0, sizeof(signed_xml_obj) + zend_object_properties_size(ce));
    
    zend_object_std_init(&obj->zobj, ce);
    object_properties_init(&obj->zobj, ce);
    obj->zobj.handlers = &signed_xml_obj_handlers;

    return &obj->zobj;
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpsignedxml_construct, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpsignedxml_set_content, 0, 0, 1)
 ZEND_ARG_INFO(0, content)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpsignedxml_get_content, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpsignedxml_set_signaturetype, 0, 0, 1)
 ZEND_ARG_INFO(0, type)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpsignedxml_set_digestmethod, 0, 0, 1)
 ZEND_ARG_INFO(0, digestmethod)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpsignedxml_set_signaturemethod, 0, 0, 1)
 ZEND_ARG_INFO(0, signaturemethod)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpsignedxml_get_signers, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpsignedxml_sign, 0, 0, 2)
 ZEND_ARG_INFO(0, signer)
 ZEND_ARG_INFO(0, data)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpsignedxml_verify, 0, 0, 2)
 ZEND_ARG_INFO(0, message)
 ZEND_ARG_INFO(0, xpath)
ZEND_END_ARG_INFO()

//связывание методов класса в function entry
zend_function_entry signed_xml_methods[] = {
    PHP_ME(CPSignedXML, __construct, arginfo_cpsignedxml_construct, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
    PHP_ME(CPSignedXML, set_Content, arginfo_cpsignedxml_set_content, ZEND_ACC_PUBLIC)
    PHP_ME(CPSignedXML, get_Content, arginfo_cpsignedxml_get_content, ZEND_ACC_PUBLIC)
    PHP_ME(CPSignedXML, set_SignatureType, arginfo_cpsignedxml_set_signaturetype, ZEND_ACC_PUBLIC)
    PHP_ME(CPSignedXML, set_DigestMethod, arginfo_cpsignedxml_set_digestmethod, ZEND_ACC_PUBLIC)
    PHP_ME(CPSignedXML, set_SignatureMethod, arginfo_cpsignedxml_set_signaturemethod, ZEND_ACC_PUBLIC)
    PHP_ME(CPSignedXML, get_Signers, arginfo_cpsignedxml_get_signers, ZEND_ACC_PUBLIC)
    PHP_ME(CPSignedXML, Sign, arginfo_cpsignedxml_sign, ZEND_ACC_PUBLIC)
    PHP_ME(CPSignedXML, Verify, arginfo_cpsignedxml_verify, ZEND_ACC_PUBLIC)
    {NULL, NULL, NULL}};

void signed_xml_init(void) {
    zend_class_entry ce;
    INIT_CLASS_ENTRY(ce, "CPSignedXML", signed_xml_methods);
    signed_xml_ce = zend_register_internal_class(&ce );
    signed_xml_ce->create_object = signed_xml_create_handler;
    memcpy(&signed_xml_obj_handlers, zend_get_std_object_handlers(),
           sizeof(zend_object_handlers));
    signed_xml_obj_handlers.clone_obj = NULL;
    signed_xml_obj_handlers.free_obj = signed_xml_free;
    signed_xml_obj_handlers.offset = XtOffsetOf(signed_xml_obj, zobj);
}
