#ifndef PHP_CP_CERTIFICATES_H_
#define PHP_CP_CERTIFICATES_H_

//���������� ���������, ������� ������ ������ �������������� ������
//� �������� php
struct certs_obj {
    zend_object zo;
    NS_SHARED_PTR::shared_ptr<CryptoPro::PKI::CAdES::CPPCadesCPCertificatesObject>
        m_pCppCadesImpl;
};

//�������� ��� ��������� �������� �������������� ������
extern zend_object_handlers certs_obj_handlers;
extern zend_class_entry *certs_ce;

//������� ������������ ������. ������������ ��� ����������� ��������
void certs_free_storage(void *object TSRMLS_DC);

//������� �������� �������� ��� ������ ������� ������. ������������ ���
//�������� ����� ��������
zend_object_value certs_create_handler(zend_class_entry *type TSRMLS_DC);

//������� ������������� ������. ������ ���������� �
//�������, ������������� ������
void certs_init(TSRMLS_D);
#endif
