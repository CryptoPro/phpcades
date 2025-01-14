#ifndef PHP_ABOUT_H_
#define PHP_ABOUT_H_

#include "CPPCadesAbout.h"
#include "php.h"

//���������� ���������, ������� ������ ������ �������������� ������
//� �������� php
struct about_obj {
    zend_object zo;
    NS_SHARED_PTR::shared_ptr<CryptoPro::PKI::CAdES::CPPCadesAboutObject>
        m_pCppCadesImpl;
};

//�������� ��� ��������� �������� �������������� ������
extern zend_object_handlers about_obj_handlers;

extern zend_class_entry *about_ce;

//������� ������������ ������. ������������ ��� ����������� ��������
void about_free_storage(void *object TSRMLS_DC);

//������� �������� �������� ��� ������ ������� ������. ������������ ���
//�������� ����� ��������
zend_object_value about_create_handler(zend_class_entry *type TSRMLS_DC);

//������� ������������� ������. ������ ���������� �
//�������, ������������� ������
void about_init(TSRMLS_D);

#endif
