cmake_minimum_required(VERSION 2.8)
project(TestProject2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++11")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/ext)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/ext)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/ext/CMakeModules ${CMAKE_MODULE_PATH})

include_directories(${CMAKE_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/src ${CMAKE_SOURCE_DIR}/ext ${CMAKE_SOURCE_DIR}/ext/include)

add_subdirectory(src)




