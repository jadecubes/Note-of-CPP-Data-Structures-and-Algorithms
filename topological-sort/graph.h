#ifndef GRAPH_H
#define GRAPH_H

#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <vector>

// Directed graph over int vertex labels (labels need not be contiguous or
// start at 0; duplicates in the constructor are ignored, and edge endpoints
// not passed to the constructor are added automatically) with two
// topological sorts. Both return {} if the graph contains a cycle.
class Graph {
public:
  explicit Graph(const std::vector<int> &values);

  void addEdge(int u, int v);

  // A valid topological order, deterministic (descending-order DFS, reverse
  // postorder). NOT guaranteed lexicographically smallest; see Readme.md.
  std::vector<int> topologicalSortDfs();

  // The lexicographically smallest topological order (Kahn's algorithm with
  // a min-heap: provably picks the smallest available vertex at every step).
  std::vector<int> topologicalSortBfs();

private:
  void addVertex(int v);
  bool dfs(int vertex, std::stack<int> &stack,
           std::unordered_set<int> &visited,
           std::unordered_set<int> &visiting);

  std::unordered_map<int, std::vector<int>> adjList;
  std::vector<int> vertices;         // unique labels
  std::unordered_set<int> labels;    // membership for O(1) dedup
};

#endif // GRAPH_H
