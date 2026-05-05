set(phpcades_LIB_SRCS
    PHPCadesAbout.cpp
    PHPCadesCPAlgorithm.cpp
    PHPCadesCPAttribute.cpp
    PHPCadesCPAttributes.cpp
    PHPCadesCPBasicConstraints.cpp
    PHPCadesCPCertificate.cpp
    PHPCadesCPCertificateStatus.cpp
    PHPCadesCPCertificates.cpp
    PHPCadesCPEKU.cpp
    PHPCadesCPEKUs.cpp
    PHPCadesCPEncodedData.cpp
    PHPCadesCPEnvelopedData.cpp
    PHPCadesCPExtendedKeyUsage.cpp
    PHPCadesCPHashedData.cpp
    PHPCadesCPKeyUsage.cpp
    PHPCadesCPOID.cpp
    PHPCadesCPPrivateKey.cpp
    PHPCadesCPPublicKey.cpp
    PHPCadesCPRawSignature.cpp
    PHPCadesCPRecipients.cpp
    PHPCadesCPSignedData.cpp
    PHPCadesCPSignedXML.cpp
    PHPCadesCPSigner.cpp
    PHPCadesCPSigners.cpp
    PHPCadesCPStore.cpp
    PHPCadesSymmetricAlgorithm.cpp
    PHPCadesVersion.cpp
    dllmain.cpp
)

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
set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_library(phpcades SHARED ${phpcades_LIB_SRCS})

find_library(FOUND_LIB_CPPCADES
    NAMES cppcades
    HINTS /opt/cprocsp/lib/amd64 /opt/cprocsp/lib/ia32 /opt/cprocsp/lib/aarch64)

find_library(FOUND_LIB_CPLIB
    NAMES cplib
    HINTS /opt/cprocsp/lib/amd64 /opt/cprocsp/lib/ia32 /opt/cprocsp/lib/aarch64)

target_link_libraries(phpcades ${FOUND_LIB_CPPCADES} ${FOUND_LIB_CPLIB})