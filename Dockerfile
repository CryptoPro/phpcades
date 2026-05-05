# cp -r ~/linux-amd64_deb/ .
# docker build -t phpcades-build .

FROM ubuntu:latest

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && \
    apt-get install -y --no-install-recommends \
        git \
        cmake \
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
        ./csp/cprocsp-legacy* \
        ./csp/cprocsp-pki-cades* && \
    rm -rf /var/lib/apt/lists/*

COPY . /phpcades

WORKDIR /phpcades

RUN mkdir build && cd build && \
    cmake .. && \
    make -j$(nproc)

RUN php_exts=$(php -i | grep 'extension_dir' | cut -d' ' -f3 | xargs) && \
    ln -s $(realpath build/src/libphpcades.so) $php_exts

RUN echo 'extension=libphpcades.so' >> $(php --ini | sed -n 's/^Loaded Configuration File: *//p')

# docker run -it -w /phpcades/samples/ phpcades-build
# /opt/cprocsp/bin/amd64/cryptcp -createcert -dn "CN=test" -provtype 80 -cont '\\.\HDIMAGE\test' -ca https://cryptopro.ru/certsrv
# php test_extension.php
