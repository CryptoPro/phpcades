#include "stdafx.h"
#include "PHPCadesCPEnvelopedData.h"
#include "PHPCadesCPRecipients.h"
#include "CPPCadesCPSigner.h"
using namespace CryptoPro::PKI::CAdES;

PHP_METHOD(CPEnvelopedData, __construct) {
    zend_object *zobj = Z_OBJ_P(getThis());
    enveloped_data_obj *obj =
        (enveloped_data_obj *)((char *)zobj - XtOffsetOf(enveloped_data_obj, zobj));
    obj->m_pCppCadesImpl = new CPPCadesCPEnvelopedDataObject();
}

PHP_METHOD(CPEnvelopedData, get_Content) {
    CStringBlob content;

    zend_object *zobj = Z_OBJ_P(getThis());
    enveloped_data_obj *obj =
        (enveloped_data_obj *)((char *)zobj - XtOffsetOf(enveloped_data_obj, zobj));

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_Content(content));

    RETURN_ATL_STRING_A(content);
}

PHP_METHOD(CPEnvelopedData, set_Content) {
    char *str;
    size_t len;

    if (zend_parse_parameters(ZEND_NUM_ARGS() , "s", &str, &len) ==
        FAILURE)
        RETURN_WITH_EXCEPTION(E_INVALIDARG);

    zend_object *zobj = Z_OBJ_P(getThis());
    enveloped_data_obj *obj =
        (enveloped_data_obj *)((char *)zobj - XtOffsetOf(enveloped_data_obj, zobj));

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->put_Content(str, len));
}

PHP_METHOD(CPEnvelopedData, get_ContentEncoding) {
    CADESCOM_CONTENT_ENCODING_TYPE type;

    zend_object *zobj = Z_OBJ_P(getThis());
    enveloped_data_obj *obj =
        (enveloped_data_obj *)((char *)zobj - XtOffsetOf(enveloped_data_obj, zobj));

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_ContentEncoding(&type));

    RETURN_LONG(type);
}

PHP_METHOD(CPEnvelopedData, set_ContentEncoding) {
    int type;

    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &type) == FAILURE)
        RETURN_WITH_EXCEPTION(E_INVALIDARG);

    zend_object *zobj = Z_OBJ_P(getThis());
    enveloped_data_obj *obj =
        (enveloped_data_obj *)((char *)zobj - XtOffsetOf(enveloped_data_obj, zobj));
    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->put_ContentEncoding(
        (CADESCOM_CONTENT_ENCODING_TYPE)type));
}

PHP_METHOD(CPEnvelopedData, Encrypt) {
    long lType;
    CAPICOM_ENCODING_TYPE Type;
    CryptoPro::CBlob data;
    char *str;
    int len;

    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &lType) ==
        FAILURE)
        RETURN_WITH_EXCEPTION(E_INVALIDARG);

    Type = (CAPICOM_ENCODING_TYPE)lType;

    zend_object *zobj = Z_OBJ_P(getThis());
    enveloped_data_obj *obj =
        (enveloped_data_obj *)((char *)zobj - XtOffsetOf(enveloped_data_obj, zobj));

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->Encrypt(Type, data));

    len = data.cbData();
    str = (char *)ecalloc(len, sizeof(char));
    memcpy(str, data.pbData(), len);

    RETURN_STRINGL(str, len);
}

PHP_METHOD(CPEnvelopedData, Decrypt) {
    CryptoPro::CBlob data;
    unsigned char *str;
    size_t len;

    if (zend_parse_parameters(ZEND_NUM_ARGS() , "s", &str, &len) ==
        FAILURE)
        RETURN_WITH_EXCEPTION(E_INVALIDARG);

    zend_object *zobj = Z_OBJ_P(getThis());
    enveloped_data_obj *obj =
        (enveloped_data_obj *)((char *)zobj - XtOffsetOf(enveloped_data_obj, zobj));
    data.assign(str, len);

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->Decrypt(data));
}

