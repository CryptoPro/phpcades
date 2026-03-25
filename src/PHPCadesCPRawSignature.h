#ifndef PHPCADES_RAW_SIGNATURE
#define PHPCADES_RAW_SIGNATURE

#include "CPPCadesRawSignature.h"

//объявление структуры, которая свяжет объект оборачиваемого класса
//с объектом php
typedef struct _raw_sig_obj {
    NS_SHARED_PTR::shared_ptr<CryptoPro::PKI::CAdES::CPPCadesRawSignatureObject>
        m_pCppCadesImpl;
    zend_object zobj; /* MUST be the last element */
} raw_sig_obj;

//хэндлеры для обработки объектов оборачиваемого класса
extern zend_class_entry *raw_sig_ce;
extern zend_object_handlers raw_sig_obj_handlers;

// void raw_sig_free_storage(void *object );
// zend_object_value raw_sig_create_handler(zend_class_entry *type );

//функция инициализации класса. должна включаться в
//функцию, инициализации модуля
void raw_sig_init(void);

#endif
