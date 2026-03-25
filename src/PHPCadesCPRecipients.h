#ifndef PHP_RECIPIENTS_H
#define PHP_RECIPIENTS_H

#include "CPPCadesCollections.h"

//объявление структуры, которая свяжет объект оборачиваемого класса
//с объектом php
typedef struct _recipients_obj {
    NS_SHARED_PTR::shared_ptr<CryptoPro::PKI::CAdES::CPPCadesCPRecipientsObject>
        m_pCppCadesImpl;
    zend_object zobj; /* MUST be the last element */
} recipients_obj;

//хэндлеры для обработки объектов оборачиваемого класса
extern zend_class_entry *recipients_ce;
extern zend_object_handlers recipients_obj_handlers;

// void recipients_free_storage(void *object );
// zend_object_value recipients_create_handler(zend_class_entry *type );

//функция инициализации класса. должна включаться в
//функцию, инициализации модуля
void recipients_init(void);
#endif
