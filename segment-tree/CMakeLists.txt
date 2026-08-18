add_library(segment_tree segment_tree.cpp segment_tree.h)
target_include_directories(segment_tree PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(segment_tree_tests test_segment_tree.cpp)
target_link_libraries(segment_tree_tests PRIVATE segment_tree GTest::gtest_main)
gtest_discover_tests(segment_tree_tests)
