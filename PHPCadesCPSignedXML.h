#ifndef PHP_CADES_SIGNED_XML_H
#define PHP_CADES_SIGNED_XML_H

#include "CPPCadesSignedXML.h"

//���������� ���������, ������� ������ ������ �������������� ������
//� �������� php
struct sig_xml_obj {
    zend_object zo;
    NS_SHARED_PTR::shared_ptr<CryptoPro::PKI::CAdES::CPPCadesSignedXMLObject> m_pCppCadesImpl;
};

//�������� ��� ��������� �������� �������������� ������
extern zend_object_handlers sig_xml_obj_handlers;
extern zend_class_entry *sig_xml_ce;

void sig_xml_free_storage(void *object TSRMLS_DC);
zend_object_value sig_xml_create_handler(zend_class_entry *type TSRMLS_DC);

//������� ������������� ������. ������ ���������� �
//�������, ������������� ������
void sig_xml_init(TSRMLS_D);

#endif
