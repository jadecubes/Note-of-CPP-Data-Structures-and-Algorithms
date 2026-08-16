add_library(topologicalSort Graph.cpp Graph.h)
target_include_directories(topologicalSort PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(topologicalSort_tests test_graph.cpp)
target_link_libraries(topologicalSort_tests PRIVATE topologicalSort GTest::gtest_main)
gtest_discover_tests(topologicalSort_tests)
