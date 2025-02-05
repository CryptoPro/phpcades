#ifndef PHP_CP_CERTIFICATE_H_
#define PHP_CP_CERTIFICATE_H_

#include "CPPCadesCPCertificate.h"

//объявление структуры, которая свяжет объект оборачиваемого класса
//с объектом php
struct cert_obj {
    zend_object zo;
    NS_SHARED_PTR::shared_ptr<CryptoPro::PKI::CAdES::CPPCadesCPCertificateObject>
        m_pCppCadesImpl;
};

extern zend_object_handlers cert_obj_handlers;
extern zend_class_entry *cert_ce;

void cert_free_storage(void *object TSRMLS_DC);
zend_object_value cert_create_handler(zend_class_entry *type TSRMLS_DC);
//функция инициализации класса. должна включаться в
//функцию, инициализации модуля
void cert_init(TSRMLS_D);
#endif
