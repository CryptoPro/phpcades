#ifndef PHP_SYMMETRIC_ALGORITHM_H_
#define PHP_SYMMETRIC_ALGORITHM_H_

#include "CPPCadesSymmetricAlgorithm.h"

//���������� ���������, ������� ������ ������ �������������� ������
//� �������� php
struct symmetric_algorithm_obj {
    zend_object zo;
    NS_SHARED_PTR::shared_ptr<CryptoPro::PKI::CAdES::CPPCadesSymmetricAlgorithmObject>
        m_pCppCadesImpl;
};

//�������� ��� ��������� �������� �������������� ������
extern zend_object_handlers symmetric_algorithm_obj_handlers;
extern zend_class_entry *symmetric_algorithm_ce;

//������� ������������ ������. ������������ ��� ����������� ��������
void symmetric_algorithm_free_storage(void *object TSRMLS_DC);
//������� �������� �������� ��� ������ ������� ������. ������������ ���
//�������� ����� ��������
zend_object_value symmetric_algorithm_create_handler(zend_class_entry *type
                                                         TSRMLS_DC);

//������� ������������� ������. ������ ���������� �
//�������, ������������� ������
void symmetric_algorithm_init(TSRMLS_D);
#endif
