#ifndef PHP_CP_ENCODED_DATA_H_
#define PHP_CP_ENCODED_DATA_H_

#include "CPPCadesCPEncodedData.h"

//объявление структуры, которая свяжет объект оборачиваемого класса
//с объектом php
typedef struct _encoded_data_obj {
    NS_SHARED_PTR::shared_ptr<CryptoPro::PKI::CAdES::CPPCadesCPEncodedDataObject>
        m_pCppCadesImpl;
    zend_object zobj; /* MUST be the last element */
} encoded_data_obj;

//хэндлеры для обработки объектов оборачиваемого класса
extern zend_object_handlers encoded_data_obj_handlers;
extern zend_class_entry *encoded_data_ce;

//функция освобождения памяти. используется при уничтожении объектов
// void encoded_data_free_storage(void *object );
// //функция создания хэндлера для нового объекта класса. используется при
// //создании новых объектов
// zend_object_value encoded_data_create_handler(zend_class_entry *type );

//функция инициализации класса. должна включаться в
//функцию, инициализации модуля
void encoded_data_init(void);
#endif
