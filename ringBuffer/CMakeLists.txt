add_library(RingBuffer
  SringBuffer.cpp
  SringBuffer.h
)

target_include_directories(RingBuffer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(RingBuffer_tests
  test_ring_buffer.cpp
)
set(GTEST_ROOT "${CMAKE_SOURCE_DIR}/external/gtest")
set(CMAKE_PREFIX_PATH "${GTEST_ROOT}")
target_link_libraries(RingBuffer_tests
  RingBuffer
  GTest::gtest
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(RingBuffer_tests)
