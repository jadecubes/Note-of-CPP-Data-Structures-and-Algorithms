# Topological Sort
In the file, the functions, topologicalSortBfs and topologicalSortDfs generate the smallest lexicographical order of topological sort.

## What Is It?
Please refer to https://www.youtube.com/watch?v=AfSk24UTFS8

## Comparisons of topologicalSortBfs and topologicalSortDfs

### Time Complexity of topologicalSortDfs
- Sorting Vertices:

   ```std::sort on vertices: O(V log V).```

- DFS Traversal:
```
    Visit each vertex once: O(V).
    Process each edge once: O(E) (for cycle detection and recursion).
```
- Sorting Neighbors:
```
    For each vertex, sort its adjacency list.
    Let d(v) be the out-degree of vertex v. Sorting adjList[v]: O(d(v) log d(v)).
    Total over all vertices: Σ d(v) = E (sum of out-degrees is number of edges), but sorting cost is Σ O(d(v) log d(v)).
    Worst case: One vertex has E edges → O(E log E).
    Average case: If degrees are balanced, closer to O(E log (E/V)), but we use worst-case for analysis.
```
- Overall:
```
    O(V log V + V + E + E log E) = O(V log V + E log E).
```

### Time Complexity of topologicalSortBfs
- In-degree Calculation
  ```
  Complexity: O(V + E) (accounts for visiting each vertex and edge once).
  ```
- Initial Population of the Priority Queue
```
for (int i : vertices) {
    if (indegree[i] == 0) pq.push(i);
}
```

```
- Work:

    - Loop over V vertices: O(V).
    - For each vertex with in-degree 0, pq.push(i) is called.
    = push in a priority_queue (heap) is O(log k), where k is the current heap size.

- How Many Pushes?:

    - At most V vertices can have in-degree 0 initially (if the graph is a forest with no edges).
    - Worst case: Heap grows from 0 to k ≤ V elements.

- Cost:

    - First push: O(log 1).
    - Second push: O(log 2).
    - Up to k-th push: O(log k), where k ≤ V.
    - Total: O(log 1 + log 2 + ... + log V) = O(log (1 * 2 * ... * V)) = O(log V!).
    - Stirling’s approximation: log V! ≈ V log V - V → O(V log V).

- Complexity: O(V log V) for pushing all initial vertices.
```
- Main Loop (Processing the Queue)
```
while (!pq.empty()) {
    int node = pq.top();
    pq.pop();
    result.push_back(node);
    for (int neighbor : adjList[node]) {
        if (--indegree[neighbor] == 0) pq.push(neighbor);
    }
}
```

```
Pops: O(V log V).
Pushes: O(V log V) (all vertices pushed once).
Edge processing: O(E) (just the decrements and checks).
Combined: O(V log V + E).
```

- Overall Complexity
```
    In-degree: O(V + E).
    Initial pushes: O(V log V).
    Main loop: O(V log V + E).
```
- Total: O(V + E + V log V + V log V + E) = O(V log V + E).

### Conclusion
In both topologicalSortBfs and topologicalSortDfs, the space complexity is O(V).

But, for time complexity, topologicalSortBfs is O(V log V + E) and topologicalSortDfs is O(V log V + E log E), so topologicalSortBfs performs better.
