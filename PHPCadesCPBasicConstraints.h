#ifndef PHP_CP_BASICCONSTRAINTS_H_
#define PHP_CP_BASICCONSTRAINTS_H_

#include "CPPCadesCPBasicConstraints.h"

//���������� ���������, ������� ������ ������ �������������� ������
//� �������� php
struct basic_constr_obj {
    zend_object zo;
    NS_SHARED_PTR::shared_ptr<CryptoPro::PKI::CAdES::CPPCadesCPBasicConstraintsObject>
        m_pCppCadesImpl;
};

//�������� ��� ��������� �������� �������������� ������
extern zend_object_handlers basic_constr_obj_handlers;
extern zend_class_entry *basic_constr_ce;

//������� ������������ ������. ������������ ��� ����������� ��������
void basic_constr_free_storage(void *object TSRMLS_DC);
//������� �������� �������� ��� ������ ������� ������. ������������ ���
//�������� ����� ��������
zend_object_value basic_constr_create_handler(zend_class_entry *type TSRMLS_DC);

//������� ������������� ������. ������ ���������� �
//�������, ������������� ������
void basic_constr_init(TSRMLS_D);
#endif
