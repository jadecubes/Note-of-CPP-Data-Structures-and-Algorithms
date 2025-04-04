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
