#ifndef PHP_CPC_PUBLIC_KEY_H_
#define PHP_CPC_PUBLIC_KEY_H_

#include "CPPCadesCPPublicKey.h"

//объявление структуры, которая свяжет объект оборачиваемого класса
//с объектом php
typedef struct _public_key_obj {
    NS_SHARED_PTR::shared_ptr<CryptoPro::PKI::CAdES::CPPCadesCPPublicKeyObject>
        m_pCppCadesImpl;
    zend_object zobj; /* MUST be the last element */
} public_key_obj;

//хэндлеры для обработки объектов оборачиваемого класса
extern zend_object_handlers public_key_obj_handlers;
extern zend_class_entry *public_key_ce;

//функция освобождения памяти. используется при уничтожении объектов
// void public_key_free_storage(void *object );
// //функция создания хэндлера для нового объекта класса. используется при
// //создании новых объектов
// zend_object_value public_key_create_handler(zend_class_entry *type );

//функция инициализации класса. должна включаться в
//функцию, инициализации модуля
void public_key_init(void);
#endif
