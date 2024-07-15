#ifndef PHP_CP_ENVELOPED_DATA_H_
#define PHP_CP_ENVELOPED_DATA_H_

#include "CPPCadesCPEnvelopedData.h"

//объявление структуры, которая свяжет объект оборачиваемого класса
//с объектом php
struct enveloped_data_obj {
    zend_object zo;
    CryptoPro::PKI::CAdES::CPPCadesCPEnvelopedDataObject *m_pCppCadesImpl;
};

//хэндлеры для обработки объектов оборачиваемого класса
extern zend_object_handlers enveloped_data_obj_handlers;
extern zend_class_entry *enveloped_data_ce;

//функция освобождения памяти. используется при уничтожении объектов
void enveloped_data_free_storage(void *object TSRMLS_DC);
//функция создания хэндлера для нового объекта класса. используется при
//создании новых объектов
zend_object_value enveloped_data_create_handler(zend_class_entry *type
                                                    TSRMLS_DC);

//функция инициализации класса. должна включаться в
//функцию, инициализации модуля
void enveloped_data_init(TSRMLS_D);
#endif
