cmake_minimum_required(VERSION 3.16)
project(hermes)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find required packages
find_package(OpenSSL REQUIRED)
find_package(Threads REQUIRED)

# Add executable
add_executable(hermes
    src/main.cpp
    libs/easywsclient.cpp
)

# Include directory for easywsclient.hpp
target_include_directories(hermes PRIVATE
    libs/
    src/
)

# Link libraries
target_link_libraries(hermes
    OpenSSL::SSL
    OpenSSL::Crypto
    Threads::Threads
)

# Compiler flags
target_compile_options(hermes PRIVATE -Wall -Wextra -O2)
