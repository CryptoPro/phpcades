#ifndef PHP_CP_OID_H_
#define PHP_CP_OID_H_

#include "CPPCadesCPOID.h"

//���������� ���������, ������� ������ ������ �������������� ������
//� �������� php
struct oid_obj {
    zend_object zo;
    NS_SHARED_PTR::shared_ptr<CryptoPro::PKI::CAdES::CPPCadesCPOIDObject> m_pCppCadesImpl;
};

//�������� ��� ��������� �������� �������������� ������
extern zend_object_handlers oid_obj_handlers;
extern zend_class_entry *oid_ce;

//������� ������������ ������. ������������ ��� ����������� ��������
void oid_free_storage(void *object TSRMLS_DC);
//������� �������� �������� ��� ������ ������� ������. ������������ ���
//�������� ����� ��������
zend_object_value oid_create_handler(zend_class_entry *type TSRMLS_DC);

//������� ������������� ������. ������ ���������� �
//�������, ������������� ������
void oid_init(TSRMLS_D);
#endif
