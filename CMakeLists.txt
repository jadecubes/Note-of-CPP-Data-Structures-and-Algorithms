cmake_minimum_required(VERSION 3.24)

project(CppDataStructuresAndAlgorithms LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# For clangd / VS Code IntelliSense (.vscode/c_cpp_properties.json reads it).
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

enable_testing()

# GoogleTest, pinned by hash so every machine and CI runner builds the same
# thing (no dependence on a locally installed copy).
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.tar.gz
  URL_HASH SHA256=7b42b4d6ed48810c5362c265a17faebe90dc2373c885e5216439d37927f02926)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
include(GoogleTest)

# Warnings for this project's own code. Deliberately set *after* GoogleTest
# is pulled in: add_compile_options only reaches targets declared later, so
# the vendored sources keep their own flags and stay quiet.
option(WARNINGS_AS_ERRORS "Treat compiler warnings as errors (used by CI)" OFF)
if(MSVC)
  add_compile_options(/W4)
  if(WARNINGS_AS_ERRORS)
    add_compile_options(/WX)
  endif()
else()
  add_compile_options(-Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion
                      -Wshadow)
  if(WARNINGS_AS_ERRORS)
    add_compile_options(-Werror)
  endif()
endif()

add_subdirectory(findKClosest)
add_subdirectory(lru)
add_subdirectory(ringBuffer)
add_subdirectory(segmentTree)
add_subdirectory(topologicalSort)
