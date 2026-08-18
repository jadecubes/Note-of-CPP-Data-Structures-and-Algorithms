add_library(ring_buffer s_ring_buffer.cpp s_ring_buffer.h)
target_include_directories(ring_buffer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(ring_buffer_tests test_ring_buffer.cpp)
target_link_libraries(ring_buffer_tests PRIVATE ring_buffer GTest::gtest_main)
gtest_discover_tests(ring_buffer_tests)
