#ifndef PHP_CP_ATTRIBUTE_H_
#define PHP_CP_ATTRIBUTE_H_

#include "CPPCadesCPAttribute.h"

//объ€вление структуры, котора€ св€жет объект оборачиваемого класса
//с объектом php
struct attr_obj {
    zend_object zo;
    boost::shared_ptr<CryptoPro::PKI::CAdES::CPPCadesCPAttributeObject>
        m_pCppCadesImpl;
};

extern zend_object_handlers attr_obj_handlers;
extern zend_class_entry *attr_ce;

void attr_free_storage(void *object TSRMLS_DC);
zend_object_value attr_create_handler(zend_class_entry *type TSRMLS_DC);
//функци€ инициализации класса. должна включатьс€ в
//функцию, инициализации модул€
void attr_init(TSRMLS_D);

#endif
