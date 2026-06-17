cmake_minimum_required(VERSION 3.28.3)
project(Zappy CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

list(TRANSFORM SHARED_SRCS PREPEND ${CMAKE_SOURCE_DIR}/shared/src/)

set(MAIN
        src/Main.cpp
)

set(SRCS
        src/graphics/GameObject.cpp
        src/graphics/UiObject.cpp
        src/graphics/Transformable3D.cpp
        src/graphics/Transformable2D.cpp
        src/graphics/Scene.cpp
        src/graphics/Camera.cpp
        src/graphics/primitives/Model.cpp
        src/graphics/primitives/Text2D.cpp
        src/Window.cpp
        src/GUI.cpp
        src/Assets.cpp
        src/elements/Player.cpp
        src/elements/Egg.cpp
        src/elements/Resource.cpp
        src/elements/Tile.cpp
        src/elements/Map.cpp
        src/elements/Elevation.cpp
        src/elements/Environement.cpp
        src/elements/Events.cpp
)

set(HEADERS
        include/elements/
        include/
        src/
)

include_directories(${HEADERS})

option(ENABLE_ASAN "Enable Address Sanitizer" OFF)

if (ENABLE_ASAN)
    set(ASAN_FLAGS -fsanitize=address -fno-omit-frame-pointer)
    add_compile_options(${ASAN_FLAGS})
    add_link_options(${ASAN_FLAGS})
endif ()

# raylib
find_package(raylib QUIET)
if (NOT raylib_FOUND)
    include(FetchContent)
    FetchContent_Declare(
            raylib
            GIT_REPOSITORY https://github.com/raysan5/raylib.git
            GIT_TAG 6.0
            GIT_SHALLOW 1
    )
    FetchContent_MakeAvailable(raylib)
endif ()

# raylib-cpp
find_package(raylib_cpp QUIET)
if (NOT raylib_cpp_FOUND)
    if (NOT DEFINED RAYLIB_CPP_VERSION)
        set(RAYLIB_CPP_VERSION v6.0.0)
    endif ()
    include(FetchContent)
    FetchContent_Declare(
            raylib_cpp
            GIT_REPOSITORY https://github.com/RobLoach/raylib-cpp.git
            GIT_TAG ${RAYLIB_CPP_VERSION}
    )
    FetchContent_MakeAvailable(raylib_cpp)
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

add_executable(zappy_gui ${MAIN} ${SRCS})
target_link_libraries(zappy_gui raylib raylib_cpp shared)

target_compile_options(zappy_gui PRIVATE)

include(CTest)
enable_testing()

find_library(CRITERION criterion REQUIRED)

set(SRCS_TESTS
        tests/tests_init.cpp
)

add_executable(gui_tests_run_bin EXCLUDE_FROM_ALL ${SRCS_TESTS} ${SRCS})

target_compile_options(gui_tests_run_bin PRIVATE --coverage)
target_link_options(gui_tests_run_bin PRIVATE --coverage)
target_link_libraries(gui_tests_run_bin criterion raylib raylib_cpp shared)

add_custom_target(remove_coverage
        COMMAND find ${CMAKE_BINARY_DIR} -name "*.gc*" -delete
)

add_custom_target(gui_tests_run
        COMMAND ./gui_tests_run_bin
        DEPENDS gui_tests_run_bin
        DEPENDS remove_coverage
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)

add_custom_target(gui_all_tests
        DEPENDS remove_coverage gui_tests_run_bin
)

add_test(NAME gui_unit_tests COMMAND $<TARGET_FILE:gui_tests_run_bin>)
