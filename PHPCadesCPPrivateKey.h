#ifndef PHP_CP_PRIVATE_KEY_H_
#define PHP_CP_PRIVATE_KEY_H_

#include "CPPCadesCPPrivateKey.h"

//объявление структуры, которая свяжет объект оборачиваемого класса
//с объектом php
struct private_key_obj {
    zend_object zo;
    NS_SHARED_PTR::shared_ptr<CryptoPro::PKI::CAdES::CPPCadesCPPrivateKeyObject>
        m_pCppCadesImpl;
};

//хэндлеры для обработки объектов оборачиваемого класса
extern zend_object_handlers private_key_obj_handlers;
extern zend_class_entry *private_key_ce;

//функция освобождения памяти. используется при уничтожении объектов
void private_key_free_storage(void *object TSRMLS_DC);
//функция создания хэндлера для нового объекта класса. используется при
//создании новых объектов
zend_object_value private_key_create_handler(zend_class_entry *type TSRMLS_DC);

//функция инициализации класса. должна включаться в
//функцию, инициализации модуля
void private_key_init(TSRMLS_D);
#endif
