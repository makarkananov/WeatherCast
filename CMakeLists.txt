cmake_minimum_required(VERSION 3.12)

project(
        lab10
        VERSION 1.0
        DESCRIPTION "C++ YEAR 2023 Lab10"
        LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)

if(WIN32) # Install dlls in the same directory as the executable on Windows
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
endif()

add_subdirectory(libs)
add_subdirectory(bin)