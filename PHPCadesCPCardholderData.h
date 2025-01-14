#ifndef PHP_CP_CARDHOLDER_DATA_H_
#define PHP_CP_CARDHOLDER_DATA_H_

#include "CPPCadesCardholderData.h"

//���������� ���������, ������� ������ ������ �������������� ������
//� �������� php
struct chd_obj {
    zend_object zo;
    CryptoPro::PKI::CAdES::CPPCadesCardholderDataObject *m_pCppCadesImpl;
};

//�������� ��� ��������� �������� �������������� ������
extern zend_object_handlers chd_obj_handlers;
extern zend_class_entry *chd_ce;

//������� ������������ ������. ������������ ��� ����������� ��������
void chd_free_storage(void *object TSRMLS_DC);
//������� �������� �������� ��� ������ ������� ������. ������������ ���
//�������� ����� ��������
zend_object_value chd_create_handler(zend_class_entry *type TSRMLS_DC);

//������� ������������� ������. ������ ���������� �
//�������, ������������� ������
void chd_init(TSRMLS_D);
#endif
