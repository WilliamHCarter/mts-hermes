cmake_minimum_required(VERSION 3.16)
project(hermes)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Find required packages
find_package(OpenSSL REQUIRED)
find_package(Threads REQUIRED)

# TLS settings
set(USE_TLS ON CACHE BOOL "Enable TLS support")
set(USE_OPEN_SSL ON CACHE BOOL "Use OpenSSL for TLS")

include(FetchContent)

# IXWebSocket
FetchContent_Declare(
    IXWebSocket
    GIT_REPOSITORY https://github.com/machinezone/IXWebSocket.git
    GIT_TAG        v11.4.5  # Latest stable version
)
FetchContent_MakeAvailable(IXWebSocket)

# RapidJSON
set(RAPIDJSON_BUILD_DOC OFF CACHE INTERNAL "")
set(RAPIDJSON_BUILD_EXAMPLES OFF CACHE INTERNAL "")
set(RAPIDJSON_BUILD_TESTS OFF CACHE INTERNAL "")
FetchContent_Declare(
    rapidjson
    GIT_REPOSITORY https://github.com/Tencent/rapidjson.git
    GIT_TAG        master
)
FetchContent_MakeAvailable(rapidjson)

# Add executable
add_executable(hermes
    src/main.cpp
)

# Include RapidJSON headers
target_include_directories(hermes PRIVATE
    ${rapidjson_SOURCE_DIR}/include
)

# Link libraries
target_link_libraries(hermes
    ixwebsocket
    OpenSSL::SSL
    OpenSSL::Crypto
    Threads::Threads
)

# Compiler flags
target_compile_options(hermes PRIVATE -Wall -Wextra -O2)
