cmake_minimum_required(VERSION 3.5)
set(PHP_INCLUDE_DIR "/php")
set(CMAKE_CXX_STANDARD 11)
project(PHPModule LANGUAGES CXX)

set(phpcades_LIB_SRCS
    PHPCadesCPSigners.cpp 
    PHPCadesCPSigner.cpp 
    PHPCadesCPExtendedKeyUsage.cpp
    PHPCadesCPAttribute.cpp 
    PHPCadesCPEKU.cpp 
    PHPCadesCPEKUs.cpp 
    PHPCadesCPBasicConstraints.cpp
    PHPCadesCPSignedData.cpp 
    PHPCadesCPPublicKey.cpp 
    PHPCadesCPPrivateKey.cpp 
    PHPCadesCPOID.cpp
    PHPCadesCPEncodedData.cpp 
    PHPCadesCPAttributes.cpp 
    PHPCadesCPCertificateStatus.cpp
    PHPCadesCPEnvelopedData.cpp 
    PHPCadesCPAlgorithm.cpp 
    PHPCadesCPRecipients.cpp 
    PHPCadesCPKeyUsage.cpp
    PHPCadesAbout.cpp 
    PHPCadesCPCertificates.cpp 
    PHPCadesCPSignedXML.cpp
    PHPCadesCPHashedData.cpp 
    PHPCadesCPRawSignature.cpp 
    PHPCadesCPCertificate.cpp 
    PHPCadesCPStore.cpp 
    dllmain.cpp 
    PHPCadesVersion.cpp 
    PHPCadesSymmetricAlgorithm.cpp 
)

find_package(Boost REQUIRED)

add_definitions(-DUNIX -DSIZEOF_VOID_P=${CMAKE_SIZEOF_VOID_P})
add_compile_options(-fpermissive)

execute_process(
    COMMAND bash -c "if type dpkg > /dev/null 2>&1; then dpkg -l|grep cprocsp-pki-cades|awk ' { print $3 } '; else rpm -qa|grep cprocsp-pki-cades; fi|cut -d. -f1|cut -d- -f1"
    OUTPUT_VARIABLE CPRO_CADES_VERSION_MAJOR
    OUTPUT_STRIP_TRAILING_WHITESPACE
)
execute_process(
    COMMAND bash -c "if type dpkg > /dev/null 2>&1; then dpkg -l|grep cprocsp-pki-cades|awk ' { print $3 } '; else rpm -qa|grep cprocsp-pki-cades; fi|cut -d. -f2|cut -d- -f1"
    OUTPUT_VARIABLE CPRO_CADES_VERSION_MINOR
    OUTPUT_STRIP_TRAILING_WHITESPACE
)
execute_process(
    COMMAND bash -c "if type dpkg > /dev/null 2>&1; then dpkg -l|grep cprocsp-pki-cades|awk ' { print $3 } '; else rpm -qa|grep cprocsp-pki-cades; fi|cut -d. -f3|cut -d- -f1"
    OUTPUT_VARIABLE CPRO_CADES_VERSION_BUILD
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

add_definitions(-DCPRO_CADES_VERSION_MAJOR=${CPRO_CADES_VERSION_MAJOR})
add_definitions(-DCPRO_CADES_VERSION_MINOR=${CPRO_CADES_VERSION_MINOR})
add_definitions(-DCPRO_CADES_VERSION_BUILD=${CPRO_CADES_VERSION_BUILD})

message(STATUS "cprocsp-pki-cades: ${CPRO_CADES_VERSION_MAJOR}.${CPRO_CADES_VERSION_MINOR}.${CPRO_CADES_VERSION_BUILD}")

#set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-write-strings")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated-declarations")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-narrowing")
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(phpcades_DIRS
    /opt/cprocsp/include
    /opt/cprocsp/include/cpcsp
    /opt/cprocsp/include/pki/atl
    /opt/cprocsp/include/pki/cppcades
    /opt/cprocsp/include/pki/cplib
    /opt/cprocsp/include/pki
    ${CMAKE_CURRENT_SOURCE_DIR}/cplib
    ${PHP_INCLUDE_DIR}/main
    ${PHP_INCLUDE_DIR}/Zend
    ${PHP_INCLUDE_DIR}/TSRM
)    

include_directories(${Boost_INCLUDE_DIRS})
include_directories(${PHP_INCLUDE_DIR})
include_directories(${phpcades_DIRS})

add_library(phpcades SHARED ${phpcades_LIB_SRCS})

find_library(FOUND_LIB_CPPCADES
    NAMES cppcades
    HINTS /opt/cprocsp/lib/amd64 /opt/cprocsp/lib/ia32 /opt/cprocsp/lib/aarch64)
target_link_libraries(phpcades ${FOUND_LIB_CPPCADES})

find_library(FOUND_LIB_CPLIB
    NAMES cplib
    HINTS /opt/cprocsp/lib/amd64 /opt/cprocsp/lib/ia32 /opt/cprocsp/lib/aarch64)
target_link_libraries(phpcades ${FOUND_LIB_CPLIB})