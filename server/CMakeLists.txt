cmake_minimum_required(VERSION 3.28.3)
project(Zappy CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(MAIN
        src/Main.cpp
)

set(SRCS
        src/Server.cpp
        src/AIClient.cpp
        src/GUIClient.cpp
        src/Environement.cpp
        src/master/Master.cpp
)

set(HEADERS
        include/
        include/master/
)

include_directories(${HEADERS})

option(ENABLE_ASAN "Enable Address Sanitizer" OFF)

if (ENABLE_ASAN)
    set(ASAN_FLAGS -fsanitize=address -fno-omit-frame-pointer)
    add_compile_options(${ASAN_FLAGS})
    add_link_options(${ASAN_FLAGS})
endif ()


# criterion
find_package(criterion QUIET)
if (NOT criterion_FOUND)
    if (NOT DEFINED CRITERION_VERSION)
        set(CRITERION_VERSION v2.4.2)
    endif ()
    include(FetchContent)
    FetchContent_Declare(
            criterion
            GIT_REPOSITORY https://github.com/Snaipe/Criterion.git
            GIT_TAG ${CRITERION_VERSION}
    )
    FetchContent_MakeAvailable(criterion)
endif ()

add_executable(zappy_server ${MAIN} ${SRCS})
target_link_libraries(zappy_server shared)

find_library(CRITERION criterion REQUIRED)

set(SRCS_TESTS
        tests/tests_init.cpp
        tests/tests_args.cpp
)

add_executable(server_tests_run_bin EXCLUDE_FROM_ALL ${SRCS_TESTS} ${SRCS})

target_compile_options(server_tests_run_bin PRIVATE --coverage)
target_link_options(server_tests_run_bin PRIVATE --coverage)
target_link_libraries(server_tests_run_bin criterion shared)

add_custom_target(server_tests_run
        COMMAND find ${CMAKE_BINARY_DIR} -name "*.gcda" -delete
        COMMAND ./server_tests_run_bin
        DEPENDS server_tests_run_bin
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)
