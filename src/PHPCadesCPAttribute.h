#ifndef PHP_CP_ATTRIBUTE_H_
#define PHP_CP_ATTRIBUTE_H_

#include "CPPCadesCPAttribute.h"

//объявление структуры, которая свяжет объект оборачиваемого класса
//с объектом php
typedef struct _attribute_obj {
    NS_SHARED_PTR::shared_ptr<CryptoPro::PKI::CAdES::CPPCadesCPAttributeObject>
        m_pCppCadesImpl;
    zend_object zobj; /* MUST be the last element */
} attribute_obj;

extern zend_object_handlers attribute_obj_handlers;
extern zend_class_entry *attribute_ce;

// // void attr_free_storage(void *object );
// zend_object_value attr_create_handler(zend_class_entry *type );
//функция инициализации класса. должна включаться в
//функцию, инициализации модуля
void attr_init(void);

#endif
