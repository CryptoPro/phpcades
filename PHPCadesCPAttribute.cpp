#include "stdafx.h"
#include "PHPCadesCPAttribute.h"
#include "PHPCadesCPOID.h"
using namespace CryptoPro::PKI::CAdES;

//Методы
PHP_METHOD(CPAttribute, __construct) {
    attr_obj *obj =
        (attr_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);
    NS_SHARED_PTR::shared_ptr<CPPCadesCPAttributeObject> ptr(
        new CPPCadesCPAttributeObject());
    obj->m_pCppCadesImpl = ptr;
}

PHP_METHOD(CPAttribute, set_OID) {
    char *str;
    int len;

    attr_obj *obj =
        (attr_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &str, &len) ==
        FAILURE)
        RETURN_WITH_EXCEPTION(E_INVALIDARG);
    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->put_OID(CAtlStringA(str)));
}

PHP_METHOD(CPAttribute, get_OID) {
    attr_obj *obj =
        (attr_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);

    object_init_ex(return_value, oid_ce);
    oid_obj *oobj =
        (oid_obj *)zend_object_store_get_object(return_value TSRMLS_CC);
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
    unsigned int len;

    attr_obj *obj =
        (attr_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &str, &len) ==
        FAILURE)
        RETURN_WITH_EXCEPTION(E_INVALIDARG);
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
    char *tstr;
    DWORD len;
    CADESCOM_ATTRIBUTE Name;

    attr_obj *obj =
        (attr_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);
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
        tstr = const_cast<char *>(prstr.c_str());
        RETURN_STRING(tstr, 1)
    }
    RETURN_STRINGL(reinterpret_cast<char *>(str), len, 0)
}

PHP_METHOD(CPAttribute, set_Name) {
    long lname;
    CADESCOM_ATTRIBUTE name;
    attr_obj *obj =
        (attr_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &lname) ==
        FAILURE)
        RETURN_WITH_EXCEPTION(E_INVALIDARG);

    name = (CADESCOM_ATTRIBUTE)lname;

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->put_Name(name));
}

PHP_METHOD(CPAttribute, get_Name) {
    CADESCOM_ATTRIBUTE name;
    attr_obj *obj =
        (attr_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_Name(&name));

    RETURN_LONG(name)
}

PHP_METHOD(CPAttribute, set_ValueEncoding) {
    long lType;
    CAPICOM_ENCODING_TYPE Type;
    attr_obj *obj =
        (attr_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &lType) ==
        FAILURE)
        RETURN_WITH_EXCEPTION(E_INVALIDARG);

    Type = (CAPICOM_ENCODING_TYPE)lType;

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->put_ValueEncoding(Type));
}

PHP_METHOD(CPAttribute, get_ValueEncoding) {
    CAPICOM_ENCODING_TYPE type;
    attr_obj *obj =
        (attr_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_ValueEncoding(&type));

    RETURN_LONG(type)
}

//Вспомогательные функции обертки
zend_object_handlers attr_obj_handlers;
zend_class_entry *attr_ce;

void attr_free_storage(void *object TSRMLS_DC) {
    attr_obj *obj = (attr_obj *)object;
    obj->m_pCppCadesImpl.reset();

    zend_hash_destroy(obj->zo.properties);
    FREE_HASHTABLE(obj->zo.properties);

    efree(obj);
}

zend_object_value attr_create_handler(zend_class_entry *type TSRMLS_DC) {
    zend_object_value retval;

    attr_obj *obj = (attr_obj *)emalloc(sizeof(attr_obj));
    memset(obj, 0, sizeof(attr_obj));
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
        zend_objects_store_put(obj, NULL, attr_free_storage, NULL TSRMLS_CC);
    retval.handlers = &attr_obj_handlers;

    return retval;
}

//связывание методов класса в function entry
zend_function_entry attr_methods[] = {
    PHP_ME(CPAttribute, __construct, NULL, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
    PHP_ME(CPAttribute, set_OID, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(CPAttribute, get_OID, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(CPAttribute, set_Value, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(CPAttribute, get_Value, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(CPAttribute, set_Name, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(CPAttribute, get_Name, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(CPAttribute, set_ValueEncoding, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(CPAttribute, get_ValueEncoding, NULL, ZEND_ACC_PUBLIC){NULL, NULL,
                                                                  NULL}};

void attr_init(TSRMLS_D) {
    zend_class_entry ce;
    INIT_CLASS_ENTRY(ce, "CPAttribute", attr_methods);
    attr_ce = zend_register_internal_class(&ce TSRMLS_CC);
    attr_ce->create_object = attr_create_handler;
    memcpy(&attr_obj_handlers, zend_get_std_object_handlers(),
           sizeof(zend_object_handlers));
    attr_obj_handlers.clone_obj = NULL;
}
