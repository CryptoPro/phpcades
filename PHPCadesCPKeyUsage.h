#ifndef PHP_CP_KEY_USAGE_H_
#define PHP_CP_KEY_USAGE_H_

#include "CPPCadesCPKeyUsage.h"

//объявление структуры, которая свяжет объект оборачиваемого класса
//с объектом php
struct ku_obj {
    zend_object zo;
    boost::shared_ptr<CryptoPro::PKI::CAdES::CPPCadesCPKeyUsageObject> m_pCppCadesImpl;
};

//хэндлеры для обработки объектов оборачиваемого класса
extern zend_object_handlers ku_obj_handlers;
extern zend_class_entry *ku_ce;

//функция освобождения памяти. используется при уничтожении объектов
void ku_free_storage(void *object TSRMLS_DC);

//функция создания хэндлера для нового объекта класса. используется при
//создании новых объектов
zend_object_value ku_create_handler(zend_class_entry *type TSRMLS_DC);

//функция инициализации класса. должна включаться в
//функцию, инициализации модуля
void ku_init(TSRMLS_D);
#endif
