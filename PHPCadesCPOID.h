#ifndef PHP_CP_OID_H_
#define PHP_CP_OID_H_

#include "CPPCadesCPOID.h"

//объявление структуры, которая свяжет объект оборачиваемого класса
//с объектом php
typedef struct _oid_obj {
    NS_SHARED_PTR::shared_ptr<CryptoPro::PKI::CAdES::CPPCadesCPOIDObject> m_pCppCadesImpl;
    zend_object zobj; /* MUST be the last element */
} oid_obj;

//хэндлеры для обработки объектов оборачиваемого класса
extern zend_object_handlers oid_obj_handlers;
extern zend_class_entry *oid_ce;

//функция освобождения памяти. используется при уничтожении объектов
// void oid_free_storage(void *object );
// //функция создания хэндлера для нового объекта класса. используется при
// //создании новых объектов
// zend_object_value oid_create_handler(zend_class_entry *type );

//функция инициализации класса. должна включаться в
//функцию, инициализации модуля
void oid_init(void);
#endif
