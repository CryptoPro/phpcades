#ifndef PHP_CADES_SIGNED_XML_H
#define PHP_CADES_SIGNED_XML_H

#include "CPPCadesSignedXML.h"

//объ€вление структуры, котора€ св€жет объект оборачиваемого класса
//с объектом php
struct sig_xml_obj {
    zend_object zo;
    boost::shared_ptr<CryptoPro::PKI::CAdES::CPPCadesSignedXMLObject> m_pCppCadesImpl;
};

//хэндлеры дл€ обработки объектов оборачиваемого класса
extern zend_object_handlers sig_xml_obj_handlers;
extern zend_class_entry *sig_xml_ce;

void sig_xml_free_storage(void *object TSRMLS_DC);
zend_object_value sig_xml_create_handler(zend_class_entry *type TSRMLS_DC);

//функци€ инициализации класса. должна включатьс€ в
//функцию, инициализации модул€
void sig_xml_init(TSRMLS_D);

#endif
