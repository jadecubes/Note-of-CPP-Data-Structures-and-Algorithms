# C++ Data Structures and Algorithms

![C++](https://img.shields.io/badge/Language-C%2B%2B17-blue.svg)
![Implementations](https://img.shields.io/badge/Implementations-5-green.svg)
![License](https://img.shields.io/badge/License-MIT-yellow.svg)

A curated collection of efficient C++ implementations of essential data structures and algorithms, showcasing modern C++ features and STL advantages.

---

## Why This Repository?

This repository offers:

- **Modern C++ Practices**: Leverages C++17 features and STL containers for cleaner, more efficient code
- **Educational Focus**: Each implementation includes detailed explanations comparing C++ approaches with other languages
- **Complexity Analysis**: Comprehensive time and space complexity analysis for every algorithm
- **Production-Ready Code**: Includes CMake build system and Google Test unit tests
- **Performance Optimizations**: Demonstrates why C++ STL often outperforms manual implementations

---

## Implementations

### Data Structures

| Name | Difficulty | Topics | Time Complexity | Description |
|------|-----------|--------|-----------------|-------------|
| [LRU Cache](lru/) | ⭐⭐⭐ | Hash Table, Doubly Linked List | O(1) get/put | Cache with O(1) operations using `std::list` and `std::unordered_map` |
| [Ring Buffer](ringBuffer/) | ⭐⭐ | Circular Buffer, Arrays | O(1) read/write | Circular buffer implementation with boundary management |
| [Segment Tree](segmentTree/) | ⭐⭐⭐⭐ | Trees, Range Queries | O(log n) update/query | Efficient range update and point query operations |

### Algorithms

| Name | Difficulty | Topics | Time Complexity | Description |
|------|-----------|--------|-----------------|-------------|
| [Find K Closest Elements](findKClosest/) | ⭐⭐⭐ | Binary Search, Two Pointers | O(log n + k) | Find k closest elements to target in sorted array |
| [Topological Sort](topologicalSort/) | ⭐⭐⭐ | Graph, DFS, BFS | O(V log V + E) | DFS and BFS variants; the BFS (Kahn + min-heap) one guarantees the lexicographically smallest ordering |

---

## Featured Implementation: LRU Cache

**Problem**: Design a data structure that follows Least Recently Used (LRU) cache constraints with O(1) time complexity for both `get` and `put` operations.

**C++ Implementation Highlights**:

```cpp
// std::list (doubly linked) + std::unordered_map of iterators:
int Lru::get(int key) {
  auto it = index.find(key);
  if (it == index.end()) return -1;

  // splice() moves the node to the front (most recently used) in O(1),
  // without invalidating any iterators — the whole trick in one line.
  entries.splice(entries.begin(), entries, it->second);
  return it->second->second;
}
```

See [lru/Lru.cpp](lru/Lru.cpp) for the full implementation — the snippet
above is the highlight, not a copy to keep in sync.

**Why C++ Wins Here**:
- No need for custom Node class - `std::pair` handles key-value storage
- `std::list` is a built-in doubly linked list (no manual pointer management)
- `splice()` efficiently moves elements in O(1)
- Iterator-based design eliminates manual node tracking

[View full implementation →](lru/)

---

## Featured Algorithm: Topological Sort

**Problem**: Sort vertices in a directed acyclic graph (DAG) such that for every edge u→v, u comes before v — ideally the lexicographically smallest such ordering.

**Implementation Comparison**:

This repository includes **two implementations**:

1. **DFS-based**: Time complexity O(V log V + E log E)
2. **BFS-based (Kahn's Algorithm)**: Time complexity O(V log V + E) ✅ **More efficient**

**Key Insight**:

```cpp
// BFS approach using priority queue for lexicographical ordering
std::priority_queue<int, std::vector<int>, std::greater<int>> pq;

for (int i = 0; i < V; i++) {
    if (inDegree[i] == 0) pq.push(i);
}

while (!pq.empty()) {
    int u = pq.top(); pq.pop();
    result.push_back(u);

    for (int v : adj[u]) {
        if (--inDegree[v] == 0) pq.push(v);
    }
}
```

**Why BFS Outperforms**: The BFS approach avoids sorting neighbors during traversal (better time complexity), and it is the only one of the two that *guarantees* the lexicographically smallest ordering — see [topologicalSort/Readme.md](topologicalSort/) for why no DFS can.

[View detailed analysis →](topologicalSort/)

---

## Learning Path

### Beginner
Start with simpler data structures to understand C++ STL advantages:
1. Ring Buffer - Learn about circular indexing
2. Find K Closest Elements - Master binary search

### Intermediate
Progress to hash-based and tree structures:
3. LRU Cache - Combine hash tables with linked lists
4. Segment Tree - Understand tree-based range queries

### Advanced
Tackle graph algorithms with multiple approaches:
5. Topological Sort - Compare DFS vs BFS implementations

---

## Solution Quality Metrics

- **Average Time Complexity**: O(log n) or better for most operations
- **STL Usage**: 100% - All implementations leverage C++ Standard Template Library
- **Memory Efficiency**: Optimal space complexity with minimal overhead
- **Test Coverage**: Google Test suite for every module, run in CI on Linux and macOS
- **Documentation**: Every implementation includes detailed README with complexity analysis

---

## Project Structure

```
Note-of-CPP-Data-Structures-and-Algorithms/
├── CMakeLists.txt             # Root build configuration (fetches GoogleTest)
├── README.md                  # This file
├── build.sh                   # Configure + build
├── run_tests.sh               # Build + run all tests via ctest
├── .github/workflows/ci.yml   # CI: build & test on Linux and macOS
│
└── <module>/                  # One directory per implementation, each with:
    ├── <Name>.h               #   declaration
    ├── <Name>.cpp             #   definition
    ├── test_<name>.cpp        #   Google Test suite
    ├── Readme.md              #   notes and complexity analysis
    └── CMakeLists.txt         #   library + test targets

Modules: findKClosest/, lru/, ringBuffer/, segmentTree/, topologicalSort/
```

---

## Building the Project

### Prerequisites
- CMake 3.24 or higher
- C++17 compatible compiler (GCC 7+, Clang 5+, MSVC 2017+)
- Google Test (automatically fetched and pinned by CMake)

### Build Instructions

```bash
# Build all implementations
./build.sh

# Build and run all tests
./run_tests.sh
```

### Working with a Single Module

```bash
cmake -S . -B build
cmake --build build --parallel

# Run one module's tests
ctest --test-dir build -R Lru --output-on-failure
# ...or its test binary directly
./build/lru/lru_tests
```

---

## Resources

### C++ STL References
- [C++ Reference - Containers](https://en.cppreference.com/w/cpp/container)
- [C++ Reference - Algorithms](https://en.cppreference.com/w/cpp/algorithm)

### Algorithm Theory
- [Introduction to Algorithms (CLRS)](https://mitpress.mit.edu/books/introduction-algorithms-third-edition)
- [Competitive Programming Handbook](https://cses.fi/book/book.pdf)

### CMake Documentation
- [CMake Tutorial](https://cmake.org/cmake/help/latest/guide/tutorial/index.html)
- [Modern CMake](https://cliutils.gitlab.io/modern-cmake/)

---

## Contributing

Contributions are welcome! To contribute:

1. **Fork** this repository
2. Create a **feature branch** (`git checkout -b feature/new-data-structure`)
3. Follow the existing code structure:
   - Add `.h` and `.cpp` files in a new directory
   - Include a `Readme.md` with complexity analysis
   - Add a `CMakeLists.txt` (copy any module's — a few lines) and an
     `add_subdirectory` line in the root `CMakeLists.txt`
   - Write tests using Google Test
4. **Commit** your changes with descriptive messages
5. **Push** to your branch
6. Open a **Pull Request**

### Code Style Guidelines
- Use C++17 features and STL containers
- Include time/space complexity in comments
- Follow existing naming conventions
- Add comparison with alternative approaches in README

---

## Disclaimer

This repository is created for **educational purposes** to demonstrate efficient C++ implementations of common data structures and algorithms. The code emphasizes:

- Understanding core algorithmic concepts
- Leveraging C++ STL for cleaner, faster code
- Comparing implementation approaches

**Note**: These implementations are designed for learning and interview preparation. Always understand the underlying logic rather than memorizing code patterns.

---

## License

This project is licensed under the MIT License - see individual files for details.

---

**Happy Coding!** If you find this repository helpful, please consider giving it a ⭐

*Made with C++ and passion for algorithms*
