add_library(topological_sort graph.cpp graph.h)
target_include_directories(topological_sort PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(topological_sort_tests test_graph.cpp)
target_link_libraries(topological_sort_tests PRIVATE topological_sort GTest::gtest_main)
gtest_discover_tests(topological_sort_tests)
