#include "stdafx.h"
#include "PHPCadesCPAlgorithm.h"
using namespace CryptoPro::PKI::CAdES;

//Методы
PHP_METHOD(CPAlgorithm, __construct) {
    CPPCadesCPAlgorithmObject *algo;

    algo_obj *obj =
        (algo_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);
    algo = new CPPCadesCPAlgorithmObject();
    obj->m_pCppCadesImpl = algo;
}

PHP_METHOD(CPAlgorithm, get_Name) {
    CADESCOM_ENCRYPTION_ALGORITHM Name;

    algo_obj *obj =
        (algo_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);
    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_Name(&Name));

    RETURN_LONG(Name)
}

PHP_METHOD(CPAlgorithm, set_Name) {
    long lName;
    CADESCOM_ENCRYPTION_ALGORITHM Name;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &lName) ==
        FAILURE)
        RETURN_WITH_EXCEPTION(E_INVALIDARG);

    Name = (CADESCOM_ENCRYPTION_ALGORITHM)lName;

    algo_obj *obj =
        (algo_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);
    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->put_Name(Name));
}

PHP_METHOD(CPAlgorithm, get_KeyLength) {
    CAPICOM_ENCRYPTION_KEY_LENGTH Len;

    algo_obj *obj =
        (algo_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);
    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->get_KeyLength(&Len));

    RETURN_LONG(Len)
}

PHP_METHOD(CPAlgorithm, set_KeyLength) {
    long lLen;
    CAPICOM_ENCRYPTION_KEY_LENGTH Len;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &lLen) == FAILURE)
        RETURN_WITH_EXCEPTION(E_INVALIDARG);
    Len = (CAPICOM_ENCRYPTION_KEY_LENGTH)lLen;

    algo_obj *obj =
        (algo_obj *)zend_object_store_get_object(getThis() TSRMLS_CC);
    HR_ERRORCHECK_RETURN(obj->m_pCppCadesImpl->put_KeyLength(Len));
}

//Вспомагательные функции обертки
zend_object_handlers algo_obj_handlers;
zend_class_entry *algo_ce;

void algo_free_storage(void *object TSRMLS_DC) {
    algo_obj *obj = (algo_obj *)object;
    delete obj->m_pCppCadesImpl;

    zend_hash_destroy(obj->zo.properties);
    FREE_HASHTABLE(obj->zo.properties);

    efree(obj);
}

zend_object_value algo_create_handler(zend_class_entry *type TSRMLS_DC) {
    zend_object_value retval;

    algo_obj *obj = (algo_obj *)emalloc(sizeof(algo_obj));
    memset(obj, 0, sizeof(algo_obj));
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
        zend_objects_store_put(obj, NULL, algo_free_storage, NULL TSRMLS_CC);
    retval.handlers = &algo_obj_handlers;

    return retval;
}

//связывание методов класса в function entry
zend_function_entry algo_methods[] = {
    PHP_ME(CPAlgorithm, __construct, NULL, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
    PHP_ME(CPAlgorithm, get_Name, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(CPAlgorithm, set_Name, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(CPAlgorithm, get_KeyLength, NULL, ZEND_ACC_PUBLIC) PHP_ME(
        CPAlgorithm, set_KeyLength, NULL, ZEND_ACC_PUBLIC){NULL, NULL, NULL}};

void algo_init(TSRMLS_D) {
    zend_class_entry ce;
    INIT_CLASS_ENTRY(ce, "CPAlgorithm", algo_methods);
    algo_ce = zend_register_internal_class(&ce TSRMLS_CC);
    algo_ce->create_object = algo_create_handler;
    memcpy(&algo_obj_handlers, zend_get_std_object_handlers(),
           sizeof(zend_object_handlers));
    algo_obj_handlers.clone_obj = NULL;
}
