#ifndef PHP_CP_EXTENDED_KEY_USAGE_H_
#define PHP_CP_EXTENDED_KEY_USAGE_H_

#include "CPPCadesCPExtendedKeyUsage.h"

//объявление структуры, которая свяжет объект оборачиваемого класса
//с объектом php
typedef struct _exku_obj {
    NS_SHARED_PTR::shared_ptr<CryptoPro::PKI::CAdES::CPPCadesCPExtendedKeyUsageObject>
        m_pCppCadesImpl;
    zend_object zobj; /* MUST be the last element */
} exku_obj;

//хэндлеры для обработки объектов оборачиваемого класса
extern zend_object_handlers exku_obj_handlers;
extern zend_class_entry *exku_ce;

//функция освобождения памяти. используется при уничтожении объектов
// void exku_free_storage(void *object );

//функция создания хэндлера для нового объекта класса. используется при
//создании новых объектов
// zend_object_value exku_create_handler(zend_class_entry *type );

//функция инициализации класса. должна включаться в
//функцию, инициализации модуля
void exku_init(void);
#endif
