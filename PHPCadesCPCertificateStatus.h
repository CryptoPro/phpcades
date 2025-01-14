#ifndef PHP_CP_CERTIFICATE_STATUS_H_
#define PHP_CP_CERTIFICATE_STATUS_H_

#include "CPPCadesCPCertificateStatus.h"

//���������� ���������, ������� ������ ������ �������������� ������
//� �������� php
struct certstat_obj {
    zend_object zo;
    NS_SHARED_PTR::shared_ptr<CryptoPro::PKI::CAdES::CPPCadesCPCertificateStatusObject>
        m_pCppCadesImpl;
};

//�������� ��� ��������� �������� �������������� ������
extern zend_object_handlers certstat_obj_handlers;
extern zend_class_entry *certstat_ce;

//������� ������������ ������. ������������ ��� ����������� ��������
void certstat_free_storage(void *object TSRMLS_DC);

//������� �������� �������� ��� ������ ������� ������. ������������ ���
//�������� ����� ��������
zend_object_value certstat_create_handler(zend_class_entry *type TSRMLS_DC);

//������� ������������� ������. ������ ���������� �
//�������, ������������� ������
void certstat_init(TSRMLS_D);
#endif
