cmake_minimum_required(VERSION 3.5)
project(allocators)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES SmallAllocator.cpp)
add_executable(allocators ${SOURCE_FILES})