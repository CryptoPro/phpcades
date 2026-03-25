#ifndef PHP_SIGNED_DATA_H
#define PHP_SIGNED_DATA_H

#include "CPPCadesCPSignedData.h"

//объявление структуры, которая свяжет объект оборачиваемого класса
//с объектом php
typedef struct _signed_data_obj {
    CryptoPro::PKI::CAdES::CPPCadesSignedDataObject *m_pCppCadesImpl;
    zend_object zobj; /* MUST be the last element */
} signed_data_obj;

//хэндлеры для обработки объектов оборачиваемого класса
extern zend_class_entry *signed_data_ce;
extern zend_object_handlers signed_data_obj_handlers;

// void signed_data_free_storage(void *object );
// zend_object_value signed_data_create_handler(zend_class_entry *type );

//функция инициализации класса. должна включаться в
//функцию, инициализации модуля
void signed_data_init(void);
#endif
