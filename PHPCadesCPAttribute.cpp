#include "stdafx.h"
#include "PHPCadesCPAttribute.h"
#include "PHPCadesCPOID.h"
using namespace CryptoPro::PKI::CAdES;

//Методы
PHP_METHOD(CPAttribute, __construct) {
    zend_object *zobj = Z_OBJ_P(getThis());
    attribute_obj *obj =
        (attribute_obj *)((char *)zobj - XtOffsetOf(attribute_obj, zobj));
    NS_SHARED_PTR::shared_ptr<CPPCadesCPAttributeObject> ptr(
        new CPPCadesCPAttributeObject());
    obj->m_pCppCadesImpl = ptr;
}

PHP_METHOD(CPAttribute, set_OID) {
    char *str;
    int len;

    if (zend_parse_parameters(ZEND_NUM_ARGS() , "s", &str, &len) ==
        FAILURE)
        RETURN_WITH_EXCEPTION(E_INVALIDARG);

    zend_object *zobj = Z_OBJ_P(getThis());
    attribute_obj *obj =
        (attribute_obj *)((char *)zobj - XtOffsetOf(attribute_obj, zobj));

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->put_OID(CAtlStringA(str)));
}

PHP_METHOD(CPAttribute, get_OID) {
    zend_object *zobj = Z_OBJ_P(getThis());
    attribute_obj *obj =
        (attribute_obj *)((char *)zobj - XtOffsetOf(attribute_obj, zobj));

    object_init_ex(return_value, oid_ce);
    zobj = Z_OBJ_P(return_value);
    oid_obj *oobj =
        (oid_obj *)((char *)zobj - XtOffsetOf(oid_obj, zobj));
    oobj->m_pCppCadesImpl =
        NS_SHARED_PTR::shared_ptr<CPPCadesCPOIDObject>(new CPPCadesCPOIDObject());
    NS_SHARED_PTR::shared_ptr<CPPCadesCPOIDObject> ptr(new CPPCadesCPOIDObject());

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_OID(ptr));
    oobj->m_pCppCadesImpl = ptr;
}

PHP_METHOD(CPAttribute, set_Value) {
    CryptoPro::CBlob val;
    CADESCOM_ATTRIBUTE Name;
    unsigned char *str;
    size_t len;

    if (zend_parse_parameters(ZEND_NUM_ARGS() , "s", &str, &len) ==
        FAILURE)
        RETURN_WITH_EXCEPTION(E_INVALIDARG);

    zend_object *zobj = Z_OBJ_P(getThis());
    attribute_obj *obj =
        (attribute_obj *)((char *)zobj - XtOffsetOf(attribute_obj, zobj));

    val.assign(str, len);
    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_Name(&Name));

    if (Name == CADESCOM_AUTHENTICATED_ATTRIBUTE_SIGNING_TIME) {
        try {
            CryptoPro::CDateTime time((char *)str);
            HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->put_DateTimeValue(time));
        } catch (...) {
            RETURN_WITH_EXCEPTION(E_INVALIDARG);
        }
    } else {
        HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->put_Value(val));
    }
}

PHP_METHOD(CPAttribute, get_Value) {
    CryptoPro::CBlob val;
    BYTE *str;
    DWORD len;
    CADESCOM_ATTRIBUTE Name;

    zend_object *zobj = Z_OBJ_P(getThis());
    attribute_obj *obj =
        (attribute_obj *)((char *)zobj - XtOffsetOf(attribute_obj, zobj));
    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_Name(&Name));

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_Value(val));

    len = val.cbData();
    str = (BYTE *)ecalloc(len, sizeof(BYTE));
    if (Name != CADESCOM_AUTHENTICATED_ATTRIBUTE_SIGNING_TIME)
        memcpy(str, val.pbData(), len);
    else {
        FILETIME fTime;
        DWORD fTimeSize = sizeof(FILETIME);
        CryptStringToBinary(reinterpret_cast<TCHAR *>(val.pbData()), len,
                            CRYPT_STRING_BASE64, str, &len, NULL, NULL);
        CryptDecodeObject(X509_ASN_ENCODING | PKCS_7_ASN_ENCODING,
                          (LPCSTR)szOID_RSA_signingTime, str, len, 0, &fTime,
                          &fTimeSize);
        CryptoPro::CDateTime Time(fTime);
        CryptoPro::CStringProxy prstr = Time.tostring();
        zend_string *tstr = zend_string_init(const_cast<char *>(prstr.c_str()), strlen(prstr.c_str()), 0);
        RETURN_NEW_STR(tstr);
    }
    RETURN_STRINGL(reinterpret_cast<char *>(str), len);
}

