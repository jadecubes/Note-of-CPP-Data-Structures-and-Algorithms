# Template for CMakeLists.txt

add_library(
  lru
  ./Lru.cpp
  ./Lru.h
)

target_include_directories(lru PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})


