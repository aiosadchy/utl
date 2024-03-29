################################################################################
#                                     utl                                      #
################################################################################

cmake_minimum_required (VERSION 3.8)
project(utl
    VERSION         0.1.0
    DESCRIPTION     "A simple general purpose utility library for modern C++"
    HOMEPAGE_URL    "https://github.com/aiosadchy/utl"
)


################################################################################
#                                   options                                    #
################################################################################

option(
    UTL_NO_UNSCOPED_MACROS
    "Do not re-define library macros without 'UTL' prefix"
    OFF
)

option(
    UTL_DO_NOT_USE_COUNTER_MACRO
    "Do not allow use of '__COUNTER__' macro in library code"
    OFF
)

option(
    UTL_BUILD_TESTS
    "Build library tests"
    OFF
)


################################################################################
#                                   library                                    #
################################################################################

add_library(utl INTERFACE)
target_include_directories(utl INTERFACE include)
target_compile_features(utl INTERFACE cxx_std_17)

set(UTL_COMPILE_DEFINITIONS)

function(msg level)
    message(${level} "utl: " ${ARGN})
endfunction()

if (UTL_NO_UNSCOPED_MACROS)
    set(UTL_COMPILE_DEFINITIONS ${UTL_COMPILE_DEFINITIONS} UTL_NO_UNSCOPED_MACROS)
    msg(STATUS "unscoped macros are disabled")
endif()

if (UTL_DO_NOT_USE_COUNTER_MACRO)
    set(UTL_COMPILE_DEFINITIONS ${UTL_COMPILE_DEFINITIONS} UTL_DO_NOT_USE_COUNTER_MACRO)
    msg(STATUS "do not allow use of '__COUNTER__' macro in library code")
endif()

target_compile_definitions(utl INTERFACE ${UTL_COMPILE_DEFINITIONS})


################################################################################
#                                    tests                                     #
################################################################################

if (UTL_BUILD_TESTS)
    msg(STATUS "tests are enabled")

    enable_testing()

    set(UTL_TEST_SOURCES
        test/src/utl/default_copyable.cpp
        test/src/utl/default_movable.cpp
        test/src/utl/hash.cpp
        test/src/utl/non_constructible.cpp
        test/src/utl/non_copyable.cpp
        test/src/utl/range.cpp
        test/src/utl/repeat.cpp
        test/src/utl/scope_guard.cpp
        test/src/utl/static_block.cpp
        test/src/utl/string_literal.cpp
        test/src/utl/timer.cpp
        test/src/utl/type_id.cpp
        test/src/utl/type_info.cpp
        test/src/utl/type_traits.cpp
    )

    foreach(TEST ${UTL_TEST_SOURCES})
        get_filename_component(TEST_BASE_NAME ${TEST} NAME_WE)
        set(TEST_EXE test_utl_${TEST_BASE_NAME})
        add_executable(${TEST_EXE} ${TEST} test/src/main.cpp)
        target_include_directories(${TEST_EXE} PRIVATE test/include)
        target_link_libraries(${TEST_EXE} PRIVATE utl)

        if(MSVC)
            target_compile_options(${TEST_EXE} PRIVATE /W4 /WX)
        else()
            target_compile_options(${TEST_EXE} PRIVATE -Wall -Wextra -pedantic -Werror)
        endif()

        add_test(${TEST_EXE} ${TEST_EXE})
    endforeach()

endif()
