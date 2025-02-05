#ifndef PHP_SIGNERS_H
#define PHP_SIGNERS_H

#include "CPPCadesCollections.h"

//объявление структуры, которая свяжет объект оборачиваемого класса
//с объектом php
struct signers_obj {
    zend_object zo;
    NS_SHARED_PTR::shared_ptr<CryptoPro::PKI::CAdES::CPPCadesCPSignersObject> m_pCppCadesImpl;
};

//хэндлеры для обработки объектов оборачиваемого класса
extern zend_class_entry *signers_ce;
extern zend_object_handlers signers_obj_handlers;

void signers_free_storage(void *object TSRMLS_DC);
zend_object_value signers_create_handler(zend_class_entry *type TSRMLS_DC);

//функция инициализации класса. должна включаться в
//функцию, инициализации модуля
void signers_init(TSRMLS_D);

#endif
