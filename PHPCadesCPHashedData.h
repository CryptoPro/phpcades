#ifndef PHP_HASHED_DATA_H
#define PHP_HASHED_DATA_H

#include "CPPCadesCPHashedData.h"

//���������� ���������, ������� ������ ������ �������������� ������
//� �������� php
struct hash_dat_obj {
    zend_object zo;
    NS_SHARED_PTR::shared_ptr<CryptoPro::PKI::CAdES::CPPCadesCPHashedDataObject>
        m_pCppCadesImpl;
};

//�������� ��� ��������� �������� �������������� ������
extern zend_class_entry *hash_dat_class_entry;
extern zend_object_handlers hash_dat_handlers;

void hash_dat_free_storage(void *object TSRMLS_DC);
zend_object_value hash_dat_create_handler(zend_class_entry *type TSRMLS_DC);

//������� ������������� ������. ������ ���������� �
//�������, ������������� ������
void hash_dat_init(TSRMLS_D);

#endif
