#include "stdafx.h"
#include "PHPCadesCPEncodedData.h"
using namespace CryptoPro::PKI::CAdES;

PHP_METHOD(CPEncodedData, __construct) {
    zend_object *zobj = Z_OBJ_P(getThis());
    encoded_data_obj *obj =
        (encoded_data_obj *)((char *)zobj - XtOffsetOf(encoded_data_obj, zobj));
    obj->m_pCppCadesImpl = NS_SHARED_PTR::shared_ptr<CPPCadesCPEncodedDataObject>(
        new CPPCadesCPEncodedDataObject());
}

PHP_METHOD(CPEncodedData, Format) {
    CAtlStringW atlstr;
    long lML;
    BOOL bML;

    zend_object *zobj = Z_OBJ_P(getThis());
    encoded_data_obj *obj =
        (encoded_data_obj *)((char *)zobj - XtOffsetOf(encoded_data_obj, zobj));

    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &lML) == FAILURE)
        RETURN_WITH_EXCEPTION(E_INVALIDARG);

    bML = (BOOL)lML;

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->Format(bML, atlstr));

    RETURN_ATL_STRING_W(atlstr);
}

PHP_METHOD(CPEncodedData, get_Value) {
    long lType;
    CAPICOM_ENCODING_TYPE Type;
    CryptoPro::CBlob data;
    char *str;
    unsigned int len;

    zend_object *zobj = Z_OBJ_P(getThis());
    encoded_data_obj *obj =
        (encoded_data_obj *)((char *)zobj - XtOffsetOf(encoded_data_obj, zobj));

    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &lType) ==
        FAILURE)
        RETURN_WITH_EXCEPTION(E_INVALIDARG);

    Type = (CAPICOM_ENCODING_TYPE)lType;

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_Value(Type, data));

    len = data.cbData();
    str = (char *)ecalloc(len, sizeof(char));
    memcpy(str, data.pbData(), len);

    RETURN_STRINGL(str, len);
}

zend_object_handlers encoded_data_obj_handlers;
zend_class_entry *encoded_data_ce;

static void encoded_data_free(zend_object *object ) {
    encoded_data_obj *obj = (encoded_data_obj *)((char *)object - XtOffsetOf(encoded_data_obj, zobj));
    obj->m_pCppCadesImpl.reset();

    zend_object_std_dtor(object);
}

static zend_object* encoded_data_create_handler(zend_class_entry *ce ) {
    encoded_data_obj *obj = (encoded_data_obj *)emalloc(sizeof(encoded_data_obj) + zend_object_properties_size(ce));
    memset(obj, 0, sizeof(encoded_data_obj) + zend_object_properties_size(ce));
    
    zend_object_std_init(&obj->zobj, ce);
    object_properties_init(&obj->zobj, ce);
    obj->zobj.handlers = &encoded_data_obj_handlers;

    return &obj->zobj;
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpencodeddata_construct, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpencodeddata_format, 0, 0, 1)
 ZEND_ARG_INFO(0, multiline)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpencodeddata_get_value, 0, 0, 1)
 ZEND_ARG_INFO(0, type)
ZEND_END_ARG_INFO()

//связывание методов класса в function entry
zend_function_entry encoded_data_methods[] = {
    PHP_ME(CPEncodedData, __construct, arginfo_cpencodeddata_construct, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
    PHP_ME(CPEncodedData, Format, arginfo_cpencodeddata_format, ZEND_ACC_PUBLIC)
    PHP_ME(CPEncodedData, get_Value, arginfo_cpencodeddata_get_value, ZEND_ACC_PUBLIC)
    {NULL, NULL, NULL}};

void encoded_data_init(void) {
    zend_class_entry ce;
    INIT_CLASS_ENTRY(ce, "CPEncodedData", encoded_data_methods);
    encoded_data_ce = zend_register_internal_class(&ce );
    encoded_data_ce->create_object = encoded_data_create_handler;
    memcpy(&encoded_data_obj_handlers, zend_get_std_object_handlers(),
           sizeof(zend_object_handlers));
    encoded_data_obj_handlers.clone_obj = NULL;
    encoded_data_obj_handlers.free_obj = encoded_data_free;
    encoded_data_obj_handlers.offset = XtOffsetOf(encoded_data_obj, zobj);
}
