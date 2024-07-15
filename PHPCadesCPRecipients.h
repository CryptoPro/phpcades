#ifndef PHP_RECIPIENTS_H
#define PHP_RECIPIENTS_H

#include "CPPCadesCollections.h"

//объ€вление структуры, котора€ св€жет объект оборачиваемого класса
//с объектом php
struct recipients_obj {
    zend_object zo;
    boost::shared_ptr<CryptoPro::PKI::CAdES::CPPCadesCPRecipientsObject>
        m_pCppCadesImpl;
};

//хэндлеры дл€ обработки объектов оборачиваемого класса
extern zend_class_entry *recipients_class_entry;
extern zend_object_handlers recipients_handlers;

void recipients_free_storage(void *object TSRMLS_DC);
zend_object_value recipients_create_handler(zend_class_entry *type TSRMLS_DC);

//функци€ инициализации класса. должна включатьс€ в
//функцию, инициализации модул€
void recipients_init(TSRMLS_D);
#endif
