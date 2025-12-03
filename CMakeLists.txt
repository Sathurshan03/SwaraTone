# Project CMakeLists.txt

cmake_minimum_required(VERSION 3.10)

project(SwaraTone VERSION 1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

option(BUILD_TESTS "ON to build tests job." OFF)

add_subdirectory(src)

if(BUILD_TESTS)
    add_subdirectory(test)
endif()
