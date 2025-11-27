# cp -r ~/linux-amd64_deb/ .
# docker build -t phpcades-build .

FROM ubuntu:latest

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && \
    apt-get install -y --no-install-recommends \
        git \
        libxml2-dev \
        build-essential \
        libboost-all-dev \
        ca-certificates \
        php-dev && \
    rm -rf /var/lib/apt/lists/*

RUN update-ca-certificates

COPY linux-amd64_deb csp

RUN chmod +x ./csp/install*.sh

RUN ./csp/install.sh

RUN apt-get update && apt-get install -y --no-install-recommends \
        ./csp/cprocsp-rdr-gui-gtk* \
        ./csp/lsb-cprocsp-devel* \
        ./csp/cprocsp-pki-cades* && \
    rm -rf /var/lib/apt/lists/*

RUN git clone https://github.com/CryptoPro/phpcades.git

WORKDIR /phpcades

RUN php_dir=$(find /usr/include -name "php.h" 2>/dev/null | xargs dirname | xargs dirname) && \
    sed -i "s|^PHPDIR=.*|PHPDIR=$php_dir|" Makefile.unix

RUN eval `/opt/cprocsp/src/doxygen/CSP/../setenv.sh --64`; \
    make -f Makefile.unix

RUN php_exts=$(php -i | grep 'extension_dir' | cut -d' ' -f3 | xargs) && \
    ln -s $(realpath libphpcades.so) $php_exts

RUN echo 'extension=libphpcades.so' >> $(php --ini | sed -n 's/^Loaded Configuration File: *//p')

# docker run -it phpcades-build
# /opt/cprocsp/bin/amd64/cryptcp -createcert -dn "CN=test" -provtype 80 -cont '\\.\HDIMAGE\test' -ca https://cryptopro.ru/certsrv
# php test_extension.php
