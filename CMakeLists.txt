cmake_minimum_required (VERSION 3.8)
project(utl
        VERSION         0.0.1
        DESCRIPTION     "A simple general purpose utility library for modern C++"
        HOMEPAGE_URL    "https://github.com/aiosadchy/utl"
)

# utl library

option(UTL_UNSCOPED_MACROS "Define macros without 'UTL' prefix" ON)

set(LIBRARY_NAME utl)
add_library(${LIBRARY_NAME} INTERFACE)
target_include_directories(${LIBRARY_NAME} INTERFACE include)
target_compile_features(${LIBRARY_NAME} INTERFACE cxx_std_17)

if (UTL_UNSCOPED_MACROS)
    target_compile_definitions(${LIBRARY_NAME} INTERFACE UTL_UNSCOPED_MACROS)
endif()

# tests

set(TEST_PROJECT_NAME ${LIBRARY_NAME}_test)
add_executable(${TEST_PROJECT_NAME}
        test/main.cpp
)
target_link_libraries(${TEST_PROJECT_NAME} ${LIBRARY_NAME})
target_compile_options(${TEST_PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic)
