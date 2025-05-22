#include <gtest/gtest.h>
#include "SringBuffer.h"
#include <cstring>

class RingBufferTest : public ::testing::Test
{
protected:
    static constexpr int kBufferSize = 8;
    char rawBuffer[kBufferSize];
    SRingBuffer ring;

    void SetUp() override
    {
        std::memset(rawBuffer, 0, kBufferSize);
        RingInit(&ring, rawBuffer, kBufferSize);
    }
};

TEST_F(RingBufferTest, InitSetsCorrectDefaults)
{
    EXPECT_EQ(ring.ri, 0);
    EXPECT_EQ(ring.wi, 0);
    EXPECT_EQ(ring.TotalLen, 0);
    EXPECT_EQ(ring.MaxLen, kBufferSize);
    EXPECT_EQ(ring.buf, rawBuffer);
}

TEST_F(RingBufferTest, WriteIncreasesWriteIndexAndTotalLength)
{
    RingIncWi(&ring, 3);
    EXPECT_EQ(ring.wi, 3);
    EXPECT_EQ(ring.TotalLen, 3);
}

TEST_F(RingBufferTest, ReadIncreasesReadIndexAndDecreasesTotalLength)
{
    RingIncWi(&ring, 4);
    RingIncRi(&ring, 2);
    EXPECT_EQ(ring.ri, 2);
    EXPECT_EQ(ring.TotalLen, 2);
}

TEST_F(RingBufferTest, WriteWrapsAroundCorrectly)
{
    RingIncWi(&ring, kBufferSize);
    EXPECT_EQ(ring.wi, 0);
}

TEST_F(RingBufferTest, ReadWrapsAroundCorrectly)
{
    RingIncWi(&ring, kBufferSize);
    RingIncRi(&ring, kBufferSize);
    EXPECT_EQ(ring.ri, 0);
    EXPECT_EQ(ring.TotalLen, 0);
}

TEST_F(RingBufferTest, AvailableSpaceIsCorrect)
{
    RingIncWi(&ring, 6);
    EXPECT_EQ(RingAvailableSpace(&ring), 2);
}

TEST_F(RingBufferTest, DistancesAreCorrect)
{
    RingIncWi(&ring, 2);
    RingIncRi(&ring, 1);
    EXPECT_EQ(RingWBDistance(&ring), kBufferSize - 2);
    EXPECT_EQ(RingRBDistance(&ring), kBufferSize - 1);
}
