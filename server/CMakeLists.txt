cmake_minimum_required(VERSION 3.28.3)
project(Zappy CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SHARED_SRCS
    Connect.cpp
    Utils.cpp
    ArgsParser.cpp
    Help.cpp
)

list(TRANSFORM SHARED_SRCS PREPEND ${CMAKE_SOURCE_DIR}/shared/src/)

set(MAIN
    src/Main.cpp
)

set(SRCS
    src/Server.cpp
    src/AIClient.cpp
    src/GUIClient.cpp
    src/Environement.cpp
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

add_executable(zappy_server ${MAIN} ${SRCS} ${SHARED_SRCS})

find_library(CRITERION criterion REQUIRED)

set(SRCS_TESTS
    tests/tests_init.cpp
    tests/tests_args.cpp
)

add_executable(server_tests_run_bin EXCLUDE_FROM_ALL ${SRCS_TESTS} ${SRCS} ${SHARED_SRCS})

target_compile_options(server_tests_run_bin PRIVATE --coverage)
target_link_options(server_tests_run_bin PRIVATE --coverage)
target_link_libraries(server_tests_run_bin criterion )

add_custom_target(server_tests_run
    COMMAND find ${CMAKE_BINARY_DIR} -name "*.gcda" -delete
    COMMAND ./server_tests_run_bin
    DEPENDS server_tests_run_bin
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)
