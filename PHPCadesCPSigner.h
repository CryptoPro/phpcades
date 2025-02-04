#ifndef CP_SIGNER_H
#define CP_SIGNER_H

#include "CPPCadesCPSigner.h"

struct sig_obj {
    zend_object zo;
    NS_SHARED_PTR::shared_ptr<CryptoPro::PKI::CAdES::CPPCadesCPSignerObject> m_pCppCadesImpl;
};

extern zend_object_handlers sig_obj_handlers;
extern zend_class_entry *sig_ce;

void sig_free_storage(void *object TSRMLS_DC);
zend_object_value sig_create_handler(zend_class_entry *type TSRMLS_DC);
//функция инициализации класса. должна включаться в
//функцию, инициализации модуля
void sig_init(TSRMLS_D);
#endif
