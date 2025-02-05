#ifndef PHP_CP_ALGORITHM_H_
#define PHP_CP_ALGORITHM_H_

#include "CPPCadesCPAlgorithm.h"

//объявление структуры, которая свяжет объект оборачиваемого класса
//с объектом php
typedef struct _algo_obj {
    CryptoPro::PKI::CAdES::CPPCadesCPAlgorithmObject *m_pCppCadesImpl;
    zend_object zobj; /* MUST be the last element */
} algo_obj;

//хэндлеры для обработки объектов оборачиваемого класса
extern zend_object_handlers algo_obj_handlers;
extern zend_class_entry *algo_ce;

// //функция освобождения памяти. используется при уничтожении объектов
// void algo_free_storage(void *object );

// //функция создания хэндлера для нового объекта класса. используется при
// //создании новых объектов
// zend_object_value algo_create_handler(zend_class_entry *type );

//функция инициализации класса. должна включаться в
//функцию, инициализации модуля
void algo_init(void);

#endif
