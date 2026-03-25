#ifndef PHP_SYMMETRIC_ALGORITHM_H_
#define PHP_SYMMETRIC_ALGORITHM_H_

#include "CPPCadesSymmetricAlgorithm.h"

//объявление структуры, которая свяжет объект оборачиваемого класса
//с объектом php
typedef struct _symmetric_algorithm_obj {
    NS_SHARED_PTR::shared_ptr<CryptoPro::PKI::CAdES::CPPCadesSymmetricAlgorithmObject>
        m_pCppCadesImpl;
    zend_object zobj; /* MUST be the last element */
} symmetric_algorithm_obj;

//хэндлеры для обработки объектов оборачиваемого класса
extern zend_object_handlers symmetric_algorithm_obj_handlers;
extern zend_class_entry *symmetric_algorithm_ce;

//функция освобождения памяти. используется при уничтожении объектов
// void symmetric_algorithm_free_storage(void *object );
// //функция создания хэндлера для нового объекта класса. используется при
// //создании новых объектов
// zend_object_value symmetric_algorithm_create_handler(zend_class_entry *type
//                                                          );

//функция инициализации класса. должна включаться в
//функцию, инициализации модуля
void symmetric_algorithm_init(void);
#endif
