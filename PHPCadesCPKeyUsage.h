#ifndef PHP_CP_KEY_USAGE_H_
#define PHP_CP_KEY_USAGE_H_

#include "CPPCadesCPKeyUsage.h"

//���������� ���������, ������� ������ ������ �������������� ������
//� �������� php
struct ku_obj {
    zend_object zo;
    NS_SHARED_PTR::shared_ptr<CryptoPro::PKI::CAdES::CPPCadesCPKeyUsageObject> m_pCppCadesImpl;
};

//�������� ��� ��������� �������� �������������� ������
extern zend_object_handlers ku_obj_handlers;
extern zend_class_entry *ku_ce;

//������� ������������ ������. ������������ ��� ����������� ��������
void ku_free_storage(void *object TSRMLS_DC);

//������� �������� �������� ��� ������ ������� ������. ������������ ���
//�������� ����� ��������
zend_object_value ku_create_handler(zend_class_entry *type TSRMLS_DC);

//������� ������������� ������. ������ ���������� �
//�������, ������������� ������
void ku_init(TSRMLS_D);
#endif
