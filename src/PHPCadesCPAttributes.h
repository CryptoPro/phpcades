#ifndef PHP_CP_ATTRIBUTES_H_
#define PHP_CP_ATTRIBUTES_H_

#include "CPPCadesCPAttributes.h"

//объявление структуры, которая свяжет объект оборачиваемого класса
//с объектом php
typedef struct _attributes_col_obj {
    NS_SHARED_PTR::shared_ptr<CryptoPro::PKI::CAdES::CPPCadesCPAttributesObject> m_pCppCadesImpl;
    zend_class_entry *type;
    zend_object zobj; /* MUST be the last element */
} attributes_col_obj;

extern zend_class_entry *attributes_col_ce;
extern zend_object_handlers attributes_col_obj_handlers;

// void attr_col_free_storage(void *object );
// zend_object_value attr_col_create_handler(zend_class_entry *type );

//функция инициализации класса. должна включаться в
//функцию, инициализации модуля
void attr_col_init(void);

#endif
