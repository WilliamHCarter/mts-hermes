cmake_minimum_required(VERSION 3.16)
project(hermes)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Fetch IXWebSocket automatically
include(FetchContent)
FetchContent_Declare(
    IXWebSocket
    GIT_REPOSITORY https://github.com/machinezone/IXWebSocket.git
    GIT_TAG        v11.4.5  # Latest stable version
)

# Make IXWebSocket available
FetchContent_MakeAvailable(IXWebSocket)

# Find required packages
find_package(OpenSSL REQUIRED)
find_package(Threads REQUIRED)

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
