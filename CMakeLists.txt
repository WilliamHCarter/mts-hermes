cmake_minimum_required(VERSION 3.16)
project(hermes)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# conditional for macOS OpenSSL
if(APPLE)
    # Homebrew OpenSSL
    set(OPENSSL_ROOT_DIR /opt/homebrew/opt/openssl@3)
    set(OPENSSL_LIBRARIES /opt/homebrew/opt/openssl@3/lib)

    if(NOT EXISTS ${OPENSSL_ROOT_DIR})
        set(OPENSSL_ROOT_DIR /opt/homebrew/opt/openssl)
    endif()
    if(NOT EXISTS ${OPENSSL_ROOT_DIR})
        set(OPENSSL_ROOT_DIR /usr/local/opt/openssl@3)
    endif()
    if(NOT EXISTS ${OPENSSL_ROOT_DIR})
        set(OPENSSL_ROOT_DIR /usr/local/opt/openssl)
    endif()
endif()

# Find required packages
find_package(OpenSSL REQUIRED)
find_package(Threads REQUIRED)
find_package(ZLIB REQUIRED)

# Build uSockets
file(GLOB USOCKETS_SOURCES
    uWebSockets/uSockets/src/*.c
    uWebSockets/uSockets/src/eventing/*.c
    uWebSockets/uSockets/src/crypto/*.c
    uWebSockets/uSockets/src/crypto/*.cpp
)

add_library(uSockets STATIC ${USOCKETS_SOURCES})

# Include directories for uSockets
target_include_directories(uSockets PUBLIC
    uWebSockets/uSockets/src
    ${OPENSSL_INCLUDE_DIR}
)

target_compile_definitions(uSockets PRIVATE LIBUS_USE_OPENSSL)
target_link_libraries(uSockets PUBLIC
    OpenSSL::SSL
    OpenSSL::Crypto
)

# Add executable
add_executable(hermes
    src/main.cpp
)

# Include directories
target_include_directories(hermes PRIVATE
    uWebSockets/src
    uWebSockets/uSockets/src
    src/
    ${OPENSSL_INCLUDE_DIR}
)

# Link libraries
target_link_libraries(hermes
    uSockets
    OpenSSL::SSL
    OpenSSL::Crypto
    Threads::Threads
    ZLIB::ZLIB
)

# Compiler flags
target_compile_options(hermes PRIVATE -Wall -Wextra -O2)

# macOS specific flags
if(APPLE)
    target_link_libraries(hermes "-framework CoreFoundation")
endif()
