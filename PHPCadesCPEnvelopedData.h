#ifndef PHP_CP_ENVELOPED_DATA_H_
#define PHP_CP_ENVELOPED_DATA_H_

#include "stdafx.h"
#include "CPPCadesCPEnvelopedData.h"

//���������� ���������, ������� ������ ������ �������������� ������
//� �������� php
struct enveloped_data_obj {
    zend_object zo;
    CryptoPro::PKI::CAdES::CPPCadesCPEnvelopedDataObject *m_pCppCadesImpl;
};

//�������� ��� ��������� �������� �������������� ������
extern zend_object_handlers enveloped_data_obj_handlers;
extern zend_class_entry *enveloped_data_ce;

//������� ������������ ������. ������������ ��� ����������� ��������
void enveloped_data_free_storage(void *object TSRMLS_DC);
//������� �������� �������� ��� ������ ������� ������. ������������ ���
//�������� ����� ��������
zend_object_value enveloped_data_create_handler(zend_class_entry *type
                                                    TSRMLS_DC);

//������� ������������� ������. ������ ���������� �
//�������, ������������� ������
void enveloped_data_init(TSRMLS_D);
#endif
