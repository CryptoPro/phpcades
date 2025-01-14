#ifndef PHP_CP_PRIVATE_KEY_H_
#define PHP_CP_PRIVATE_KEY_H_

#include "CPPCadesCPPrivateKey.h"

//���������� ���������, ������� ������ ������ �������������� ������
//� �������� php
struct private_key_obj {
    zend_object zo;
    NS_SHARED_PTR::shared_ptr<CryptoPro::PKI::CAdES::CPPCadesCPPrivateKeyObject>
        m_pCppCadesImpl;
};

//�������� ��� ��������� �������� �������������� ������
extern zend_object_handlers private_key_obj_handlers;
extern zend_class_entry *private_key_ce;

//������� ������������ ������. ������������ ��� ����������� ��������
void private_key_free_storage(void *object TSRMLS_DC);
//������� �������� �������� ��� ������ ������� ������. ������������ ���
//�������� ����� ��������
zend_object_value private_key_create_handler(zend_class_entry *type TSRMLS_DC);

//������� ������������� ������. ������ ���������� �
//�������, ������������� ������
void private_key_init(TSRMLS_D);
#endif
