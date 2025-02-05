#include "stdafx.h"
#include "PHPCadesCPCardholderData.h"
using namespace CryptoPro::PKI::CAdES;

PHP_METHOD(CPCardholderData, __construct) {
    CPPCadesCardholderDataObject *chd;
    zend_object *zobj = Z_OBJ_P(getThis());
    chd_obj *obj =
        (chd_obj *)((char *)zobj - XtOffsetOf(chd_obj, zobj));
    chd = new CPPCadesCardholderDataObject();
    obj->m_pCppCadesImpl = chd;
}

PHP_METHOD(CPCardholderData, get_SocialAccountNumber) {
    CAtlString atlstr;

    zend_object *zobj = Z_OBJ_P(getThis());
    chd_obj *obj =
        (chd_obj *)((char *)zobj - XtOffsetOf(chd_obj, zobj));
    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_SocialAccountNumber(atlstr));

    RETURN_ATL_STRING(atlstr);
}

PHP_METHOD(CPCardholderData, get_OMSNumber) {
    CAtlString atlstr;

    zend_object *zobj = Z_OBJ_P(getThis());
    chd_obj *obj =
        (chd_obj *)((char *)zobj - XtOffsetOf(chd_obj, zobj));
    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_OMSNumber(atlstr));

    RETURN_ATL_STRING(atlstr);
}

PHP_METHOD(CPCardholderData, get_Name) {
    CAtlString atlstr;

    zend_object *zobj = Z_OBJ_P(getThis());
    chd_obj *obj =
        (chd_obj *)((char *)zobj - XtOffsetOf(chd_obj, zobj));
    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_Name(atlstr));

    RETURN_ATL_STRING(atlstr);
}

PHP_METHOD(CPCardholderData, get_FirstName) {
    CAtlString atlstr;

    zend_object *zobj = Z_OBJ_P(getThis());
    chd_obj *obj =
        (chd_obj *)((char *)zobj - XtOffsetOf(chd_obj, zobj));
    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_FirstName(atlstr));

    RETURN_ATL_STRING(atlstr);
}

PHP_METHOD(CPCardholderData, get_LastName) {
    CAtlString atlstr;

    zend_object *zobj = Z_OBJ_P(getThis());
    chd_obj *obj =
        (chd_obj *)((char *)zobj - XtOffsetOf(chd_obj, zobj));
    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_LastName(atlstr));

    RETURN_ATL_STRING(atlstr);
}

PHP_METHOD(CPCardholderData, get_SecondName) {
    CAtlString atlstr;

    zend_object *zobj = Z_OBJ_P(getThis());
    chd_obj *obj =
        (chd_obj *)((char *)zobj - XtOffsetOf(chd_obj, zobj));
    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_SecondName(atlstr));

    RETURN_ATL_STRING(atlstr);
}

PHP_METHOD(CPCardholderData, get_CardIssuerAddress) {
    CAtlString atlstr;

    zend_object *zobj = Z_OBJ_P(getThis());
    chd_obj *obj =
        (chd_obj *)((char *)zobj - XtOffsetOf(chd_obj, zobj));
    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_CardIssuerAddress(atlstr));

    RETURN_ATL_STRING(atlstr);
}

PHP_METHOD(CPCardholderData, get_DateOfBirth) {
    CAtlString atlstr;

    zend_object *zobj = Z_OBJ_P(getThis());
    chd_obj *obj =
        (chd_obj *)((char *)zobj - XtOffsetOf(chd_obj, zobj));
    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_DateOfBirth(atlstr));

    RETURN_ATL_STRING(atlstr);
}

PHP_METHOD(CPCardholderData, get_PlaceOfBirth) {
    CAtlString atlstr;

    zend_object *zobj = Z_OBJ_P(getThis());
    chd_obj *obj =
        (chd_obj *)((char *)zobj - XtOffsetOf(chd_obj, zobj));
    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_PlaceOfBirth(atlstr));

    RETURN_ATL_STRING(atlstr);
}

PHP_METHOD(CPCardholderData, get_SexString) {
    CAtlString atlstr;

    zend_object *zobj = Z_OBJ_P(getThis());
    chd_obj *obj =
        (chd_obj *)((char *)zobj - XtOffsetOf(chd_obj, zobj));
    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_SexString(atlstr));

    RETURN_ATL_STRING(atlstr);
}

