#ifndef PHP_CADES_SIGNED_XML_H
#define PHP_CADES_SIGNED_XML_H

#include "CPPCadesSignedXML.h"

//объявление структуры, которая свяжет объект оборачиваемого класса
//с объектом php
typedef struct _signed_xml_obj {
    NS_SHARED_PTR::shared_ptr<CryptoPro::PKI::CAdES::CPPCadesSignedXMLObject> m_pCppCadesImpl;
    zend_object zobj; /* MUST be the last element */
} signed_xml_obj;

//хэндлеры для обработки объектов оборачиваемого класса
extern zend_object_handlers signed_xml_obj_handlers;
extern zend_class_entry *signed_xml_ce;

// void signed_xml_free_storage(void *object );
// zend_object_value signed_xml_create_handler(zend_class_entry *type );

//функция инициализации класса. должна включаться в
//функцию, инициализации модуля
void signed_xml_init(void);

#endif
