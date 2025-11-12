# Template for CMakeLists.txt

add_library(
  findKClosest
  ./FindKClosest.cpp
  
)

target_include_directories(findKClosest PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})