PHP_METHOD(CPCardholderData, get_Sex) {
    CADESCOM_HUMAN_SEXES sex;

    zend_object *zobj = Z_OBJ_P(getThis());
    chd_obj *obj =
        (chd_obj *)((char *)zobj - XtOffsetOf(chd_obj, zobj));
    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_Sex(&sex));

    RETURN_LONG(sex);
}

zend_object_handlers chd_obj_handlers;
zend_class_entry *chd_ce;

static void chd_free(zend_object *object ) {
    chd_obj *obj = (chd_obj *)((char *)object - XtOffsetOf(chd_obj, zobj));
    delete(obj->m_pCppCadesImpl);

    zend_object_std_dtor(object);
}

static zend_object* chd_create_handler(zend_class_entry *ce ) {
    chd_obj *obj = (chd_obj *)emalloc(sizeof(chd_obj) + zend_object_properties_size(ce));
    memset(obj, 0, sizeof(chd_obj) + zend_object_properties_size(ce));
    
    zend_object_std_init(&obj->zobj, ce);
    object_properties_init(&obj->zobj, ce);
    obj->zobj.handlers = &chd_obj_handlers;

    return &obj->zobj;
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpcardholderdata_construct, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpcardholderdata_get_socialaccountnumber, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpcardholderdata_get_omsnumber, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpcardholderdata_get_name, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpcardholderdata_get_firstname, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpcardholderdata_get_lastname, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpcardholderdata_get_secondname, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpcardholderdata_get_cardissueraddress, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpcardholderdata_get_dateofbirth, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpcardholderdata_get_placeofbirth, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpcardholderdata_get_sexstring, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpcardholderdata_get_sex, 0, 0, 0)
ZEND_END_ARG_INFO()

//связывание методов класса в function entry
zend_function_entry chd_methods[] = {
    PHP_ME(CPCardholderData, __construct, arginfo_cpcardholderdata_construct, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
    PHP_ME(CPCardholderData, get_SocialAccountNumber, arginfo_cpcardholderdata_get_socialaccountnumber, ZEND_ACC_PUBLIC)
    PHP_ME(CPCardholderData, get_OMSNumber, arginfo_cpcardholderdata_get_omsnumber, ZEND_ACC_PUBLIC)
    PHP_ME(CPCardholderData, get_Name, arginfo_cpcardholderdata_get_name, ZEND_ACC_PUBLIC)
    PHP_ME(CPCardholderData, get_FirstName, arginfo_cpcardholderdata_get_firstname, ZEND_ACC_PUBLIC)
    PHP_ME(CPCardholderData, get_LastName, arginfo_cpcardholderdata_get_lastname, ZEND_ACC_PUBLIC)
    PHP_ME(CPCardholderData, get_SecondName, arginfo_cpcardholderdata_get_secondname, ZEND_ACC_PUBLIC)
    PHP_ME(CPCardholderData, get_CardIssuerAddress, arginfo_cpcardholderdata_get_cardissueraddress, ZEND_ACC_PUBLIC)
    PHP_ME(CPCardholderData, get_DateOfBirth, arginfo_cpcardholderdata_get_dateofbirth, ZEND_ACC_PUBLIC)
    PHP_ME(CPCardholderData, get_PlaceOfBirth, arginfo_cpcardholderdata_get_placeofbirth, ZEND_ACC_PUBLIC)
    PHP_ME(CPCardholderData, get_SexString, arginfo_cpcardholderdata_get_sexstring, ZEND_ACC_PUBLIC)
    PHP_ME(CPCardholderData, get_Sex, arginfo_cpcardholderdata_get_sex, ZEND_ACC_PUBLIC)
    {NULL, NULL, NULL}};

void chd_init(void) {
    zend_class_entry ce;
    INIT_CLASS_ENTRY(ce, "CPCardholderData", chd_methods);
    chd_ce = zend_register_internal_class(&ce );
    chd_ce->create_object = chd_create_handler;
    memcpy(&chd_obj_handlers, zend_get_std_object_handlers(),
           sizeof(zend_object_handlers));
    chd_obj_handlers.clone_obj = NULL;
    chd_obj_handlers.free_obj = chd_free;
    chd_obj_handlers.offset = XtOffsetOf(chd_obj, zobj);
}