PHP_METHOD(CPAttribute, set_Name) {
    long lname;
    CADESCOM_ATTRIBUTE name;

    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &lname) ==
        FAILURE)
        RETURN_WITH_EXCEPTION(E_INVALIDARG);

    zend_object *zobj = Z_OBJ_P(getThis());
    attribute_obj *obj =
        (attribute_obj *)((char *)zobj - XtOffsetOf(attribute_obj, zobj));


    name = (CADESCOM_ATTRIBUTE)lname;

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->put_Name(name));
}

PHP_METHOD(CPAttribute, get_Name) {
    CADESCOM_ATTRIBUTE name;
    zend_object *zobj = Z_OBJ_P(getThis());
    attribute_obj *obj =
        (attribute_obj *)((char *)zobj - XtOffsetOf(attribute_obj, zobj));

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_Name(&name));

    RETURN_LONG(name);
}

PHP_METHOD(CPAttribute, set_ValueEncoding) {
    long lType;
    CAPICOM_ENCODING_TYPE Type;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &lType) ==
        FAILURE)
        RETURN_WITH_EXCEPTION(E_INVALIDARG);

    Type = (CAPICOM_ENCODING_TYPE)lType;
    zend_object *zobj = Z_OBJ_P(getThis());
    attribute_obj *obj =
        (attribute_obj *)((char *)zobj - XtOffsetOf(attribute_obj, zobj));

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->put_ValueEncoding(Type));
}

PHP_METHOD(CPAttribute, get_ValueEncoding) {
    CAPICOM_ENCODING_TYPE type;
    zend_object *zobj = Z_OBJ_P(getThis());
    attribute_obj *obj =
        (attribute_obj *)((char *)zobj - XtOffsetOf(attribute_obj, zobj));

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_ValueEncoding(&type));

    RETURN_LONG(type);
}

//Вспомогательные функции обертки
zend_object_handlers attribute_obj_handlers;
zend_class_entry *attribute_ce;

static void attribute_free(zend_object *object) {
    attribute_obj *obj = (attribute_obj *)((char *)object - XtOffsetOf(attribute_obj, zobj));;
    obj->m_pCppCadesImpl.reset();

    zend_object_std_dtor(object);
}

static zend_object* attribute_create_handler(zend_class_entry *ce ) {
    attribute_obj *obj = (attribute_obj *)emalloc(sizeof(attribute_obj) + zend_object_properties_size(ce));
    memset(obj, 0, sizeof(attribute_obj) + zend_object_properties_size(ce));
    
    zend_object_std_init(&obj->zobj, ce);
    object_properties_init(&obj->zobj, ce);
    obj->zobj.handlers = &attribute_obj_handlers;

    return &obj->zobj;
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpattribute_construct, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpattribute_set_oid, 0, 0, 1)
 ZEND_ARG_INFO(0, oid)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpattribute_get_oid, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpattribute_set_value, 0, 0, 1)
 ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpattribute_get_value, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpattribute_set_name, 0, 0, 1)
 ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpattribute_get_name, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpattribute_set_valueencoding, 0, 0, 1)
 ZEND_ARG_INFO(0, valueencoding)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpattribute_get_valueencoding, 0, 0, 0)
ZEND_END_ARG_INFO()

//связывание методов класса в function entry
zend_function_entry attr_methods[] = {
    PHP_ME(CPAttribute, __construct, arginfo_cpattribute_construct, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
    PHP_ME(CPAttribute, set_OID, arginfo_cpattribute_set_oid, ZEND_ACC_PUBLIC)
    PHP_ME(CPAttribute, get_OID, arginfo_cpattribute_get_oid, ZEND_ACC_PUBLIC)
    PHP_ME(CPAttribute, set_Value, arginfo_cpattribute_set_value, ZEND_ACC_PUBLIC)
    PHP_ME(CPAttribute, get_Value, arginfo_cpattribute_get_value, ZEND_ACC_PUBLIC)
    PHP_ME(CPAttribute, set_Name, arginfo_cpattribute_set_name, ZEND_ACC_PUBLIC)
    PHP_ME(CPAttribute, get_Name, arginfo_cpattribute_get_name, ZEND_ACC_PUBLIC)
    PHP_ME(CPAttribute, set_ValueEncoding, arginfo_cpattribute_set_valueencoding, ZEND_ACC_PUBLIC)
    PHP_ME(CPAttribute, get_ValueEncoding, arginfo_cpattribute_get_valueencoding, ZEND_ACC_PUBLIC)
    {NULL, NULL, NULL}};

void attr_init(void) {
    zend_class_entry ce;
    INIT_CLASS_ENTRY(ce, "CPAttribute", attr_methods);
    attribute_ce = zend_register_internal_class(&ce );
    attribute_ce->create_object = attribute_create_handler;
    memcpy(&attribute_obj_handlers, zend_get_std_object_handlers(),
           sizeof(zend_object_handlers));
    attribute_obj_handlers.clone_obj = NULL;
    attribute_obj_handlers.free_obj = attribute_free;
    attribute_obj_handlers.offset = XtOffsetOf(attribute_obj, zobj);
}
