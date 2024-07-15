#ifndef PHP_SYMMETRIC_ALGORITHM_H_
#define PHP_SYMMETRIC_ALGORITHM_H_

#include "CPPCadesSymmetricAlgorithm.h"

//объявление структуры, которая свяжет объект оборачиваемого класса
//с объектом php
struct symmetric_algorithm_obj {
    zend_object zo;
    boost::shared_ptr<CryptoPro::PKI::CAdES::CPPCadesSymmetricAlgorithmObject>
        m_pCppCadesImpl;
};

//хэндлеры для обработки объектов оборачиваемого класса
extern zend_object_handlers symmetric_algorithm_obj_handlers;
extern zend_class_entry *symmetric_algorithm_ce;

//функция освобождения памяти. используется при уничтожении объектов
void symmetric_algorithm_free_storage(void *object TSRMLS_DC);
//функция создания хэндлера для нового объекта класса. используется при
//создании новых объектов
zend_object_value symmetric_algorithm_create_handler(zend_class_entry *type
                                                         TSRMLS_DC);

//функция инициализации класса. должна включаться в
//функцию, инициализации модуля
void symmetric_algorithm_init(TSRMLS_D);
#endif
