cmake_minimum_required(VERSION 3.14.0)

include(FetchContent)

find_package(raylib_cpp QUIET)

if (NOT raylib_cpp_FOUND)
    FetchContent_Declare(raylib_cpp
        GIT_REPOSITORY https://github.com/RobLoach/raylib-cpp.git
        GIT_TAG be4b64941aa12b35974c2de94af9e2f62732f9af # 2022-07-11
    )
    FetchContent_MakeAvailable(raylib_cpp)
endif()