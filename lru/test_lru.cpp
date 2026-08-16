#include "Lru.h"

#include <stdexcept>

#include <gtest/gtest.h>

TEST(LruTest, GetMissingKeyReturnsMinusOne) {
  Lru cache(2);
  EXPECT_EQ(cache.get(1), -1);
}

TEST(LruTest, PutThenGetRoundTrips) {
  Lru cache(2);
  cache.put(1, 100);
  EXPECT_EQ(cache.get(1), 100);
}

TEST(LruTest, PutUpdatesExistingKey) {
  Lru cache(2);
  cache.put(1, 100);
  cache.put(1, 200);
  EXPECT_EQ(cache.get(1), 200);
}

TEST(LruTest, UpdatingKeyInFullCacheEvictsNothing) {
  Lru cache(2);
  cache.put(1, 100);
  cache.put(2, 200);
  cache.put(2, 222); // update in place: must not take the eviction path
  EXPECT_EQ(cache.get(1), 100);
  EXPECT_EQ(cache.get(2), 222);
}

TEST(LruTest, EvictsLeastRecentlyUsedWhenFull) {
  Lru cache(2);
  cache.put(1, 100);
  cache.put(2, 200);
  cache.put(3, 300); // evicts key 1
  EXPECT_EQ(cache.get(1), -1);
  EXPECT_EQ(cache.get(2), 200);
  EXPECT_EQ(cache.get(3), 300);
}

TEST(LruTest, GetRefreshesRecency) {
  Lru cache(2);
  cache.put(1, 100);
  cache.put(2, 200);
  EXPECT_EQ(cache.get(1), 100); // key 2 is now least recently used
  cache.put(3, 300);            // evicts key 2
  EXPECT_EQ(cache.get(2), -1);
  EXPECT_EQ(cache.get(1), 100);
}

TEST(LruTest, PutRefreshesRecency) {
  Lru cache(2);
  cache.put(1, 100);
  cache.put(2, 200);
  cache.put(1, 111); // key 2 is now least recently used
  cache.put(3, 300); // evicts key 2
  EXPECT_EQ(cache.get(2), -1);
  EXPECT_EQ(cache.get(1), 111);
}

TEST(LruTest, RemoveErasesKey) {
  Lru cache(2);
  cache.put(1, 100);
  cache.remove(1);
  EXPECT_EQ(cache.get(1), -1);
  cache.remove(42); // removing an absent key is a no-op
}

TEST(LruTest, RemovedSlotIsReusable) {
  Lru cache(2);
  cache.put(1, 100);
  cache.put(2, 200);
  cache.remove(1);
  cache.put(3, 300); // fits without evicting key 2
  EXPECT_EQ(cache.get(2), 200);
  EXPECT_EQ(cache.get(3), 300);
}

TEST(LruTest, NonPositiveCapacityThrows) {
  EXPECT_THROW(Lru(0), std::invalid_argument);
  EXPECT_THROW(Lru(-1), std::invalid_argument);
}
