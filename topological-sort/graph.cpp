#include "graph.h"

#include <algorithm>
#include <functional>
#include <queue>

Graph::Graph(const std::vector<int> &values) {
  for (int v : values) {
    addVertex(v);
  }
}

// Dedup: without it a duplicate label (or an edge endpoint that was also a
// constructor value) inflates vertices.size() and makes the BFS cycle check
// falsely report a cycle.
void Graph::addVertex(int v) {
  if (labels.insert(v).second) {
    vertices.push_back(v);
  }
}

void Graph::addEdge(int u, int v) {
  addVertex(u); // unknown endpoints become vertices, so both sort variants
  addVertex(v); // agree on the vertex set
  adjList[u].push_back(v);
}

std::vector<int> Graph::topologicalSortDfs() {
  // The result is the reverse of the push order, so descending visits push
  // small vertices last (they pop first). Deterministic, but NOT guaranteed
  // lexicographically smallest — no DFS visit order can be; see Readme.md.
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
