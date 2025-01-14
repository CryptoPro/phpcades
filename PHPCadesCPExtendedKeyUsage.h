#ifndef PHP_CP_EXTENDED_KEY_USAGE_H_
#define PHP_CP_EXTENDED_KEY_USAGE_H_

#include "CPPCadesCPExtendedKeyUsage.h"

//���������� ���������, ������� ������ ������ �������������� ������
//� �������� php
struct exku_obj {
    zend_object zo;
    NS_SHARED_PTR::shared_ptr<CryptoPro::PKI::CAdES::CPPCadesCPExtendedKeyUsageObject>
        m_pCppCadesImpl;
};

//�������� ��� ��������� �������� �������������� ������
extern zend_object_handlers exku_obj_handlers;
extern zend_class_entry *exku_ce;

//������� ������������ ������. ������������ ��� ����������� ��������
void exku_free_storage(void *object TSRMLS_DC);

//������� �������� �������� ��� ������ ������� ������. ������������ ���
//�������� ����� ��������
zend_object_value exku_create_handler(zend_class_entry *type TSRMLS_DC);

//������� ������������� ������. ������ ���������� �
//�������, ������������� ������
void exku_init(TSRMLS_D);
#endif
