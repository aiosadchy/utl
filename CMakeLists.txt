cmake_minimum_required (VERSION 3.8)
project(utl
    VERSION         0.1.0
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

add_executable(utl_tests
        test/src/main.cpp
        test/src/test.cpp
        test/src/test_non_constructible.cpp
        test/src/test_non_copyable.cpp
        test/src/test_range.cpp
        test/src/test_repeat.cpp
        test/src/test_scope_guard.cpp
        test/src/test_static_block.cpp
        test/src/test_type_id.cpp
        test/src/test_type_info.cpp
)
target_include_directories(utl_tests PRIVATE test/include)
target_link_libraries(utl_tests PRIVATE utl)
target_compile_options(utl_tests PRIVATE -Wall -Wextra -pedantic)

enable_testing()
add_test(utl utl_tests)
