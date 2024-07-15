#ifndef PHP_CP_CERTIFICATES_H_
#define PHP_CP_CERTIFICATES_H_

//объявление структуры, которая свяжет объект оборачиваемого класса
//с объектом php
struct certs_obj {
    zend_object zo;
    boost::shared_ptr<CryptoPro::PKI::CAdES::CPPCadesCPCertificatesObject>
        m_pCppCadesImpl;
};

//хэндлеры для обработки объектов оборачиваемого класса
extern zend_object_handlers certs_obj_handlers;
extern zend_class_entry *certs_ce;

//функция освобождения памяти. используется при уничтожении объектов
void certs_free_storage(void *object TSRMLS_DC);

//функция создания хэндлера для нового объекта класса. используется при
//создании новых объектов
zend_object_value certs_create_handler(zend_class_entry *type TSRMLS_DC);

//функция инициализации класса. должна включаться в
//функцию, инициализации модуля
void certs_init(TSRMLS_D);
#endif
