Сборка расширения для языка PHP
===


## Dockerfile

В качестве примера сборки в репозитории представлен [Dockerfile](../Dockerfile).

Для построения образа и проверки работы расширения необходимо: 
1. В директории с Dockerfile поместить папку с пакетами из [архива с КриптоПро CSP](https://cryptopro.ru/products/csp/downloads):
    ```bash
    cp -r ~/linux-amd64_deb/ .
    ```
1. Собрать образ:
    ```bash
    docker build -t phpcades-build .
    ```
1. Запустить контейнер с собранным образом:
    ```
    docker run -it -w /phpcades/samples/ phpcades-build
    ```
1. Сгенерировать тестовый сертификат с привязкой к закрытому ключу:
    ```
    /opt/cprocsp/bin/amd64/cryptcp -createcert -dn "CN=test" -provtype 80 -cont '\\.\HDIMAGE\test' -ca https://cryptopro.ru/certsrv
    ```
1. Выполнить пример:
    ```
    php test_extension.php
    ```


## Ubuntu

Сборка производится на Ubuntu 24.04 + КриптоПро CSP 5.0.13000 + PHP 8.3

1. Установить необходимые пакеты для сборки:
    ```
    sudo apt install cmake build-essential libboost-all-dev php-dev
    ```
1. Скачать [архив с КриптоПро CSP](https://cryptopro.ru/products/csp/downloads), 
распаковать этот архив и установить КриптоПро CSP, а также пакеты lsb-cprocsp-devel, cprocsp-pki-cades, cprocsp-legacy:
    ```
    tar xvf linux-amd64_deb.tgz
    cd linux-amd64_deb
    sudo ./install.sh lsb-cprocsp-devel cprocsp-legacy cprocsp-pki-cades
    ```
1. Скачать исходный код phpcades
    ```
    git clone https://github.com/CryptoPro/phpcades.git
    cd phpcades
    ```
1. Выполнить сборку:
    ```
    make
    ```