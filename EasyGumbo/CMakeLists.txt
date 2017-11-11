cmake_minimum_required(VERSION 3.0)
cmake_policy(SET CMP0048 NEW)

set(PROJECT EasyGumbo)

project(${PROJECT}
        VERSION 1.0.0)

# c++11
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++11")

file(GLOB SOURCES
    src/*.h
    src/*.cpp
    src/*.hpp
)
add_library(${PROJECT} ${SOURCES})