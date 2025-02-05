#include "stdafx.h"
#include "PHPCadesCPBasicConstraints.h"
using namespace CryptoPro::PKI::CAdES;

PHP_METHOD(CPBasicConstraints, __construct) {
    zend_object *zobj = Z_OBJ_P(getThis());
    basic_constr_obj *obj =
        (basic_constr_obj *)((char *)zobj - XtOffsetOf(basic_constr_obj, zobj));
    obj->m_pCppCadesImpl = NS_SHARED_PTR::shared_ptr<CPPCadesCPBasicConstraintsObject>(
        new CPPCadesCPBasicConstraintsObject());
}

PHP_METHOD(CPBasicConstraints, set_IsPresent) {
    long lpr;
    BOOL pr;
    zend_object *zobj = Z_OBJ_P(getThis());
    basic_constr_obj *obj =
        (basic_constr_obj *)((char *)zobj - XtOffsetOf(basic_constr_obj, zobj));

    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &lpr) == FAILURE)
        RETURN_WITH_EXCEPTION(E_INVALIDARG);

    pr = (BOOL)lpr;

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->put_IsPresent(pr));
}

PHP_METHOD(CPBasicConstraints, get_IsPresent) {
    BOOL pr;
    zend_object *zobj = Z_OBJ_P(getThis());
    basic_constr_obj *obj =
        (basic_constr_obj *)((char *)zobj - XtOffsetOf(basic_constr_obj, zobj));

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_IsPresent(&pr));

    RETURN_LONG(pr);
}

PHP_METHOD(CPBasicConstraints, set_IsCritical) {
    long lcr;
    BOOL cr;
    zend_object *zobj = Z_OBJ_P(getThis());
    basic_constr_obj *obj =
        (basic_constr_obj *)((char *)zobj - XtOffsetOf(basic_constr_obj, zobj));

    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &lcr) == FAILURE)
        RETURN_WITH_EXCEPTION(E_INVALIDARG);

    cr = (BOOL)lcr;

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->put_IsCritical(cr));
}

PHP_METHOD(CPBasicConstraints, get_IsCritical) {
    BOOL cr;
    zend_object *zobj = Z_OBJ_P(getThis());
    basic_constr_obj *obj =
        (basic_constr_obj *)((char *)zobj - XtOffsetOf(basic_constr_obj, zobj));

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_IsCritical(&cr));

    RETURN_LONG(cr);
}

PHP_METHOD(CPBasicConstraints, get_IsCertificateAuthority) {
    BOOL ca;
    zend_object *zobj = Z_OBJ_P(getThis());
    basic_constr_obj *obj =
        (basic_constr_obj *)((char *)zobj - XtOffsetOf(basic_constr_obj, zobj));

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_IsCertificateAuthority(&ca));

    RETURN_LONG(ca);
}

PHP_METHOD(CPBasicConstraints, get_IsPathLenConstraintPresent) {
    BOOL plcp;
    zend_object *zobj = Z_OBJ_P(getThis());
    basic_constr_obj *obj =
        (basic_constr_obj *)((char *)zobj - XtOffsetOf(basic_constr_obj, zobj));

    HR_ERRORCHECK_RETURN(
        obj->m_pCppCadesImpl->get_IsPathLenConstraintPresent(&plcp));

    RETURN_LONG(plcp);
}

PHP_METHOD(CPBasicConstraints, get_PathLenConstraint) {
    DWORD plc;
    zend_object *zobj = Z_OBJ_P(getThis());
    basic_constr_obj *obj =
        (basic_constr_obj *)((char *)zobj - XtOffsetOf(basic_constr_obj, zobj));

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_PathLenConstraint(&plc));

    RETURN_LONG(plc);
}

//Вспомогательные функции обертки
zend_object_handlers basic_constr_obj_handlers;
zend_class_entry *basic_constr_ce;

static void basic_constr_free(zend_object *object) {
    basic_constr_obj *obj = (basic_constr_obj *)((char *)object - XtOffsetOf(basic_constr_obj, zobj));
    obj->m_pCppCadesImpl.reset();

    zend_object_std_dtor(object);
}

static zend_object* basic_constr_create_handler(zend_class_entry *ce) {
    basic_constr_obj *obj = (basic_constr_obj *)emalloc(sizeof(basic_constr_obj) + zend_object_properties_size(ce));
    memset(obj, 0, sizeof(basic_constr_obj) + zend_object_properties_size(ce));
    
    zend_object_std_init(&obj->zobj, ce);
    object_properties_init(&obj->zobj, ce);
    obj->zobj.handlers = &basic_constr_obj_handlers;

    return &obj->zobj;
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpbasicconstraints_construct, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpbasicconstraints_set_ispresent, 0, 0, 1)
 ZEND_ARG_INFO(0, ispresent)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpbasicconstraints_get_ispresent, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpbasicconstraints_set_iscritical, 0, 0, 1)
 ZEND_ARG_INFO(0, iscritical)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpbasicconstraints_get_iscritical, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpbasicconstraints_get_iscertificateauthority, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpbasicconstraints_get_ispathlenconstraintpresent, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpbasicconstraints_get_pathlenconstraint, 0, 0, 0)
ZEND_END_ARG_INFO()

//связывание методов класса в function entry
zend_function_entry basic_constr_methods[] = {
    PHP_ME(CPBasicConstraints, __construct, arginfo_cpbasicconstraints_construct, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
    PHP_ME(CPBasicConstraints, set_IsPresent, arginfo_cpbasicconstraints_set_ispresent, ZEND_ACC_PUBLIC)
    PHP_ME(CPBasicConstraints, get_IsPresent, arginfo_cpbasicconstraints_get_ispresent, ZEND_ACC_PUBLIC)
    PHP_ME(CPBasicConstraints, set_IsCritical, arginfo_cpbasicconstraints_set_iscritical, ZEND_ACC_PUBLIC)
    PHP_ME(CPBasicConstraints, get_IsCritical, arginfo_cpbasicconstraints_get_iscritical, ZEND_ACC_PUBLIC) 
    PHP_ME(CPBasicConstraints, get_IsCertificateAuthority, arginfo_cpbasicconstraints_get_iscertificateauthority, ZEND_ACC_PUBLIC)
    PHP_ME(CPBasicConstraints, get_IsPathLenConstraintPresent, arginfo_cpbasicconstraints_get_ispathlenconstraintpresent, ZEND_ACC_PUBLIC) 
    PHP_ME(CPBasicConstraints, get_PathLenConstraint, arginfo_cpbasicconstraints_get_pathlenconstraint, ZEND_ACC_PUBLIC)
    {NULL, NULL, NULL}};

void basic_constr_init(void) {
    zend_class_entry ce;
    INIT_CLASS_ENTRY(ce, "CPBasicConstraints", basic_constr_methods);
    basic_constr_ce = zend_register_internal_class(&ce );
    basic_constr_ce->create_object = basic_constr_create_handler;
    memcpy(&basic_constr_obj_handlers, zend_get_std_object_handlers(),
           sizeof(zend_object_handlers));
    basic_constr_obj_handlers.clone_obj = NULL;
    basic_constr_obj_handlers.free_obj = basic_constr_free;
    basic_constr_obj_handlers.offset = XtOffsetOf(basic_constr_obj, zobj);
}
