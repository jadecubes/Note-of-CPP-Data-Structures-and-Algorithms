add_library(segmentTree SegmentTree.cpp SegmentTree.h)
target_include_directories(segmentTree PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(segmentTree_tests test_segment_tree.cpp)
target_link_libraries(segmentTree_tests PRIVATE segmentTree GTest::gtest_main)
gtest_discover_tests(segmentTree_tests)
