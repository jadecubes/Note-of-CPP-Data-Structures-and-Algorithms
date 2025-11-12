# Template for CMakeLists.txt

add_library(
  topologicalSort
  ./Graph.cpp
  
)

target_include_directories(topologicalSort PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})


