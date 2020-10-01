cmake_minimum_required (VERSION 3.8)
project(utl
        VERSION         0.0.1
        DESCRIPTION     "A simple general purpose utility library for modern C++"
        HOMEPAGE_URL    "https://github.com/aiosadchy/utl"
)

add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(utl INTERFACE include)
target_compile_features(${PROJECT_NAME} INTERFACE cxx_std_17)

set(TEST_PROJECT_NAME ${PROJECT_NAME}_test)
add_executable(${TEST_PROJECT_NAME}
        test/test_main.cpp
)
target_link_libraries(${TEST_PROJECT_NAME} utl)