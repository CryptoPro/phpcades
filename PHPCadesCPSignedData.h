#ifndef PHP_SIGNED_DATA_H
#define PHP_SIGNED_DATA_H

#include "CPPCadesCPSignedData.h"

//объ€вление структуры, котора€ св€жет объект оборачиваемого класса
//с объектом php
struct sig_dat_obj {
    zend_object zo;
    CryptoPro::PKI::CAdES::CPPCadesSignedDataObject *m_pCppCadesImpl;
};

//хэндлеры дл€ обработки объектов оборачиваемого класса
extern zend_class_entry *sig_dat_class_entry;
extern zend_object_handlers sig_dat_handlers;

void sig_dat_free_storage(void *object TSRMLS_DC);
zend_object_value sig_dat_create_handler(zend_class_entry *type TSRMLS_DC);

//функци€ инициализации класса. должна включатьс€ в
//функцию, инициализации модул€
void sig_dat_init(TSRMLS_D);
#endif
