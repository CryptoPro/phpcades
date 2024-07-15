#ifndef PHP_CP_CERTIFICATE_STATUS_H_
#define PHP_CP_CERTIFICATE_STATUS_H_

#include "CPPCadesCPCertificateStatus.h"

//объявление структуры, которая свяжет объект оборачиваемого класса
//с объектом php
struct certstat_obj {
    zend_object zo;
    boost::shared_ptr<CryptoPro::PKI::CAdES::CPPCadesCPCertificateStatusObject>
        m_pCppCadesImpl;
};

//хэндлеры для обработки объектов оборачиваемого класса
extern zend_object_handlers certstat_obj_handlers;
extern zend_class_entry *certstat_ce;

//функция освобождения памяти. используется при уничтожении объектов
void certstat_free_storage(void *object TSRMLS_DC);

//функция создания хэндлера для нового объекта класса. используется при
//создании новых объектов
zend_object_value certstat_create_handler(zend_class_entry *type TSRMLS_DC);

//функция инициализации класса. должна включаться в
//функцию, инициализации модуля
void certstat_init(TSRMLS_D);
#endif
