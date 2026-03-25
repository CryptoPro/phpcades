#ifndef PHP_CP_EKUS_H_
#define PHP_CP_EKUS_H_

#include "CPPCadesCollections.h"

//объявление структуры, которая свяжет объект оборачиваемого класса
//с объектом php
typedef struct _eku_col_obj {
    NS_SHARED_PTR::shared_ptr<CryptoPro::PKI::CAdES::CPPCadesCPEKUsObject> m_pCppCadesImpl;
    zend_class_entry *type;
    zend_object zobj; /* MUST be the last element */
} eku_col_obj;

extern zend_class_entry *eku_col_ce;
extern zend_object_handlers eku_col_handlers;

// void eku_col_free_storage(void *object );
// zend_object_value eku_col_create_handler(zend_class_entry *type );

//функция инициализации класса. должна включаться в
//функцию, инициализации модуля
void eku_col_init(void);

#endif
