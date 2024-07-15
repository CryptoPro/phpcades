#ifndef PHP_CPC_PUBLIC_KEY_H_
#define PHP_CPC_PUBLIC_KEY_H_

#include "CPPCadesCPPublicKey.h"

//объявление структуры, которая свяжет объект оборачиваемого класса
//с объектом php
struct public_key_obj {
    zend_object zo;
    boost::shared_ptr<CryptoPro::PKI::CAdES::CPPCadesCPPublicKeyObject>
        m_pCppCadesImpl;
};

//хэндлеры для обработки объектов оборачиваемого класса
extern zend_object_handlers public_key_obj_handlers;
extern zend_class_entry *public_key_ce;

//функция освобождения памяти. используется при уничтожении объектов
void public_key_free_storage(void *object TSRMLS_DC);
//функция создания хэндлера для нового объекта класса. используется при
//создании новых объектов
zend_object_value public_key_create_handler(zend_class_entry *type TSRMLS_DC);

//функция инициализации класса. должна включаться в
//функцию, инициализации модуля
void public_key_init(TSRMLS_D);
#endif
