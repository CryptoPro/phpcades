#ifndef PHP_RECIPIENTS_H
#define PHP_RECIPIENTS_H

#include "CPPCadesCollections.h"

//объявление структуры, которая свяжет объект оборачиваемого класса
//с объектом php
struct recipients_obj {
    zend_object zo;
    NS_SHARED_PTR::shared_ptr<CryptoPro::PKI::CAdES::CPPCadesCPRecipientsObject>
        m_pCppCadesImpl;
};

//хэндлеры для обработки объектов оборачиваемого класса
extern zend_class_entry *recipients_class_entry;
extern zend_object_handlers recipients_handlers;

void recipients_free_storage(void *object TSRMLS_DC);
zend_object_value recipients_create_handler(zend_class_entry *type TSRMLS_DC);

//функция инициализации класса. должна включаться в
//функцию, инициализации модуля
void recipients_init(TSRMLS_D);
#endif
