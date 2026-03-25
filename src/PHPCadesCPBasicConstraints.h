#ifndef PHP_CP_BASICCONSTRAINTS_H_
#define PHP_CP_BASICCONSTRAINTS_H_

#include "CPPCadesCPBasicConstraints.h"

//объявление структуры, которая свяжет объект оборачиваемого класса
//с объектом php
typedef struct _basic_constr_obj {
    NS_SHARED_PTR::shared_ptr<CryptoPro::PKI::CAdES::CPPCadesCPBasicConstraintsObject>
        m_pCppCadesImpl;
    zend_object zobj; /* MUST be the last element */
} basic_constr_obj;

//хэндлеры для обработки объектов оборачиваемого класса
extern zend_object_handlers basic_constr_obj_handlers;
extern zend_class_entry *basic_constr_ce;

//функция освобождения памяти. используется при уничтожении объектов
// void basic_constr_free_storage(void *object );
// //функция создания хэндлера для нового объекта класса. используется при
// //создании новых объектов
// zend_object_value basic_constr_create_handler(zend_class_entry *type );

//функция инициализации класса. должна включаться в
//функцию, инициализации модуля
void basic_constr_init(void);
#endif
