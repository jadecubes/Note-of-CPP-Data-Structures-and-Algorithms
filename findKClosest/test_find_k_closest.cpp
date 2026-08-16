#include "FindKClosest.h"

#include <limits>
#include <vector>

#include <gtest/gtest.h>

TEST(FindKClosestTest, TargetInsideArray) {
  EXPECT_EQ(findClosestElements({1, 2, 3, 4, 5}, 4, 3),
            (std::vector<int>{1, 2, 3, 4}));
}

TEST(FindKClosestTest, TargetBelowRange) {
  EXPECT_EQ(findClosestElements({1, 2, 3, 4, 5}, 4, -1),
            (std::vector<int>{1, 2, 3, 4}));
}

TEST(FindKClosestTest, TargetAboveRange) {
  EXPECT_EQ(findClosestElements({1, 2, 3, 4, 5}, 2, 100),
            (std::vector<int>{4, 5}));
}

TEST(FindKClosestTest, TiePrefersSmallerElement) {
  // 3 and 5 are equally close to 4; the smaller element wins.
  EXPECT_EQ(findClosestElements({1, 3, 5, 7}, 1, 4), (std::vector<int>{3}));
}

TEST(FindKClosestTest, DuplicatesInArray) {
  EXPECT_EQ(findClosestElements({1, 1, 2, 2, 2, 3}, 3, 2),
            (std::vector<int>{2, 2, 2}));
}

TEST(FindKClosestTest, KEqualsArraySize) {
  EXPECT_EQ(findClosestElements({1, 2, 3}, 3, 9), (std::vector<int>{1, 2, 3}));
}

TEST(FindKClosestTest, KLargerThanArrayReturnsWholeArray) {
  EXPECT_EQ(findClosestElements({1, 2}, 5, 0), (std::vector<int>{1, 2}));
}

TEST(FindKClosestTest, NonPositiveKReturnsEmpty) {
  EXPECT_TRUE(findClosestElements({1, 2, 3}, 0, 2).empty());
  EXPECT_TRUE(findClosestElements({1, 2, 3}, -1, 2).empty());
}

TEST(FindKClosestTest, EmptyArrayReturnsEmpty) {
  EXPECT_TRUE(findClosestElements({}, 3, 5).empty());
}

TEST(FindKClosestTest, ExtremeValuesDoNotOverflow) {
  // With int distance arithmetic, both subtractions overflow (UB) and the
  // farthest window is returned instead of the closest.
  const int kMax = std::numeric_limits<int>::max();
  const int kMin = std::numeric_limits<int>::min();
  EXPECT_EQ(findClosestElements({kMin, kMin + 1, kMax - 1, kMax}, 2, kMax),
            (std::vector<int>{kMax - 1, kMax}));
  EXPECT_EQ(findClosestElements({kMin, kMin + 1, kMax - 1, kMax}, 2, kMin),
            (std::vector<int>{kMin, kMin + 1}));
}
