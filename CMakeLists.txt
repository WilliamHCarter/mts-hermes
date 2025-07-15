cmake_minimum_required(VERSION 3.16)
project(hermes)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find required packages
find_package(OpenSSL REQUIRED)
find_package(Threads REQUIRED)

# Configure IXWebSocket with TLS support
set(USE_TLS ON CACHE BOOL "Enable TLS support")
set(USE_OPEN_SSL ON CACHE BOOL "Use OpenSSL for TLS")

# Fetch IXWebSocket automatically
include(FetchContent)
FetchContent_Declare(
    IXWebSocket
    GIT_REPOSITORY https://github.com/machinezone/IXWebSocket.git
    GIT_TAG        v11.4.5  # Latest stable version
)

# Make IXWebSocket available
FetchContent_MakeAvailable(IXWebSocket)

# Add executable
add_executable(hermes
    src/main.cpp
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
