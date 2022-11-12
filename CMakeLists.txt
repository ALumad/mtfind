cmake_minimum_required(VERSION 3.16)
project(fileparser CXX)
set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_STANDARD 17)

set(LIB_NAME parser)
set(BIN_NAME mtfind)
set(TEST_NAME testparser)
enable_testing()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

add_subdirectory(src)
