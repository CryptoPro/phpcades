#ifndef PHP_CPC_PUBLIC_KEY_H_
#define PHP_CPC_PUBLIC_KEY_H_

#include "CPPCadesCPPublicKey.h"

//���������� ���������, ������� ������ ������ �������������� ������
//� �������� php
struct public_key_obj {
    zend_object zo;
    NS_SHARED_PTR::shared_ptr<CryptoPro::PKI::CAdES::CPPCadesCPPublicKeyObject>
        m_pCppCadesImpl;
};

//�������� ��� ��������� �������� �������������� ������
extern zend_object_handlers public_key_obj_handlers;
extern zend_class_entry *public_key_ce;

//������� ������������ ������. ������������ ��� ����������� ��������
void public_key_free_storage(void *object TSRMLS_DC);
//������� �������� �������� ��� ������ ������� ������. ������������ ���
//�������� ����� ��������
zend_object_value public_key_create_handler(zend_class_entry *type TSRMLS_DC);

//������� ������������� ������. ������ ���������� �
//�������, ������������� ������
void public_key_init(TSRMLS_D);
#endif
