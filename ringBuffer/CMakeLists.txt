# Template for CMakeLists.txt

add_library(
  ringBuffer
  ./SringBuffer.cpp
  ./SringBuffer.h
)

target_include_directories(ringBuffer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(
  ringBuffer_tests
  ./test_ring_buffer.cpp
)
set(GTEST_ROOT "${CMAKE_SOURCE_DIR}/external/gtest")
set(CMAKE_PREFIX_PATH "${GTEST_ROOT}")
target_link_libraries(ringBuffer_tests
  ringBuffer
  GTest::gtest
  GTest::gtest_main
)
include(GoogleTest)
gtest_discover_tests(ringBuffer_tests)
