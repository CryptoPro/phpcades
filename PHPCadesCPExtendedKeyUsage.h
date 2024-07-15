#ifndef PHP_CP_EXTENDED_KEY_USAGE_H_
#define PHP_CP_EXTENDED_KEY_USAGE_H_

#include "CPPCadesCPExtendedKeyUsage.h"

//объявление структуры, которая свяжет объект оборачиваемого класса
//с объектом php
struct exku_obj {
    zend_object zo;
    boost::shared_ptr<CryptoPro::PKI::CAdES::CPPCadesCPExtendedKeyUsageObject>
        m_pCppCadesImpl;
};

//хэндлеры для обработки объектов оборачиваемого класса
extern zend_object_handlers exku_obj_handlers;
extern zend_class_entry *exku_ce;

//функция освобождения памяти. используется при уничтожении объектов
void exku_free_storage(void *object TSRMLS_DC);

//функция создания хэндлера для нового объекта класса. используется при
//создании новых объектов
zend_object_value exku_create_handler(zend_class_entry *type TSRMLS_DC);

//функция инициализации класса. должна включаться в
//функцию, инициализации модуля
void exku_init(TSRMLS_D);
#endif
