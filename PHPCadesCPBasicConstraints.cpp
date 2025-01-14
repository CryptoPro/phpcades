#include "stdafx.h"
#include "PHPCadesCPBasicConstraints.h"
using namespace CryptoPro::PKI::CAdES;

PHP_METHOD(CPBasicConstraints, __construct) {
    basic_constr_obj *obj =
        (basic_constr_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);
    obj->m_pCppCadesImpl = NS_SHARED_PTR::shared_ptr<CPPCadesCPBasicConstraintsObject>(
        new CPPCadesCPBasicConstraintsObject());
}

PHP_METHOD(CPBasicConstraints, set_IsPresent) {
    long lpr;
    BOOL pr;
    basic_constr_obj *obj =
        (basic_constr_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &lpr) == FAILURE)
        RETURN_WITH_EXCEPTION(E_INVALIDARG);

    pr = (BOOL)lpr;

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->put_IsPresent(pr));
}

PHP_METHOD(CPBasicConstraints, get_IsPresent) {
    BOOL pr;
    basic_constr_obj *obj =
        (basic_constr_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_IsPresent(&pr));

    RETURN_LONG(pr)
}

PHP_METHOD(CPBasicConstraints, set_IsCritical) {
    long lcr;
    BOOL cr;
    basic_constr_obj *obj =
        (basic_constr_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &lcr) == FAILURE)
        RETURN_WITH_EXCEPTION(E_INVALIDARG);

    cr = (BOOL)lcr;

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->put_IsCritical(cr));
}

PHP_METHOD(CPBasicConstraints, get_IsCritical) {
    BOOL cr;
    basic_constr_obj *obj =
        (basic_constr_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_IsCritical(&cr));

    RETURN_LONG(cr)
}

PHP_METHOD(CPBasicConstraints, get_IsCertificateAuthority) {
    BOOL ca;
    basic_constr_obj *obj =
        (basic_constr_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_IsCertificateAuthority(&ca));

    RETURN_LONG(ca)
}

PHP_METHOD(CPBasicConstraints, get_IsPathLenConstraintPresent) {
    BOOL plcp;
    basic_constr_obj *obj =
        (basic_constr_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);

    HR_ERRORCHECK_RETURN(
        obj->m_pCppCadesImpl->get_IsPathLenConstraintPresent(&plcp));

    RETURN_LONG(plcp)
}

PHP_METHOD(CPBasicConstraints, get_PathLenConstraint) {
    DWORD plc;
    basic_constr_obj *obj =
        (basic_constr_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);

    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_PathLenConstraint(&plc));

    RETURN_LONG(plc)
}

//��������������� ������� �������
zend_object_handlers basic_constr_obj_handlers;
zend_class_entry *basic_constr_ce;

void basic_constr_free_storage(void *object TSRMLS_DC) {
    basic_constr_obj *obj = (basic_constr_obj *)object;
    obj->m_pCppCadesImpl.reset();

    zend_hash_destroy(obj->zo.properties);
    FREE_HASHTABLE(obj->zo.properties);

    efree(obj);
}

zend_object_value basic_constr_create_handler(zend_class_entry *type
                                                  TSRMLS_DC) {
    zend_object_value retval;

    basic_constr_obj *obj =
        (basic_constr_obj *)emalloc(sizeof(basic_constr_obj));
    memset(obj, 0, sizeof(basic_constr_obj));
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

    retval.handle = zend_objects_store_put(obj, NULL, basic_constr_free_storage,
                                           NULL TSRMLS_CC);
    retval.handlers = &basic_constr_obj_handlers;

    return retval;
}

//���������� ������� ������ � function entry
zend_function_entry basic_constr_methods[] = {
    PHP_ME(CPBasicConstraints, __construct, NULL,
           ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
    PHP_ME(CPBasicConstraints, set_IsPresent, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(CPBasicConstraints, get_IsPresent, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(CPBasicConstraints, set_IsCritical, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(CPBasicConstraints, get_IsCritical, NULL, ZEND_ACC_PUBLIC) PHP_ME(
        CPBasicConstraints, get_IsCertificateAuthority, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(CPBasicConstraints, get_IsPathLenConstraintPresent, NULL,
           ZEND_ACC_PUBLIC) PHP_ME(CPBasicConstraints, get_PathLenConstraint,
                                   NULL, ZEND_ACC_PUBLIC){NULL, NULL, NULL}};

void basic_constr_init(TSRMLS_D) {
    zend_class_entry ce;
    INIT_CLASS_ENTRY(ce, "CPBasicConstraints", basic_constr_methods);
    basic_constr_ce = zend_register_internal_class(&ce TSRMLS_CC);
    basic_constr_ce->create_object = basic_constr_create_handler;
    memcpy(&basic_constr_obj_handlers, zend_get_std_object_handlers(),
           sizeof(zend_object_handlers));
    basic_constr_obj_handlers.clone_obj = NULL;
}
