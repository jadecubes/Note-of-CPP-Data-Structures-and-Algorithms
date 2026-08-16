add_library(lru Lru.cpp Lru.h)
target_include_directories(lru PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(lru_tests test_lru.cpp)
target_link_libraries(lru_tests PRIVATE lru GTest::gtest_main)
gtest_discover_tests(lru_tests)
