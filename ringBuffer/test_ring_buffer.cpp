#include "SRingBuffer.h"

#include <cstddef>
#include <cstring>

#include <gtest/gtest.h>

class RingBufferTest : public ::testing::Test {
protected:
  static constexpr std::size_t kBufferSize = 8;
  char rawBuffer[kBufferSize];
  SRingBuffer ring;

  void SetUp() override {
    std::memset(rawBuffer, 0, kBufferSize);
    RingInit(&ring, rawBuffer, kBufferSize);
  }
};

TEST_F(RingBufferTest, InitSetsCorrectDefaults) {
  EXPECT_EQ(ring.ri, 0);
  EXPECT_EQ(ring.wi, 0);
  EXPECT_EQ(ring.TotalLen, 0);
  EXPECT_EQ(ring.MaxLen, kBufferSize);
  EXPECT_EQ(ring.buf, rawBuffer);
}

TEST_F(RingBufferTest, WriteIncreasesWriteIndexAndTotalLength) {
  RingIncWi(&ring, 3);
  EXPECT_EQ(ring.wi, 3);
  EXPECT_EQ(ring.TotalLen, 3);
}

TEST_F(RingBufferTest, ReadIncreasesReadIndexAndDecreasesTotalLength) {
  RingIncWi(&ring, 4);
  RingIncRi(&ring, 2);
  EXPECT_EQ(ring.ri, 2);
  EXPECT_EQ(ring.TotalLen, 2);
}

TEST_F(RingBufferTest, WriteWrapsAroundCorrectly) {
  RingIncWi(&ring, kBufferSize);
  EXPECT_EQ(ring.wi, 0);
}

TEST_F(RingBufferTest, ReadWrapsAroundCorrectly) {
  RingIncWi(&ring, kBufferSize);
  RingIncRi(&ring, kBufferSize);
  EXPECT_EQ(ring.ri, 0);
  EXPECT_EQ(ring.TotalLen, 0);
}

TEST_F(RingBufferTest, MidBufferWrapKeepsRemainder) {
  // Wrap past the boundary (not exactly onto it): 6 + 5 = 11 -> index 3.
  RingIncWi(&ring, 6);
  RingIncRi(&ring, 6);
  RingIncWi(&ring, 5);
  EXPECT_EQ(ring.wi, 3);
  EXPECT_EQ(ring.TotalLen, 5);
  RingIncRi(&ring, 5);
  EXPECT_EQ(ring.ri, 3);
  EXPECT_EQ(ring.TotalLen, 0);
}

TEST_F(RingBufferTest, AvailableSpaceIsCorrect) {
  RingIncWi(&ring, 6);
  EXPECT_EQ(RingAvailableSpace(&ring), 2);
}

TEST_F(RingBufferTest, DistancesAreCorrect) {
  RingIncWi(&ring, 2);
  RingIncRi(&ring, 1);
  EXPECT_EQ(RingWBDistance(&ring), kBufferSize - 2);
  EXPECT_EQ(RingRBDistance(&ring), kBufferSize - 1);
}
