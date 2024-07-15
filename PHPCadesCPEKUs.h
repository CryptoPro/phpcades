#ifndef PHP_CP_EKUS_H_
#define PHP_CP_EKUS_H_

#include "CPPCadesCollections.h"

//объ€вление структуры, котора€ св€жет объект оборачиваемого класса
//с объектом php
struct eku_col {
    zend_object zo;
    boost::shared_ptr<CryptoPro::PKI::CAdES::CPPCadesCPEKUsObject> m_pCppCadesImpl;
    zend_class_entry *type;
};

extern zend_class_entry *eku_col_ce;
extern zend_object_handlers eku_col_handlers;

void eku_col_free_storage(void *object TSRMLS_DC);
zend_object_value eku_col_create_handler(zend_class_entry *type TSRMLS_DC);

//функци€ инициализации класса. должна включатьс€ в
//функцию, инициализации модул€
void eku_col_init(TSRMLS_D);

#endif
