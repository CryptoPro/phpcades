#ifndef PHP_HASHED_DATA_H
#define PHP_HASHED_DATA_H

#include "CPPCadesCPHashedData.h"

//объявление структуры, которая свяжет объект оборачиваемого класса
//с объектом php
typedef struct hashed_data_obj {
    NS_SHARED_PTR::shared_ptr<CryptoPro::PKI::CAdES::CPPCadesCPHashedDataObject>
        m_pCppCadesImpl;
    zend_object zobj; /* MUST be the last element */
} hashed_data_obj;

//хэндлеры для обработки объектов оборачиваемого класса
extern zend_class_entry *hashed_data_ce;
extern zend_object_handlers hashed_data_obj_handlers;

// void hashed_data_free_storage(void *object );
// zend_object_value hashed_data_create_handler(zend_class_entry *type );

//функция инициализации класса. должна включаться в
//функцию, инициализации модуля
void hashed_data_init(void);

#endif
