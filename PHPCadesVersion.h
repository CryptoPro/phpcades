#ifndef PHP_CP_VERSION_H_
#define PHP_CP_VERSION_H_

#include "CPPVersion.h"
#include "php.h"

//объявление структуры, которая свяжет объект оборачиваемого класса
//с объектом php
struct version_obj {
    zend_object zo;
    boost::shared_ptr<CryptoPro::PKI::CAdES::CPPVersionObject> m_pCppCadesImpl;
};

//хэндлеры для обработки объектов оборачиваемого класса
extern zend_object_handlers version_obj_handlers;

extern zend_class_entry *version_ce;

//функция освобождения памяти. используется при уничтожении объектов
void version_free_storage(void *object TSRMLS_DC);

//функция создания хэндлера для нового объекта класса. используется при
//создании новых объектов
zend_object_value version_create_handler(zend_class_entry *type TSRMLS_DC);

//функция инициализации класса. должна включаться в
//функцию, инициализации модуля
void version_init(TSRMLS_D);

#endif
