#ifndef PHP_CP_ENCODED_DATA_H_
#define PHP_CP_ENCODED_DATA_H_

#include "CPPCadesCPEncodedData.h"

//���������� ���������, ������� ������ ������ �������������� ������
//� �������� php
struct encoded_data_obj {
    zend_object zo;
    NS_SHARED_PTR::shared_ptr<CryptoPro::PKI::CAdES::CPPCadesCPEncodedDataObject>
        m_pCppCadesImpl;
};

//�������� ��� ��������� �������� �������������� ������
extern zend_object_handlers encoded_data_obj_handlers;
extern zend_class_entry *encoded_data_ce;

//������� ������������ ������. ������������ ��� ����������� ��������
void encoded_data_free_storage(void *object TSRMLS_DC);
//������� �������� �������� ��� ������ ������� ������. ������������ ���
//�������� ����� ��������
zend_object_value encoded_data_create_handler(zend_class_entry *type TSRMLS_DC);

//������� ������������� ������. ������ ���������� �
//�������, ������������� ������
void encoded_data_init(TSRMLS_D);
#endif
