add_library(ringBuffer SRingBuffer.cpp SRingBuffer.h)
target_include_directories(ringBuffer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(ringBuffer_tests test_ring_buffer.cpp)
target_link_libraries(ringBuffer_tests PRIVATE ringBuffer GTest::gtest_main)
gtest_discover_tests(ringBuffer_tests)
