#include "SegmentTree.h"

#include <stdexcept>

#include <gtest/gtest.h>

TEST(SegmentTreeTest, FreshTreeQueriesZero) {
  SegmentTree tree(8);
  for (int i = 0; i < 8; ++i) {
    EXPECT_EQ(tree.query(i), 0);
  }
}

TEST(SegmentTreeTest, RangeUpdateRaisesOnlyCoveredIndices) {
  SegmentTree tree(8);
  tree.update(2, 5, 10);
  EXPECT_EQ(tree.query(1), 0);
  EXPECT_EQ(tree.query(2), 10);
  EXPECT_EQ(tree.query(5), 10);
  EXPECT_EQ(tree.query(6), 0);
}

TEST(SegmentTreeTest, OverlappingUpdatesKeepMaximum) {
  SegmentTree tree(8);
  tree.update(0, 7, 5);
  tree.update(2, 4, 3); // lower than 5: no visible effect
  tree.update(3, 3, 9);
  EXPECT_EQ(tree.query(2), 5);
  EXPECT_EQ(tree.query(3), 9);
  EXPECT_EQ(tree.query(4), 5);
}

TEST(SegmentTreeTest, SingleElementRangeUpdate) {
  SegmentTree tree(4);
  tree.update(1, 1, 7);
  EXPECT_EQ(tree.query(0), 0);
  EXPECT_EQ(tree.query(1), 7);
}

TEST(SegmentTreeTest, NonPowerOfTwoSize) {
  SegmentTree tree(5); // internal leaf count rounds up to 8
  tree.update(0, 4, 2);
  EXPECT_EQ(tree.query(0), 2);
  EXPECT_EQ(tree.query(4), 2);
}

TEST(SegmentTreeTest, SizeOneTree) {
  SegmentTree tree(1);
  EXPECT_EQ(tree.query(0), 0);
  tree.update(0, 0, 3);
  EXPECT_EQ(tree.query(0), 3);
}

TEST(SegmentTreeTest, NonPositiveSizeThrows) {
  EXPECT_THROW(SegmentTree(0), std::invalid_argument);
  EXPECT_THROW(SegmentTree(-4), std::invalid_argument);
}
