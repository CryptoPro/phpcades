#include "stdafx.h"
#include "PHPCadesCPAlgorithm.h"
using namespace CryptoPro::PKI::CAdES;

//Методы
PHP_METHOD(CPAlgorithm, __construct) {
    CPPCadesCPAlgorithmObject *algo;

    zend_object *zobj = Z_OBJ_P(getThis());
    algo_obj *obj =
        (algo_obj *)((char *)zobj - XtOffsetOf(algo_obj, zobj));
    algo = new CPPCadesCPAlgorithmObject();
    obj->m_pCppCadesImpl = algo;
}

PHP_METHOD(CPAlgorithm, get_Name) {
    CADESCOM_ENCRYPTION_ALGORITHM Name;

    zend_object *zobj = Z_OBJ_P(getThis());
    algo_obj *obj =
        (algo_obj *)((char *)zobj - XtOffsetOf(algo_obj, zobj));
    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_Name(&Name));

    RETURN_LONG(Name);
}

PHP_METHOD(CPAlgorithm, set_Name) {
    long lName;
    CADESCOM_ENCRYPTION_ALGORITHM Name;

    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &lName) ==
        FAILURE)
        RETURN_WITH_EXCEPTION(E_INVALIDARG);

    Name = (CADESCOM_ENCRYPTION_ALGORITHM)lName;

    zend_object *zobj = Z_OBJ_P(getThis());
    algo_obj *obj =
        (algo_obj *)((char *)zobj - XtOffsetOf(algo_obj, zobj));
    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->put_Name(Name));
}

PHP_METHOD(CPAlgorithm, get_KeyLength) {
    CAPICOM_ENCRYPTION_KEY_LENGTH Len;

    zend_object *zobj = Z_OBJ_P(getThis());
    algo_obj *obj =
        (algo_obj *)((char *)zobj - XtOffsetOf(algo_obj, zobj));
    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_KeyLength(&Len));

    RETURN_LONG(Len);
}

PHP_METHOD(CPAlgorithm, set_KeyLength) {
    long lLen;
    CAPICOM_ENCRYPTION_KEY_LENGTH Len;

    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &lLen) == FAILURE)
        RETURN_WITH_EXCEPTION(E_INVALIDARG);
    Len = (CAPICOM_ENCRYPTION_KEY_LENGTH)lLen;

    zend_object *zobj = Z_OBJ_P(getThis());
    algo_obj *obj =
        (algo_obj *)((char *)zobj - XtOffsetOf(algo_obj, zobj));
    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->put_KeyLength(Len));
}

//Вспомагательные функции обертки
zend_object_handlers algo_obj_handlers;
zend_class_entry *algo_ce;

static void algo_free(zend_object *object ) {
    algo_obj *obj = (algo_obj *)((char *)object - XtOffsetOf(algo_obj, zobj));
    delete(obj->m_pCppCadesImpl);

    zend_object_std_dtor(object);
}

static zend_object* algo_create_handler(zend_class_entry *ce ) {
    algo_obj *obj = (algo_obj *)emalloc(sizeof(algo_obj) + zend_object_properties_size(ce));
    memset(obj, 0, sizeof(algo_obj) + zend_object_properties_size(ce));
    
    zend_object_std_init(&obj->zobj, ce);
    object_properties_init(&obj->zobj, ce);
    obj->zobj.handlers = &algo_obj_handlers;

    return &obj->zobj;
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpalgorithm_construct, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpalgorithm_get_name, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpalgorithm_set_name, 0, 0, 1)
 ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpalgorithm_get_keylength, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cpalgorithm_set_keylength, 0, 0, 1)
 ZEND_ARG_INFO(0, keylength)
ZEND_END_ARG_INFO()

//связывание методов класса в function entry
zend_function_entry algo_methods[] = {
    PHP_ME(CPAlgorithm, __construct, arginfo_cpalgorithm_construct, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
    PHP_ME(CPAlgorithm, get_Name, arginfo_cpalgorithm_get_name, ZEND_ACC_PUBLIC)
    PHP_ME(CPAlgorithm, set_Name, arginfo_cpalgorithm_set_name, ZEND_ACC_PUBLIC)
    PHP_ME(CPAlgorithm, get_KeyLength, arginfo_cpalgorithm_get_keylength, ZEND_ACC_PUBLIC)
    PHP_ME(CPAlgorithm, set_KeyLength, arginfo_cpalgorithm_set_keylength, ZEND_ACC_PUBLIC)
    {NULL, NULL, NULL}};

void algo_init(void) {
    zend_class_entry ce;
    INIT_CLASS_ENTRY(ce, "CPAlgorithm", algo_methods);
    algo_ce = zend_register_internal_class(&ce );
    algo_ce->create_object = algo_create_handler;
    memcpy(&algo_obj_handlers, zend_get_std_object_handlers(),
           sizeof(zend_object_handlers));
    algo_obj_handlers.clone_obj = NULL;
    algo_obj_handlers.free_obj = algo_free;
    algo_obj_handlers.offset = XtOffsetOf(algo_obj, zobj);
}
