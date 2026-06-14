cmake_minimum_required(VERSION 3.28.3)
project(Zappy CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SHARED
    shared
)

set(SRCS
    src/ArgsParser.cpp
    src/Connect.cpp
    src/Help.cpp
    src/Utils.cpp
    src/gui/GUIEvent.cpp
    src/gui/TileInfoEvent.cpp
)

set(HEADERS
    include/
    include/gui/
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

add_library(${SHARED} ${SRCS})
target_include_directories(${SHARED} PUBLIC ${HEADERS})
set_target_properties(${SHARED} PROPERTIES PREFIX "")
