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

RUN (SCRIPTS_DIR=./tests/scripts && \
    chmod +x ${SCRIPTS_DIR}/*.sh && \
    ${SCRIPTS_DIR}/setup-root.sh && \
    ${SCRIPTS_DIR}/setup-leaf.sh && \
    ${SCRIPTS_DIR}/setup-crl.sh) > /dev/null 2>&1

RUN make

RUN php_exts=$(php -i | grep 'extension_dir' | cut -d' ' -f3 | xargs) && \
    ln -s $(realpath build/src/libphpcades.so) $php_exts

RUN echo 'extension=libphpcades.so' >> $(php --ini | sed -n 's/^Loaded Configuration File: *//p')

# docker run phpcades-build php samples/test_extension.php
