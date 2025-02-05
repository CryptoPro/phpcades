#include "stdafx.h"
#include "PHPCadesVersion.h"
using namespace CryptoPro::PKI::CAdES;

//Полное объявление структуры

//Методы
PHP_METHOD(Version, __construct) {

    zend_object *zobj = Z_OBJ_P(getThis());
    version_obj *obj =
        (version_obj *)((char *)zobj - XtOffsetOf(version_obj, zobj));
    obj->m_pCppCadesImpl =
        NS_SHARED_PTR::shared_ptr<CPPVersionObject>(new CPPVersionObject());
}

PHP_METHOD(Version, get_MajorVersion) {
    unsigned int version;

    zend_object *zobj = Z_OBJ_P(getThis());
    version_obj *obj =
        (version_obj *)((char *)zobj - XtOffsetOf(version_obj, zobj));
    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_MajorVersion(&version));

    RETURN_LONG(version);
}

PHP_METHOD(Version, get_MinorVersion) {
    unsigned int version;

    zend_object *zobj = Z_OBJ_P(getThis());
    version_obj *obj =
        (version_obj *)((char *)zobj - XtOffsetOf(version_obj, zobj));
    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_MinorVersion(&version));

    RETURN_LONG(version);
}

PHP_METHOD(Version, get_BuildVersion) {
    unsigned int version;

    zend_object *zobj = Z_OBJ_P(getThis());
    version_obj *obj =
        (version_obj *)((char *)zobj - XtOffsetOf(version_obj, zobj));
    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_BuildVersion(&version));

    RETURN_LONG(version);
}

PHP_METHOD(Version, toString) {
    CAtlString AtlVersion;

    zend_object *zobj = Z_OBJ_P(getThis());
    version_obj *obj =
        (version_obj *)((char *)zobj - XtOffsetOf(version_obj, zobj));
    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->toString(AtlVersion));

    RETURN_ATL_STRING(AtlVersion);
}

//Вспомогательные функции обертки
zend_object_handlers version_obj_handlers;
zend_class_entry *version_ce;

static void version_free(zend_object* object) {
    version_obj *obj = (version_obj *)((char *)object - XtOffsetOf(version_obj, zobj));
    obj->m_pCppCadesImpl.reset();

    zend_object_std_dtor(object); /* call Zend's free handler, which will free object properties */
}

static zend_object* version_create_handler(zend_class_entry *ce ) {
    version_obj *obj = (version_obj *)emalloc(sizeof(version_obj) + zend_object_properties_size(ce));
    memset(obj, 0, sizeof(version_obj) + zend_object_properties_size(ce));
    
    zend_object_std_init(&obj->zobj, ce); /* take care of the zend_object also ! */
    object_properties_init(&obj->zobj, ce);
    obj->zobj.handlers = &version_obj_handlers;

    return &obj->zobj;
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_version_construct, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_version_get_majorversion, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_version_get_minorversion, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_version_get_buildversion, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_version_tostring, 0, 0, 0)
ZEND_END_ARG_INFO()

//связывание методов класса в function entry
zend_function_entry version_methods[] = {
    PHP_ME(Version, __construct, arginfo_version_construct, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
    PHP_ME(Version, get_MajorVersion, arginfo_version_get_majorversion, ZEND_ACC_PUBLIC)
    PHP_ME(Version, get_MinorVersion, arginfo_version_get_minorversion, ZEND_ACC_PUBLIC)
    PHP_ME(Version, get_BuildVersion, arginfo_version_get_buildversion, ZEND_ACC_PUBLIC)
    PHP_ME(Version, toString, arginfo_version_tostring, ZEND_ACC_PUBLIC)
    {NULL, NULL, NULL}};

void version_init(void) {
    zend_class_entry ce;
    INIT_CLASS_ENTRY(ce, "Version", version_methods);
    version_ce = zend_register_internal_class(&ce );
    version_ce->create_object = version_create_handler;
    memcpy(&version_obj_handlers, zend_get_std_object_handlers(),
           sizeof(zend_object_handlers));
    version_obj_handlers.clone_obj = NULL;
    version_obj_handlers.free_obj = version_free;
    version_obj_handlers.offset = XtOffsetOf(version_obj, zobj); /* Here, we declare the offset to the engine */
}
