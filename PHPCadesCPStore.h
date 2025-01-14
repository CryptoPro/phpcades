#ifndef PHP_CP_STORE_H_
#define PHP_CP_STORE_H_
#include "CPPCadesCPStore.h"

//���������� ���������, ������� ������ ������ �������������� ������
//� �������� php
struct store_obj {
    zend_object zo;
    NS_SHARED_PTR::shared_ptr<CryptoPro::PKI::CAdES::CPPCadesCPStoreObject>
        m_pCppCadesImpl;
};

//�������� ��� ��������� �������� �������������� ������
extern zend_object_handlers store_obj_handlers;
extern zend_class_entry *store_ce;

//������� ������������ ������. ������������ ��� ����������� ��������
void store_free_storage(void *object TSRMLS_DC);

//������� �������� �������� ��� ������ ������� ������. ������������ ���
//�������� ����� ��������
zend_object_value store_create_handler(zend_class_entry *type TSRMLS_DC);

//������� ������������� ������. ������ ���������� �
//�������, ������������� ������
void store_init(TSRMLS_D);

#endif
