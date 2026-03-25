#ifndef PHP_ABOUT_H_
#define PHP_ABOUT_H_

#include "CPPCadesAbout.h"
#include "php.h"

//объявление структуры, которая свяжет объект оборачиваемого класса
//с объектом php
typedef struct _about_obj {
    NS_SHARED_PTR::shared_ptr<CryptoPro::PKI::CAdES::CPPCadesAboutObject>
        m_pCppCadesImpl;
    zend_object zobj; /* MUST be the last element */
} about_obj;

//хэндлеры для обработки объектов оборачиваемого класса
extern zend_object_handlers about_obj_handlers;

extern zend_class_entry *about_ce;

//функция освобождения памяти. используется при уничтожении объектов
// void about_free_storage(void *object );

// //функция создания хэндлера для нового объекта класса. используется при
// //создании новых объектов
// zend_object_value about_create_handler(zend_class_entry *type );

//функция инициализации класса. должна включаться в
//функцию, инициализации модуля
void about_init(void);

#endif
