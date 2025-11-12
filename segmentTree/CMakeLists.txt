# Template for CMakeLists.txt

add_library(
  segmentTree
  ./SegmentTree.cpp
  
)

target_include_directories(segmentTree PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})


