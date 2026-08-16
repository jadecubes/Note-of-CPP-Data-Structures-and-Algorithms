add_library(findKClosest FindKClosest.cpp FindKClosest.h)
target_include_directories(findKClosest PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(findKClosest_tests test_find_k_closest.cpp)
target_link_libraries(findKClosest_tests PRIVATE findKClosest GTest::gtest_main)
gtest_discover_tests(findKClosest_tests)
