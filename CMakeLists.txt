cmake_minimum_required(VERSION 3.14)

include(cmake/prelude.cmake)

project(
    sandbox
    VERSION 0.1.0
    DESCRIPTION "sandbox game"
    HOMEPAGE_URL "https://github.com/bensuperpc"
    LANGUAGES CXX
)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(cmake/project-is-top-level.cmake)
include(cmake/variables.cmake)

# set(OpenGL_GL_PREFERENCE GLVND)

# ---- Enable Utile ----
include(cmake/utile/ccache.cmake)
# include(cmake/utile/lto.cmake)
# include(cmake/utile/ninja_color.cmake)
# include(cmake/lib/backward-cpp.cmake)

# ---- Download and install dependencies

# ---- Enable Utile ----
find_package(OpenMP 3.0)

set(FETCHCONTENT_BASE_DIR "${CMAKE_BINARY_DIR}/3rd-party" CACHE BOOL "" FORCE)
set(FETCHCONTENT_QUIET FALSE CACHE BOOL "" FORCE)

include(cmake/lib/raylib.cmake)
include(cmake/lib/raygui.cmake)
include(cmake/lib/raylib-cpp.cmake)
include(cmake/lib/vector.cmake)

# ---- Declare library ----

add_library(
    sandbox_lib OBJECT
    source/lib.cpp
)

target_include_directories(
    sandbox_lib ${warning_guard}
    PUBLIC
    "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/source>"
)

target_compile_features(sandbox_lib PUBLIC cxx_std_20)

# ---- Declare executable ----

add_executable(sandbox_exe source/main.cpp)
add_executable(sandbox::exe ALIAS sandbox_exe)

set_target_properties(
    sandbox_exe PROPERTIES
    OUTPUT_NAME sandbox
    EXPORT_NAME exe
)

target_compile_features(sandbox_exe PRIVATE cxx_std_20)

target_link_libraries(sandbox_exe PRIVATE sandbox_lib)

target_link_libraries(sandbox_exe PRIVATE vector::vector raylib raylib_cpp)

# ---- Install rules ----

if(NOT CMAKE_SKIP_INSTALL_RULES)
  include(cmake/install-rules.cmake)
endif()

# ---- Developer mode ----

if(NOT sandbox_DEVELOPER_MODE)
  return()
elseif(NOT PROJECT_IS_TOP_LEVEL)
  message(
      AUTHOR_WARNING
      "Developer mode is intended for developers of sandbox"
  )
endif()

include(cmake/dev-mode.cmake)
