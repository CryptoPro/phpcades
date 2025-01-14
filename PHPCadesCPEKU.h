#ifndef PHP_CP_EKU_H_
#define PHP_CP_EKU_H_

#include "CPPCadesCPEKU.h"

//���������� ���������, ������� ������ ������ �������������� ������
//� �������� php
struct eku_obj {
    zend_object zo;
    NS_SHARED_PTR::shared_ptr<CryptoPro::PKI::CAdES::CPPCadesCPEKUObject> m_pCppCadesImpl;
};

//�������� ��� ��������� �������� �������������� ������
extern zend_object_handlers eku_obj_handlers;
extern zend_class_entry *eku_ce;

void eku_free_storage(void *object TSRMLS_DC);
zend_object_value item_create_handler(zend_class_entry *type TSRMLS_DC);

//������� ������������� ������. ������ ���������� �
//�������, ������������� ������
void eku_init(TSRMLS_D);

#endif
