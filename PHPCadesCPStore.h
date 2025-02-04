#ifndef PHP_CP_STORE_H_
#define PHP_CP_STORE_H_
#include "CPPCadesCPStore.h"

//объявление структуры, которая свяжет объект оборачиваемого класса
//с объектом php
struct store_obj {
    zend_object zo;
    NS_SHARED_PTR::shared_ptr<CryptoPro::PKI::CAdES::CPPCadesCPStoreObject>
        m_pCppCadesImpl;
};

//хэндлеры для обработки объектов оборачиваемого класса
extern zend_object_handlers store_obj_handlers;
extern zend_class_entry *store_ce;

//функция освобождения памяти. используется при уничтожении объектов
void store_free_storage(void *object TSRMLS_DC);

//функция создания хэндлера для нового объекта класса. используется при
//создании новых объектов
zend_object_value store_create_handler(zend_class_entry *type TSRMLS_DC);

//функция инициализации класса. должна включаться в
//функцию, инициализации модуля
void store_init(TSRMLS_D);

#endif
