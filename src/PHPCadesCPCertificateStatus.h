#ifndef PHP_CP_CERTIFICATE_STATUS_H_
#define PHP_CP_CERTIFICATE_STATUS_H_

#include "CPPCadesCPCertificateStatus.h"

//объявление структуры, которая свяжет объект оборачиваемого класса
//с объектом php
typedef struct _certstat_obj {
    NS_SHARED_PTR::shared_ptr<CryptoPro::PKI::CAdES::CPPCadesCPCertificateStatusObject>
        m_pCppCadesImpl;
    zend_object zobj; /* MUST be the last element */
} certstat_obj;

//хэндлеры для обработки объектов оборачиваемого класса
extern zend_object_handlers certstat_obj_handlers;
extern zend_class_entry *certstat_ce;

// //функция освобождения памяти. используется при уничтожении объектов
// void certstat_free_storage(void *object );

// //функция создания хэндлера для нового объекта класса. используется при
// //создании новых объектов
// zend_object_value certstat_create_handler(zend_class_entry *type );

//функция инициализации класса. должна включаться в
//функцию, инициализации модуля
void certstat_init(void);
#endif
