#ifndef PHP_SIGNERS_H
#define PHP_SIGNERS_H

#include "CPPCadesCollections.h"

//объ€вление структуры, котора€ св€жет объект оборачиваемого класса
//с объектом php
struct signers_obj {
    zend_object zo;
    boost::shared_ptr<CryptoPro::PKI::CAdES::CPPCadesCPSignersObject> m_pCppCadesImpl;
};

//хэндлеры дл€ обработки объектов оборачиваемого класса
extern zend_class_entry *signers_ce;
extern zend_object_handlers signers_obj_handlers;

void signers_free_storage(void *object TSRMLS_DC);
zend_object_value signers_create_handler(zend_class_entry *type TSRMLS_DC);

//функци€ инициализации класса. должна включатьс€ в
//функцию, инициализации модул€
void signers_init(TSRMLS_D);

#endif
