CMAKE_MINIMUM_REQUIRED(VERSION 3.5)
SET(PHP_INCLUDE_DIR "/php")
set (CMAKE_CXX_STANDARD 11)
PROJECT(PHPModule LANGUAGES CXX)
    SET (phpcades_LIB_SRCS
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
            errormsg.cpp
        )
FIND_PACKAGE( Boost REQUIRED )

ADD_DEFINITIONS(-DUNIX -DSIZEOF_VOID_P=${CMAKE_SIZEOF_VOID_P})
ADD_COMPILE_OPTIONS(-fpermissive)

EXECUTE_PROCESS(
    COMMAND bash -c "if type dpkg > /dev/null 2>&1; then dpkg -l|grep cprocsp-pki-cades|awk ' { print $3 } '; else rpm -qa|grep cprocsp-pki-cades; fi|cut -d. -f1|cut -d- -f1"
    OUTPUT_VARIABLE CPRO_CADES_VERSION_MAJOR
    OUTPUT_STRIP_TRAILING_WHITESPACE
    )
EXECUTE_PROCESS(
    COMMAND bash -c "if type dpkg > /dev/null 2>&1; then dpkg -l|grep cprocsp-pki-cades|awk ' { print $3 } '; else rpm -qa|grep cprocsp-pki-cades; fi|cut -d. -f2|cut -d- -f1"
    OUTPUT_VARIABLE CPRO_CADES_VERSION_MINOR
    OUTPUT_STRIP_TRAILING_WHITESPACE
    )
EXECUTE_PROCESS(
    COMMAND bash -c "if type dpkg > /dev/null 2>&1; then dpkg -l|grep cprocsp-pki-cades|awk ' { print $3 } '; else rpm -qa|grep cprocsp-pki-cades; fi|cut -d. -f3|cut -d- -f1"
    OUTPUT_VARIABLE CPRO_CADES_VERSION_BUILD
    OUTPUT_STRIP_TRAILING_WHITESPACE
    )
ADD_DEFINITIONS(-DCPRO_CADES_VERSION_MAJOR=${CPRO_CADES_VERSION_MAJOR})
ADD_DEFINITIONS(-DCPRO_CADES_VERSION_MINOR=${CPRO_CADES_VERSION_MINOR})
ADD_DEFINITIONS(-DCPRO_CADES_VERSION_BUILD=${CPRO_CADES_VERSION_BUILD})
MESSAGE("-- cprocsp-pki-cades: ${CPRO_CADES_VERSION_MAJOR}.${CPRO_CADES_VERSION_MINOR}.${CPRO_CADES_VERSION_BUILD}")

#SET(CMAKE_BUILD_TYPE Debug)
SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wno-write-strings")
SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wno-deprecated-declarations")
SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wno-narrowing")
SET(CMAKE_INCLUDE_CURRENT_DIR ON)
SET(phpcades_DIRS
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

INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIRS} )
INCLUDE_DIRECTORIES( ${PHP_INCLUDE_DIR})
INCLUDE_DIRECTORIES( ${phpcades_DIRS})

ADD_LIBRARY(phpcades SHARED ${phpcades_LIB_SRCS})
SET_TARGET_PROPERTIES(phpcades PROPERTIES PREFIX "")

FIND_LIBRARY(FOUND_LIB_CPPCADES
    NAMES cppcades
    HINTS /opt/cprocsp/lib/amd64 /opt/cprocsp/lib/ia32 /opt/cprocsp/lib/aarch64)
TARGET_LINK_LIBRARIES(phpcades ${FOUND_LIB_CPPCADES})

FIND_LIBRARY(FOUND_LIB_CPLIB
    NAMES cplib
    HINTS /opt/cprocsp/lib/amd64 /opt/cprocsp/lib/ia32 /opt/cprocsp/lib/aarch64)
TARGET_LINK_LIBRARIES(phpcades ${FOUND_LIB_CPLIB})

# ADD_CUSTOM_COMMAND(TARGET phpcades
#     POST_BUILD
#     COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:phpcades> ../../samples)