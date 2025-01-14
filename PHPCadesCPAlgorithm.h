#ifndef PHP_CP_ALGORITHM_H_
#define PHP_CP_ALGORITHM_H_

#include "CPPCadesCPAlgorithm.h"

//���������� ���������, ������� ������ ������ �������������� ������
//� �������� php
struct algo_obj {
    zend_object zo;
    CryptoPro::PKI::CAdES::CPPCadesCPAlgorithmObject *m_pCppCadesImpl;
};

//�������� ��� ��������� �������� �������������� ������
extern zend_object_handlers algo_obj_handlers;
extern zend_class_entry *algo_ce;

//������� ������������ ������. ������������ ��� ����������� ��������
void algo_free_storage(void *object TSRMLS_DC);

//������� �������� �������� ��� ������ ������� ������. ������������ ���
//�������� ����� ��������
zend_object_value algo_create_handler(zend_class_entry *type TSRMLS_DC);

//������� ������������� ������. ������ ���������� �
//�������, ������������� ������
void algo_init(TSRMLS_D);

#endif
