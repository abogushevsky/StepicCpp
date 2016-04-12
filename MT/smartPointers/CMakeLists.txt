cmake_minimum_required(VERSION 3.5)
project(smartPointers)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES StringPointer.cpp)
add_executable(smart ${SOURCE_FILES})
