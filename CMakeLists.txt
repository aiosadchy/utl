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
    UTL_UNSCOPED_MACROS
    "Define macros without 'UTL' prefix"
    OFF
)

option(
    UTL_USE_COUNTER_MACRO
    "Allow use of '__COUNTER__' macro in library code"
    OFF
)

option(
    UTL_BUILD_TESTS
    "Build library tests"
    ON
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

if (UTL_UNSCOPED_MACROS)
    set(UTL_COMPILE_DEFINITIONS ${UTL_COMPILE_DEFINITIONS} UTL_UNSCOPED_MACROS)
    msg(STATUS "define unscoped macros")
endif()

if (UTL_USE_COUNTER_MACRO)
    set(UTL_COMPILE_DEFINITIONS ${UTL_COMPILE_DEFINITIONS} UTL_USE_COUNTER_MACRO)
    msg(STATUS "allow using '__COUNTER__' macro in library code")
endif()

target_compile_definitions(utl INTERFACE ${UTL_COMPILE_DEFINITIONS})


################################################################################
#                                    tests                                     #
################################################################################

if (UTL_BUILD_TESTS)
    msg(STATUS "tests are enabled")

    enable_testing()

    set(UTL_TEST_SOURCES
        test/src/main.cpp
        test/src/test_non_constructible.cpp
        test/src/test_non_copyable.cpp
        test/src/test_range.cpp
        test/src/test_repeat.cpp
        test/src/test_scope_guard.cpp
        test/src/test_static_block.cpp
        test/src/test_type_id.cpp
        test/src/test_type_info.cpp
        test/src/test_type_traits.cpp
    )

    foreach(TEST ${UTL_TEST_SOURCES})
        get_filename_component(TEST_EXE ${TEST} NAME_WE)
        add_executable(${TEST_EXE} ${TEST})
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
