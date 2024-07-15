#ifndef PHPCADES_RAW_SIGNATURE
#define PHPCADES_RAW_SIGNATURE

#include "CPPCadesRawSignature.h"

//объ€вление структуры, котора€ св€жет объект оборачиваемого класса
//с объектом php
struct raw_sig_obj {
    zend_object zo;
    boost::shared_ptr<CryptoPro::PKI::CAdES::CPPCadesRawSignatureObject>
        m_pCppCadesImpl;
};

//хэндлеры дл€ обработки объектов оборачиваемого класса
extern zend_class_entry *raw_sig_class_entry;
extern zend_object_handlers raw_sig_handlers;

void raw_sig_free_storage(void *object TSRMLS_DC);
zend_object_value raw_sig_create_handler(zend_class_entry *type TSRMLS_DC);

//функци€ инициализации класса. должна включатьс€ в
//функцию, инициализации модул€
void raw_sig_init(TSRMLS_D);

#endif
