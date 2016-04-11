cmake_minimum_required(VERSION 3.5)
project(smartPointers)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES SmartStrPointer.cpp)
add_executable(smartPointers ${SOURCE_FILES})
