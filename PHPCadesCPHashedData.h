#ifndef PHP_HASHED_DATA_H
#define PHP_HASHED_DATA_H

#include "CPPCadesCPHashedData.h"

//объ€вление структуры, котора€ св€жет объект оборачиваемого класса
//с объектом php
struct hash_dat_obj {
    zend_object zo;
    boost::shared_ptr<CryptoPro::PKI::CAdES::CPPCadesCPHashedDataObject>
        m_pCppCadesImpl;
};

//хэндлеры дл€ обработки объектов оборачиваемого класса
extern zend_class_entry *hash_dat_class_entry;
extern zend_object_handlers hash_dat_handlers;

void hash_dat_free_storage(void *object TSRMLS_DC);
zend_object_value hash_dat_create_handler(zend_class_entry *type TSRMLS_DC);

//функци€ инициализации класса. должна включатьс€ в
//функцию, инициализации модул€
void hash_dat_init(TSRMLS_D);

#endif
