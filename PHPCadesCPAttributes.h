#ifndef PHP_CP_ATTRIBUTES_H_
#define PHP_CP_ATTRIBUTES_H_

#include "CPPCadesCPAttributes.h"

//объ€вление структуры, котора€ св€жет объект оборачиваемого класса
//с объектом php
struct attr_col {
    zend_object zo;
    boost::shared_ptr<CryptoPro::PKI::CAdES::CPPCadesCPAttributesObject> m_pCppCadesImpl;
    zend_class_entry *type;
};

extern zend_class_entry *attr_col_ce;
extern zend_object_handlers attr_col_handlers;

void attr_col_free_storage(void *object TSRMLS_DC);
zend_object_value attr_col_create_handler(zend_class_entry *type TSRMLS_DC);

//функци€ инициализации класса. должна включатьс€ в
//функцию, инициализации модул€
void attr_col_init(TSRMLS_D);

#endif
