cmake_minimum_required(VERSION 3.28.3)
project(Zappy CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SHARED_SRCS
    Connect.cpp
    Utils.cpp
    Help.cpp
    ArgsParser.cpp
)

list(TRANSFORM SHARED_SRCS PREPEND ${CMAKE_SOURCE_DIR}/shared/src/)

set(MAIN
    src/Main.cpp
)

set(SRCS
    src/GUI.cpp
)

set(HEADERS
    include/
)

include_directories(${HEADERS})

option(ENABLE_ASAN "Enable Address Sanitizer" OFF)

if (ENABLE_ASAN)
    set(ASAN_FLAGS -fsanitize=address -fno-omit-frame-pointer)
    add_compile_options(${ASAN_FLAGS})
    add_link_options(${ASAN_FLAGS})
endif()

add_executable(zappy_gui ${MAIN} ${SRCS} ${SHARED_SRCS})

target_compile_options(zappy_gui PRIVATE)

find_library(CRITERION criterion REQUIRED)

set(SRCS_TESTS
    tests/tests_init.cpp
)

add_executable(gui_tests_run_bin EXCLUDE_FROM_ALL ${SRCS_TESTS} ${SRCS} ${SHARED_SRCS})

target_compile_options(gui_tests_run_bin PRIVATE --coverage)
target_link_options(gui_tests_run_bin PRIVATE --coverage)
target_link_libraries(gui_tests_run_bin criterion )

add_custom_target(gui_tests_run
    COMMAND find ${CMAKE_BINARY_DIR} -name "*.gcda" -delete
    COMMAND ./gui_tests_run_bin
    DEPENDS gui_tests_run_bin
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)
