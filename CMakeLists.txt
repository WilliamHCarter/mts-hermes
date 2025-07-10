cmake_minimum_required(VERSION 3.16)
project(hermes)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

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
target_include_directories(uSockets PUBLIC uWebSockets/uSockets/src)
target_compile_definitions(uSockets PRIVATE LIBUS_USE_OPENSSL)

# Add executable
add_executable(hermes
    src/main.cpp
)

# Include directory for uWebSockets
target_include_directories(hermes PRIVATE
    uWebSockets/src
    uWebSockets/uSockets/src
    src/
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
