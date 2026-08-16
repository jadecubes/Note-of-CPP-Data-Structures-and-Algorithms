cmake_minimum_required(VERSION 3.24)

project(CppDataStructuresAndAlgorithms LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

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

add_subdirectory(findKClosest)
add_subdirectory(lru)
add_subdirectory(ringBuffer)
add_subdirectory(segmentTree)
add_subdirectory(topologicalSort)
