cmake_minimum_required(VERSION 3.5)
project(phpcades LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-write-strings -Wno-deprecated-declarations -Wno-narrowing")
#set(CMAKE_BUILD_TYPE Debug)
add_compile_options(-fpermissive)
add_definitions(-DUNIX -DSIZEOF_VOID_P=${CMAKE_SIZEOF_VOID_P})

execute_process(
    COMMAND php-config --include-dir
    OUTPUT_VARIABLE PHP_INCLUDE_DIR
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

if(NOT PHP_INCLUDE_DIR)
    message(FATAL_ERROR "php-config not found. Please install php-dev or php-devel package.")
else()
    message(STATUS "Found PHP include directory: ${PHP_INCLUDE_DIR}")
endif()

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

find_package(Boost REQUIRED)

add_subdirectory(src)