PHP_METHOD(CPEnvelopedData, get_Recipients) {
    zend_object *zobj = Z_OBJ_P(getThis());
    enveloped_data_obj *obj =
        (enveloped_data_obj *)((char *)zobj - XtOffsetOf(enveloped_data_obj, zobj));
    object_init_ex(return_value, recipients_ce);
    zobj = Z_OBJ_P(return_value);
    recipients_obj *Recipients_ptr =
        (recipients_obj *)((char *)zobj - XtOffsetOf(recipients_obj, zobj));

    HR_ERRORCHECK_RETURN(
        obj->m_pCppCadesImpl->get_Recipients(Recipients_ptr->m_pCppCadesImpl));
}

zend_object_handlers enveloped_data_obj_handlers;
zend_class_entry *enveloped_data_ce;

static void enveloped_data_free(zend_object *object ) {
    enveloped_data_obj *obj = (enveloped_data_obj *)((char *)object - XtOffsetOf(enveloped_data_obj, zobj));
    delete(obj->m_pCppCadesImpl);

    zend_object_std_dtor(object);
}

static zend_object* enveloped_data_create_handler(zend_class_entry *ce
                                                    ) {
    enveloped_data_obj *obj = (enveloped_data_obj *)emalloc(sizeof(enveloped_data_obj) + zend_object_properties_size(ce));
    memset(obj, 0, sizeof(enveloped_data_obj) + zend_object_properties_size(ce));
    
    zend_object_std_init(&obj->zobj, ce);
    object_properties_init(&obj->zobj, ce);
    obj->zobj.handlers = &enveloped_data_obj_handlers;

    return &obj->zobj;
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpenvelopeddata_construct, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpenvelopeddata_get_content, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpenvelopeddata_set_content, 0, 0, 1)
 ZEND_ARG_INFO(0, content)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpenvelopeddata_get_contentencoding, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpenvelopeddata_set_contentencoding, 0, 0, 1)
 ZEND_ARG_INFO(0, contentencoding)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpenvelopeddata_encrypt, 0, 0, 1)
 ZEND_ARG_INFO(0, encodingtype)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpenvelopeddata_decrypt, 0, 0, 1)
 ZEND_ARG_INFO(0, data)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpenvelopeddata_get_recipients, 0, 0, 0)
ZEND_END_ARG_INFO()

//связывание методов класса в function entry
zend_function_entry enveloped_data_methods[] = {
    PHP_ME(CPEnvelopedData, __construct, arginfo_cpenvelopeddata_construct, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
    PHP_ME(CPEnvelopedData, get_Content, arginfo_cpenvelopeddata_get_content, ZEND_ACC_PUBLIC)
    PHP_ME(CPEnvelopedData, set_Content, arginfo_cpenvelopeddata_set_content, ZEND_ACC_PUBLIC)
    PHP_ME(CPEnvelopedData, get_ContentEncoding, arginfo_cpenvelopeddata_get_contentencoding, ZEND_ACC_PUBLIC)
    PHP_ME(CPEnvelopedData, set_ContentEncoding, arginfo_cpenvelopeddata_set_contentencoding, ZEND_ACC_PUBLIC)
    PHP_ME(CPEnvelopedData, Encrypt, arginfo_cpenvelopeddata_encrypt, ZEND_ACC_PUBLIC)
    PHP_ME(CPEnvelopedData, Decrypt, arginfo_cpenvelopeddata_decrypt, ZEND_ACC_PUBLIC)
    /*PHP_ME(CPEnvelopedData, get_Algorithm, NULL, ZEND_ACC_PUBLIC)*/
    PHP_ME(CPEnvelopedData, get_Recipients, arginfo_cpenvelopeddata_get_recipients, ZEND_ACC_PUBLIC)
    {NULL, NULL, NULL}};

void enveloped_data_init(void) {
    zend_class_entry ce;
    INIT_CLASS_ENTRY(ce, "CPEnvelopedData", enveloped_data_methods);
    enveloped_data_ce = zend_register_internal_class(&ce );
    enveloped_data_ce->create_object = enveloped_data_create_handler;
    memcpy(&enveloped_data_obj_handlers, zend_get_std_object_handlers(),
           sizeof(zend_object_handlers));
    enveloped_data_obj_handlers.clone_obj = NULL;
    enveloped_data_obj_handlers.free_obj = enveloped_data_free;
    enveloped_data_obj_handlers.offset = XtOffsetOf(enveloped_data_obj, zobj);
}
