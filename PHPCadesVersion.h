#ifndef PHP_CP_VERSION_H_
#define PHP_CP_VERSION_H_

#include "CPPVersion.h"
#include "php.h"

//объявление структуры, которая свяжет объект оборачиваемого класса
//с объектом php
typedef struct _version_obj {
    NS_SHARED_PTR::shared_ptr<CryptoPro::PKI::CAdES::CPPVersionObject> m_pCppCadesImpl;
    zend_object zobj; /* MUST be the last element */
} version_obj;

//хэндлеры для обработки объектов оборачиваемого класса
extern zend_object_handlers version_obj_handlers;

extern zend_class_entry *version_ce;

// функция освобождения памяти. используется при уничтожении объектов
// void version_free_storage(void *object );

//функция создания хэндлера для нового объекта класса. используется при
//создании новых объектов
//zend_object_value version_create_handler(zend_class_entry *type );

//функция инициализации класса. должна включаться в
//функцию, инициализации модуля
void version_init(void);

#endif
