#include "stdafx.h"
#include "PHPCadesAbout.h"
#include "PHPCadesVersion.h"
using namespace CryptoPro::PKI::CAdES;

//Полное объявление структуры

//Методы
PHP_METHOD(About, __construct) {
    zend_object *zobj = Z_OBJ_P(getThis());
    about_obj *obj =
        (about_obj *)((char *)zobj - XtOffsetOf(about_obj, zobj));
    obj->m_pCppCadesImpl =
        NS_SHARED_PTR::shared_ptr<CPPCadesAboutObject>(new CPPCadesAboutObject());
}

PHP_METHOD(About, get_MajorVersion) {
    unsigned int version;
    zend_object *zobj = Z_OBJ_P(getThis());
    about_obj *obj =
        (about_obj *)((char *)zobj - XtOffsetOf(about_obj, zobj));
    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_MajorVersion(&version));

    RETURN_LONG(version);
}

PHP_METHOD(About, get_MinorVersion) {
    unsigned int version;

    zend_object *zobj = Z_OBJ_P(getThis());
    about_obj *obj =
        (about_obj *)((char *)zobj - XtOffsetOf(about_obj, zobj));
    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_MinorVersion(&version));

    RETURN_LONG(version);
}

PHP_METHOD(About, get_BuildVersion) {
    unsigned int version;

    zend_object *zobj = Z_OBJ_P(getThis());
    about_obj *obj =
        (about_obj *)((char *)zobj - XtOffsetOf(about_obj, zobj));
    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_BuildVersion(&version));

    RETURN_LONG(version);
}

PHP_METHOD(About, get_Version) {
    CAtlString AtlVersion;

    zend_object *zobj = Z_OBJ_P(getThis());
    about_obj *obj =
        (about_obj *)((char *)zobj - XtOffsetOf(about_obj, zobj));
    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_Version(AtlVersion));

    RETURN_ATL_STRING(AtlVersion);
}

PHP_METHOD(About, PluginVersion) {

    NS_SHARED_PTR::shared_ptr<CPPVersionObject> version;

    zend_object *zobj = Z_OBJ_P(getThis());
    about_obj *obj =
        (about_obj *)((char *)zobj - XtOffsetOf(about_obj, zobj));

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_PluginVersion(version));

    object_init_ex(return_value, version_ce);
    
    zobj = Z_OBJ_P(return_value);
    version_obj *pPluginVersion =
        (version_obj *)((char *)zobj - XtOffsetOf(version_obj, zobj));
    pPluginVersion->m_pCppCadesImpl = version;
}

PHP_METHOD(About, CSPVersion) {

    NS_SHARED_PTR::shared_ptr<CPPVersionObject> version;
    char *szProvName;
    size_t szProvName_len = 0;
    DWORD dwProvType = 75;

    if (zend_parse_parameters(ZEND_NUM_ARGS() , "|sl", &szProvName,
                              &szProvName_len, &dwProvType) == FAILURE)
        RETURN_WITH_EXCEPTION(E_INVALIDARG);

    CAtlString provName =
        CAtlString(CA2CT(CAtlStringA(szProvName, szProvName_len), CP_UTF8));

    zend_object *zobj = Z_OBJ_P(getThis());
    about_obj *obj =
        (about_obj *)((char *)zobj - XtOffsetOf(about_obj, zobj));

    HR_ERRORCHECK_RETURN(
        obj->m_pCppCadesImpl->get_CSPVersion(provName, dwProvType, version));

    object_init_ex(return_value, version_ce);
    zobj = Z_OBJ_P(return_value);
    version_obj *pCSPVersion =
        (version_obj *)((char *)zobj - XtOffsetOf(version_obj, zobj));
    pCSPVersion->m_pCppCadesImpl = version;
}

//Вспомогательные функции обертки
zend_object_handlers about_obj_handlers;
zend_class_entry *about_ce;

static void about_free(zend_object *object ) {
    about_obj *obj = (about_obj *)((char *)object - XtOffsetOf(about_obj, zobj));
    obj->m_pCppCadesImpl.reset();

    zend_object_std_dtor(object);
}

static zend_object* about_create_handler(zend_class_entry *ce ) {
    about_obj *obj = (about_obj *)emalloc(sizeof(about_obj) + zend_object_properties_size(ce));
    memset(obj, 0, sizeof(about_obj) + zend_object_properties_size(ce));
    
    zend_object_std_init(&obj->zobj, ce);
    object_properties_init(&obj->zobj, ce);
    obj->zobj.handlers = &about_obj_handlers;

    return &obj->zobj;
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_about_construct, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_about_get_majorversion, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_about_get_minorversion, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_about_get_buildversion, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_about_get_version, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_about_cspversion, 0, 0, 0)
 ZEND_ARG_INFO(0, provname)
 ZEND_ARG_INFO(0, provtype)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_about_pluginversion, 0, 0, 0)
ZEND_END_ARG_INFO()

//связывание методов класса в function entry
zend_function_entry about_methods[] = {
    PHP_ME(About, __construct, arginfo_about_construct, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
    PHP_ME(About, get_MajorVersion, arginfo_about_get_majorversion, ZEND_ACC_PUBLIC)
    PHP_ME(About, get_MinorVersion, arginfo_about_get_minorversion, ZEND_ACC_PUBLIC)
    PHP_ME(About, get_BuildVersion, arginfo_about_get_buildversion, ZEND_ACC_PUBLIC)
    PHP_ME(About, get_Version, arginfo_about_get_version, ZEND_ACC_PUBLIC)
    PHP_ME(About, CSPVersion, arginfo_about_cspversion, ZEND_ACC_PUBLIC)
    PHP_ME(About, PluginVersion, arginfo_about_pluginversion, ZEND_ACC_PUBLIC)
    {NULL, NULL, NULL}};

void about_init(void) {
    zend_class_entry ce;
    INIT_CLASS_ENTRY(ce, "About", about_methods);
    about_ce = zend_register_internal_class(&ce );
    about_ce->create_object = about_create_handler;
    memcpy(&about_obj_handlers, zend_get_std_object_handlers(),
           sizeof(zend_object_handlers));
    about_obj_handlers.clone_obj = NULL;
    about_obj_handlers.free_obj = about_free;
    about_obj_handlers.offset = XtOffsetOf(about_obj, zobj);
}
