#ifndef PHP_SIGNERS_H
#define PHP_SIGNERS_H

#include "CPPCadesCollections.h"

//объявление структуры, которая свяжет объект оборачиваемого класса
//с объектом php
typedef struct _signers_obj {
    NS_SHARED_PTR::shared_ptr<CryptoPro::PKI::CAdES::CPPCadesCPSignersObject> m_pCppCadesImpl;
    zend_object zobj; /* MUST be the last element */
} signers_obj;

//хэндлеры для обработки объектов оборачиваемого класса
extern zend_class_entry *signers_ce;
extern zend_object_handlers signers_obj_handlers;

// void signers_free_storage(void *object );
// zend_object* signers_create_handler(zend_class_entry *type );

//функция инициализации класса. должна включаться в
//функцию, инициализации модуля
void signers_init(void);

#endif
