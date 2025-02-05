#ifndef PHP_CP_CERTIFICATE_H_
#define PHP_CP_CERTIFICATE_H_

#include "CPPCadesCPCertificate.h"

//объявление структуры, которая свяжет объект оборачиваемого класса
//с объектом php
typedef struct _certificate_obj {
    NS_SHARED_PTR::shared_ptr<CryptoPro::PKI::CAdES::CPPCadesCPCertificateObject>
        m_pCppCadesImpl;
    zend_object zobj; /* MUST be the last element */
} certificate_obj;

extern zend_object_handlers certificate_obj_handlers;
extern zend_class_entry *cert_ce;

// zend_object* cert_create_handler(zend_class_entry *ce );
//функция инициализации класса. должна включаться в
//функцию, инициализации модуля
void cert_init(void);
#endif
