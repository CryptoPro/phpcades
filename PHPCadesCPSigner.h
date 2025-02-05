#ifndef CP_SIGNER_H
#define CP_SIGNER_H

#include "CPPCadesCPSigner.h"

typedef struct _signer_obj {
    NS_SHARED_PTR::shared_ptr<CryptoPro::PKI::CAdES::CPPCadesCPSignerObject> m_pCppCadesImpl;
    zend_object zobj; /* MUST be the last element */
} signer_obj;

extern zend_object_handlers signer_obj_handlers;
extern zend_class_entry *signer_ce;

// void sig_free_storage(void *object );
// zend_object* sig_create_handler(zend_class_entry *type );
//функция инициализации класса. должна включаться в
//функцию, инициализации модуля
void sig_init(void);
#endif
