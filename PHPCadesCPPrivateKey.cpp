#include "stdafx.h"
#include "PHPCadesCPPrivateKey.h"
#include "PHPCadesCPCardholderData.h"
using namespace CryptoPro::PKI::CAdES;

PHP_METHOD(CPPrivateKey, __construct) {
    zend_object *zobj = Z_OBJ_P(getThis());
    private_key_obj *obj =
        (private_key_obj *)((char *)zobj - XtOffsetOf(private_key_obj, zobj));
    obj->m_pCppCadesImpl = NS_SHARED_PTR::shared_ptr<CPPCadesCPPrivateKeyObject>(
        new CPPCadesCPPrivateKeyObject());
}

PHP_METHOD(CPPrivateKey, get_ContainerName) {
    CAtlString atlstr;

    zend_object *zobj = Z_OBJ_P(getThis());
    private_key_obj *obj =
        (private_key_obj *)((char *)zobj - XtOffsetOf(private_key_obj, zobj));

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_ContainerName(atlstr));

    RETURN_ATL_STRING(atlstr);
}

PHP_METHOD(CPPrivateKey, get_UniqueContainerName) {
    CAtlString atlstr;

    zend_object *zobj = Z_OBJ_P(getThis());
    private_key_obj *obj =
        (private_key_obj *)((char *)zobj - XtOffsetOf(private_key_obj, zobj));

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_UniqueContainerName(atlstr));

    RETURN_ATL_STRING(atlstr);
}

PHP_METHOD(CPPrivateKey, get_ProviderName) {
    CAtlString atlstr;

    zend_object *zobj = Z_OBJ_P(getThis());
    private_key_obj *obj =
        (private_key_obj *)((char *)zobj - XtOffsetOf(private_key_obj, zobj));

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_ProviderName(atlstr));

    RETURN_ATL_STRING(atlstr);
}

PHP_METHOD(CPPrivateKey, get_ProviderType) {
    CAPICOM_PROV_TYPE type;

    zend_object *zobj = Z_OBJ_P(getThis());
    private_key_obj *obj =
        (private_key_obj *)((char *)zobj - XtOffsetOf(private_key_obj, zobj));

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_ProviderType(&type));

    RETURN_LONG(type);
}

PHP_METHOD(CPPrivateKey, get_KeySpec) {
    CAPICOM_KEY_SPEC spec;

    zend_object *zobj = Z_OBJ_P(getThis());
    private_key_obj *obj =
        (private_key_obj *)((char *)zobj - XtOffsetOf(private_key_obj, zobj));

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_KeySpec(&spec));

    RETURN_LONG(spec);
}

PHP_METHOD(CPPrivateKey, set_KeyPin) {
    char *str;
    size_t len;

    if (zend_parse_parameters(ZEND_NUM_ARGS() , "s", &str, &len) ==
        FAILURE)
        RETURN_WITH_EXCEPTION(E_INVALIDARG);

    zend_object *zobj = Z_OBJ_P(getThis());
    private_key_obj *obj =
        (private_key_obj *)((char *)zobj - XtOffsetOf(private_key_obj, zobj));
    CAtlStringA pin(CA2CA(CAtlStringA(str), CP_UTF8));
    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->set_KeyPin(pin));
}

zend_object_handlers private_key_obj_handlers;
zend_class_entry *private_key_ce;

static void private_key_free(zend_object *object) {
    private_key_obj *obj = (private_key_obj *)((char *)object - XtOffsetOf(private_key_obj, zobj));
    obj->m_pCppCadesImpl.reset();

    zend_object_std_dtor(object);
}

static zend_object* private_key_create_handler(zend_class_entry *ce) {
    private_key_obj *obj = (private_key_obj *)emalloc(sizeof(private_key_obj) + zend_object_properties_size(ce));
    memset(obj, 0, sizeof(private_key_obj) + zend_object_properties_size(ce));
    
    zend_object_std_init(&obj->zobj, ce);
    object_properties_init(&obj->zobj, ce);
    obj->zobj.handlers = &private_key_obj_handlers;

    return &obj->zobj;
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpprivatekey_construct, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpprivatekey_get_containername, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpprivatekey_get_uniquecontainername, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpprivatekey_get_providername, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpprivatekey_get_providertype, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpprivatekey_get_keyspec, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpprivatekey_set_keypin, 0, 0, 0)
ZEND_END_ARG_INFO()

//связывание методов класса в function entry
zend_function_entry private_key_methods[] = {
    PHP_ME(CPPrivateKey, __construct, arginfo_cpprivatekey_construct, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
    PHP_ME(CPPrivateKey, get_ContainerName, arginfo_cpprivatekey_get_containername, ZEND_ACC_PUBLIC)
    PHP_ME(CPPrivateKey, get_UniqueContainerName, arginfo_cpprivatekey_get_uniquecontainername, ZEND_ACC_PUBLIC)
    PHP_ME(CPPrivateKey, get_ProviderName, arginfo_cpprivatekey_get_providername, ZEND_ACC_PUBLIC)
    PHP_ME(CPPrivateKey, get_ProviderType, arginfo_cpprivatekey_get_providertype, ZEND_ACC_PUBLIC)
    PHP_ME(CPPrivateKey, get_KeySpec, arginfo_cpprivatekey_get_keyspec, ZEND_ACC_PUBLIC)
    PHP_ME(CPPrivateKey, set_KeyPin, arginfo_cpprivatekey_set_keypin, ZEND_ACC_PUBLIC)
    // PHP_ME(CPPrivateKey, get_UECardholderData,    NULL, ZEND_ACC_PUBLIC)
    // PHP_ME(CPPrivateKey, get_UECardWelcomeText,   NULL, ZEND_ACC_PUBLIC)
    {NULL, NULL, NULL}};

void private_key_init(void) {
    zend_class_entry ce;
    INIT_CLASS_ENTRY(ce, "CPPrivateKey", private_key_methods);
    private_key_ce = zend_register_internal_class(&ce );
    private_key_ce->create_object = private_key_create_handler;
    memcpy(&private_key_obj_handlers, zend_get_std_object_handlers(),
           sizeof(zend_object_handlers));
    private_key_obj_handlers.clone_obj = NULL;
    private_key_obj_handlers.free_obj = private_key_free;
    private_key_obj_handlers.offset = XtOffsetOf(private_key_obj, zobj);
}
