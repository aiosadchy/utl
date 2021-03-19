cmake_minimum_required (VERSION 3.8)
project(utl
        VERSION         0.0.1
        DESCRIPTION     "A simple general purpose utility library for modern C++"
        HOMEPAGE_URL    "https://github.com/aiosadchy/utl"
)

function(msg level)
    message(${level} "utl: " ${ARGN})
endfunction()

# utl library

option(
    UTL_UNSCOPED_MACROS
    "Define macros without 'UTL' prefix"
    OFF
)

option(
    UTL_USE_COUNTER_MACRO
    "Allow using '__COUNTER__' macro in library code"
    OFF
)

add_library(utl INTERFACE)
target_include_directories(utl INTERFACE include)
target_compile_features(utl INTERFACE cxx_std_17)

set(UTL_COMPILE_DEFINITIONS)

if (UTL_UNSCOPED_MACROS)
    set(UTL_COMPILE_DEFINITIONS ${UTL_COMPILE_DEFINITIONS} UTL_UNSCOPED_MACROS)
    msg(STATUS "define unscoped macros")
endif()

if (UTL_USE_COUNTER_MACRO)
    set(UTL_COMPILE_DEFINITIONS ${UTL_COMPILE_DEFINITIONS} UTL_USE_COUNTER_MACRO)
    msg(STATUS "allow using '__COUNTER__' macro in library code")
endif()

target_compile_definitions(utl INTERFACE ${UTL_COMPILE_DEFINITIONS})

# tests

add_executable(utl_test
        test/main.cpp
)
target_link_libraries(utl_test utl)
target_compile_options(utl_test PRIVATE -Wall -Wextra -pedantic)
