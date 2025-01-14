#ifndef PHP_SIGNERS_H
#define PHP_SIGNERS_H

#include "CPPCadesCollections.h"

//���������� ���������, ������� ������ ������ �������������� ������
//� �������� php
struct signers_obj {
    zend_object zo;
    NS_SHARED_PTR::shared_ptr<CryptoPro::PKI::CAdES::CPPCadesCPSignersObject> m_pCppCadesImpl;
};

//�������� ��� ��������� �������� �������������� ������
extern zend_class_entry *signers_ce;
extern zend_object_handlers signers_obj_handlers;

void signers_free_storage(void *object TSRMLS_DC);
zend_object_value signers_create_handler(zend_class_entry *type TSRMLS_DC);

//������� ������������� ������. ������ ���������� �
//�������, ������������� ������
void signers_init(TSRMLS_D);

#endif
