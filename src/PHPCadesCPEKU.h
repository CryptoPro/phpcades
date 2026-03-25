#ifndef PHP_CP_EKU_H_
#define PHP_CP_EKU_H_

#include "CPPCadesCPEKU.h"

//объявление структуры, которая свяжет объект оборачиваемого класса
//с объектом php
typedef struct _eku_obj {
    NS_SHARED_PTR::shared_ptr<CryptoPro::PKI::CAdES::CPPCadesCPEKUObject> m_pCppCadesImpl;
    zend_object zobj; /* MUST be the last element */
} eku_obj;

//хэндлеры для обработки объектов оборачиваемого класса
extern zend_object_handlers eku_obj_handlers;
extern zend_class_entry *eku_ce;

// void eku_free_storage(void *object );
// zend_object_value item_create_handler(zend_class_entry *type );

//функция инициализации класса. должна включаться в
//функцию, инициализации модуля
void eku_init(void);

#endif
