#include "Graph.h"

#include <algorithm>
#include <functional>
#include <queue>

Graph::Graph(const std::vector<int> &values) : vertices(values) {}

void Graph::addEdge(int u, int v) { adjList[u].push_back(v); }

std::vector<int> Graph::topologicalSortDfs() {
  // The result is the reverse of the push order, so descending visits push
  // small vertices last (they pop first). This makes the output
  // deterministic and usually small, but NOT guaranteed lexicographically
  // smallest: once a DFS enters a vertex it must finish that vertex's whole
  // subtree, while the smallest order may need to interleave subtrees.
  // (Counterexample found by the random-DAG test: DFS 11,0,8,3,... vs
  // smallest 11,0,3,8,... — use topologicalSortBfs for the smallest order.)
  std::sort(vertices.begin(), vertices.end(), std::greater<int>());
  for (int vertex : vertices) {
    std::sort(adjList[vertex].begin(), adjList[vertex].end(),
              std::greater<int>());
  }
  std::stack<int> stack;
  std::unordered_set<int> visited;
  std::unordered_set<int> visiting;

  for (int vertex : vertices) {
    if (visited.count(vertex) == 0) {
      if (!dfs(vertex, stack, visited, visiting)) {
        return {}; // cycle
      }
    }
  }

  std::vector<int> result;
  while (!stack.empty()) {
    result.push_back(stack.top());
    stack.pop();
  }
  return result;
}

std::vector<int> Graph::topologicalSortBfs() {
  // Kahn's algorithm. Indegrees are keyed by vertex label, so labels may be
  // arbitrary ints (a vector indexed by label would break for e.g. {5, 10}).
  std::unordered_map<int, int> indegree;
  for (int u : vertices) {
    indegree[u]; // ensure every vertex has an entry
    for (int v : adjList[u]) {
      indegree[v]++;
    }
  }

  // Min-heap yields the smallest ready vertex first: the lexicographically
  // smallest valid ordering.
  std::priority_queue<int, std::vector<int>, std::greater<int>> pq;
  for (const auto &[vertex, degree] : indegree) {
    if (degree == 0) {
      pq.push(vertex);
    }
  }

  std::vector<int> result;
  while (!pq.empty()) {
    int node = pq.top();
    pq.pop();
    result.push_back(node);

    for (int neighbor : adjList[node]) {
      if (--indegree[neighbor] == 0) {
        pq.push(neighbor);
      }
    }
  }

  return result.size() == vertices.size() ? result : std::vector<int>{};
}

bool Graph::dfs(int vertex, std::stack<int> &stack,
                std::unordered_set<int> &visited,
                std::unordered_set<int> &visiting) {
  visiting.insert(vertex);

  for (int neighbor : adjList[vertex]) {
    if (visited.count(neighbor) == 0) {
      if (visiting.count(neighbor) > 0) {
        return false; // back edge: cycle
      }
      if (!dfs(neighbor, stack, visited, visiting)) {
        return false;
      }
    }
  }

  visiting.erase(vertex);
  visited.insert(vertex);
  stack.push(vertex);
  return true;
}
