#ifndef PHPCADES_RAW_SIGNATURE
#define PHPCADES_RAW_SIGNATURE

#include "CPPCadesRawSignature.h"

//объявление структуры, которая свяжет объект оборачиваемого класса
//с объектом php
struct raw_sig_obj {
    zend_object zo;
    NS_SHARED_PTR::shared_ptr<CryptoPro::PKI::CAdES::CPPCadesRawSignatureObject>
        m_pCppCadesImpl;
};

//хэндлеры для обработки объектов оборачиваемого класса
extern zend_class_entry *raw_sig_class_entry;
extern zend_object_handlers raw_sig_handlers;

void raw_sig_free_storage(void *object TSRMLS_DC);
zend_object_value raw_sig_create_handler(zend_class_entry *type TSRMLS_DC);

//функция инициализации класса. должна включаться в
//функцию, инициализации модуля
void raw_sig_init(TSRMLS_D);

#endif
