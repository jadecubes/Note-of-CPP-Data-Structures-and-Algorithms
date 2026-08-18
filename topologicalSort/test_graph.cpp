#include "Graph.h"

#include <algorithm>
#include <cstddef>
#include <random>
#include <unordered_map>
#include <utility>
#include <vector>

#include <gtest/gtest.h>

TEST(GraphTest, SortsSimpleDag) {
  Graph g({0, 1, 2, 3});
  g.addEdge(0, 1);
  g.addEdge(0, 2);
  g.addEdge(1, 3);
  g.addEdge(2, 3);
  EXPECT_EQ(g.topologicalSortDfs(), (std::vector<int>{0, 1, 2, 3}));
  EXPECT_EQ(g.topologicalSortBfs(), (std::vector<int>{0, 1, 2, 3}));
}

TEST(GraphTest, OrderingIsLexicographicallySmallest) {
  // Both 3->... chains are valid before 1, but 1 has no prerequisites and is
  // smaller, so it must come first in the smallest ordering.
  Graph g({1, 2, 3});
  g.addEdge(3, 2);
  EXPECT_EQ(g.topologicalSortBfs(), (std::vector<int>{1, 3, 2}));
  EXPECT_EQ(g.topologicalSortDfs(), (std::vector<int>{1, 3, 2}));
}

TEST(GraphTest, NonContiguousVertexLabels) {
  Graph g({50, 10, 30});
  g.addEdge(50, 10);
  g.addEdge(10, 30);
  EXPECT_EQ(g.topologicalSortBfs(), (std::vector<int>{50, 10, 30}));
  EXPECT_EQ(g.topologicalSortDfs(), (std::vector<int>{50, 10, 30}));
}

TEST(GraphTest, CycleReturnsEmptyFromBoth) {
  Graph g({0, 1, 2});
  g.addEdge(0, 1);
  g.addEdge(1, 2);
  g.addEdge(2, 0);
  EXPECT_TRUE(g.topologicalSortDfs().empty());
  EXPECT_TRUE(g.topologicalSortBfs().empty());
}

TEST(GraphTest, CycleWithAcyclicPartStillReturnsEmpty) {
  // Vertex 0 is isolated and 1->2->3->1 is a cycle. The BFS variant only
  // notices this cycle via its final size check (0 does get processed), so
  // this pins that check specifically.
  Graph g({0, 1, 2, 3});
  g.addEdge(1, 2);
  g.addEdge(2, 3);
  g.addEdge(3, 1);
  EXPECT_TRUE(g.topologicalSortDfs().empty());
  EXPECT_TRUE(g.topologicalSortBfs().empty());
}

TEST(GraphTest, SelfLoopIsACycle) {
  Graph g({0, 1});
  g.addEdge(1, 1);
  EXPECT_TRUE(g.topologicalSortDfs().empty());
  EXPECT_TRUE(g.topologicalSortBfs().empty());
}

TEST(GraphTest, EdgeToUndeclaredVertexRegistersIt) {
  // 99 was never passed to the constructor; addEdge must register it so
  // both variants agree instead of DFS emitting it while BFS reports a
  // phantom cycle.
  Graph g({0, 1});
  g.addEdge(0, 1);
  g.addEdge(1, 99);
  EXPECT_EQ(g.topologicalSortDfs(), (std::vector<int>{0, 1, 99}));
  EXPECT_EQ(g.topologicalSortBfs(), (std::vector<int>{0, 1, 99}));
}

TEST(GraphTest, DuplicateConstructorLabelsAreIgnored) {
  Graph g({1, 1, 2});
  g.addEdge(1, 2);
  EXPECT_EQ(g.topologicalSortDfs(), (std::vector<int>{1, 2}));
  EXPECT_EQ(g.topologicalSortBfs(), (std::vector<int>{1, 2}));
}

TEST(GraphTest, DisconnectedVerticesAppearInOrder) {
  Graph g({4, 2, 7});
  EXPECT_EQ(g.topologicalSortBfs(), (std::vector<int>{2, 4, 7}));
  EXPECT_EQ(g.topologicalSortDfs(), (std::vector<int>{2, 4, 7}));
}

TEST(GraphTest, DfsPushesSmallNeighborLast) {
  // The classic trap for DFS-based lexicographic ordering: with ascending
  // visits this would come out 3,2,1.
  Graph g({1, 2, 3});
  g.addEdge(3, 1);
  g.addEdge(3, 2);
  EXPECT_EQ(g.topologicalSortDfs(), (std::vector<int>{3, 1, 2}));
  EXPECT_EQ(g.topologicalSortBfs(), (std::vector<int>{3, 1, 2}));
}

TEST(GraphTest, EmptyGraph) {
  Graph g({});
  EXPECT_TRUE(g.topologicalSortDfs().empty());
  EXPECT_TRUE(g.topologicalSortBfs().empty());
}

namespace {

// True iff order is a permutation of labels respecting every edge.
bool isValidTopologicalOrder(const std::vector<int> &order,
                             const std::vector<int> &labels,
                             const std::vector<std::pair<int, int>> &edges) {
  if (order.size() != labels.size()) {
    return false;
  }
  std::unordered_map<int, std::size_t> pos;
  for (std::size_t i = 0; i < order.size(); ++i) {
    pos[order[i]] = i;
  }
  for (int label : labels) {
    if (pos.count(label) == 0) {
      return false;
    }
  }
  for (const auto &[u, v] : edges) {
    if (pos[u] >= pos[v]) {
      return false;
    }
  }
  return true;
}

} // namespace

// On random DAGs: both variants must return valid orders, and the BFS
// (Kahn + min-heap) result — the provably lexicographically smallest one —
// must never be beaten by the DFS result. The two may legitimately differ;
// see Readme.md for why no DFS can guarantee the smallest ordering.
TEST(GraphTest, RandomDagsProduceValidOrdersAndBfsIsSmallest) {
  std::mt19937 rng(20260816); // fixed seed: deterministic test
  for (int trial = 0; trial < 500; ++trial) {
    const std::size_t n = 2 + static_cast<std::size_t>(rng() % 7);

    // Random distinct labels, not necessarily contiguous.
    std::vector<int> labels(n);
    for (std::size_t i = 0; i < n; ++i) {
      labels[i] = static_cast<int>(i) * 3 + static_cast<int>(rng() % 3);
    }
    std::shuffle(labels.begin(), labels.end(), rng);

    // Edges only from earlier to later shuffle positions: guaranteed acyclic.
    Graph g(labels);
    std::vector<std::pair<int, int>> edges;
    for (std::size_t i = 0; i < n; ++i) {
      for (std::size_t j = i + 1; j < n; ++j) {
        if (rng() % 3 == 0) {
          g.addEdge(labels[i], labels[j]);
          edges.emplace_back(labels[i], labels[j]);
        }
      }
    }

    std::vector<int> bfs = g.topologicalSortBfs();
    std::vector<int> dfs = g.topologicalSortDfs();
    ASSERT_TRUE(isValidTopologicalOrder(bfs, labels, edges)) << "trial " << trial;
    ASSERT_TRUE(isValidTopologicalOrder(dfs, labels, edges)) << "trial " << trial;
    ASSERT_FALSE(std::lexicographical_compare(dfs.begin(), dfs.end(),
                                              bfs.begin(), bfs.end()))
        << "DFS beat the provably smallest BFS order in trial " << trial;
  }
}
