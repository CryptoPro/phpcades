#ifndef PHP_CP_CARDHOLDER_DATA_H_
#define PHP_CP_CARDHOLDER_DATA_H_

#include "CPPCadesCardholderData.h"

//объявление структуры, которая свяжет объект оборачиваемого класса
//с объектом php
struct chd_obj {
    zend_object zo;
    CryptoPro::PKI::CAdES::CPPCadesCardholderDataObject *m_pCppCadesImpl;
};

//хэндлеры для обработки объектов оборачиваемого класса
extern zend_object_handlers chd_obj_handlers;
extern zend_class_entry *chd_ce;

//функция освобождения памяти. используется при уничтожении объектов
void chd_free_storage(void *object TSRMLS_DC);
//функция создания хэндлера для нового объекта класса. используется при
//создании новых объектов
zend_object_value chd_create_handler(zend_class_entry *type TSRMLS_DC);

//функция инициализации класса. должна включаться в
//функцию, инициализации модуля
void chd_init(TSRMLS_D);
#endif
