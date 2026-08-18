#include "segment_tree.h"

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

TEST(SegmentTreeTest, LowerUpdateOnSameNodeDoesNotOverwrite) {
  // Identical range: both updates land on the same covering node, so a
  // plain assignment (instead of max) would regress query to 3.
  SegmentTree tree(8);
  tree.update(0, 7, 5);
  tree.update(0, 7, 3);
  EXPECT_EQ(tree.query(0), 5);
  EXPECT_EQ(tree.query(7), 5);
}

TEST(SegmentTreeTest, SingleElementRangeUpdate) {
  SegmentTree tree(4);
  tree.update(1, 1, 7);
  EXPECT_EQ(tree.query(0), 0);
  EXPECT_EQ(tree.query(1), 7);
}

TEST(SegmentTreeTest, NonPowerOfTwoSize) {
  // A partial interior range on n=5 forces recursion through the uneven
  // [0,4] -> [0,2],[3,4] splits (full-range updates stop at the root and
  // would not exercise the padded tree at all).
  SegmentTree tree(5); // internal leaf count rounds up to 8
  tree.update(1, 3, 4);
  EXPECT_EQ(tree.query(0), 0);
  EXPECT_EQ(tree.query(1), 4);
  EXPECT_EQ(tree.query(2), 4);
  EXPECT_EQ(tree.query(3), 4);
  EXPECT_EQ(tree.query(4), 0);
}

TEST(SegmentTreeTest, OutOfRangeAccessThrows) {
  SegmentTree tree(5);
  // query is [[nodiscard]]; the cast says the throw is what is under test.
  EXPECT_THROW((void)tree.query(-1), std::out_of_range);
  EXPECT_THROW((void)tree.query(5), std::out_of_range);
  EXPECT_THROW(tree.update(-1, 3, 1), std::out_of_range);
  EXPECT_THROW(tree.update(0, 5, 1), std::out_of_range);
  EXPECT_THROW(tree.update(3, 2, 1), std::out_of_range); // L > R
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
