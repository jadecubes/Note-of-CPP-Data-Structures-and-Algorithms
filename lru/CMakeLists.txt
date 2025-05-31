add_library(
  Lru
  Lru.cpp
  Lru.h
)

target_include_directories(Lru PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

set(GTEST_ROOT "${CMAKE_SOURCE_DIR}/external/gtest")
set(CMAKE_PREFIX_PATH "${GTEST_ROOT}")

