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
| [Topological Sort](topologicalSort/) | ⭐⭐⭐ | Graph, DFS, BFS | O(V log V + E) | Two implementations with lexicographically smallest ordering |

---

## Featured Implementation: LRU Cache

**Problem**: Design a data structure that follows Least Recently Used (LRU) cache constraints with O(1) time complexity for both `get` and `put` operations.

**C++ Implementation Highlights**:

```cpp
class Lru {
private:
    int capacity;
    std::list<std::pair<int, int>> cache;  // Built-in doubly linked list
    std::unordered_map<int, std::list<std::pair<int, int>>::iterator> map;

public:
    int get(int key) {
        if (map.find(key) == map.end()) return -1;

        // Move to front (most recently used)
        cache.splice(cache.begin(), cache, map[key]);
        return map[key]->second;
    }

    void put(int key, int value) {
        if (map.find(key) != map.end()) {
            cache.erase(map[key]);
        }

        cache.emplace_front(key, value);
        map[key] = cache.begin();

        if (cache.size() > capacity) {
            // Remove least recently used
            map.erase(cache.back().first);
            cache.pop_back();
        }
    }
};
```

**Why C++ Wins Here**:
- No need for custom Node class - `std::pair` handles key-value storage
- `std::list` is a built-in doubly linked list (no manual pointer management)
- `splice()` efficiently moves elements in O(1)
- Iterator-based design eliminates manual node tracking

[View full implementation →](lru/)

---

## Featured Algorithm: Topological Sort

**Problem**: Sort vertices in a directed acyclic graph (DAG) such that for every edge u→v, u comes before v. Return the lexicographically smallest ordering.

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

**Why BFS Outperforms**: The BFS approach avoids sorting neighbors during traversal, resulting in better time complexity while maintaining lexicographical order through the priority queue.

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
- **Test Coverage**: Google Test suite included for critical modules
- **Documentation**: Every implementation includes detailed README with complexity analysis

---

## Project Structure

```
Note-of-CPP-Data-Structures-and-Algorithms/
├── CMakeLists.txt              # Root build configuration
├── README.md                   # This file
├── build.sh                    # Incremental build script
├── generateCMakeLists.sh      # Auto-generate module CMakeLists
├── run_tests.sh               # Execute all tests
│
├── lru/                       # LRU Cache implementation
│   ├── Lru.h
│   ├── Lru.cpp
│   ├── Readme.md
│   └── CMakeLists.txt
│
├── ringBuffer/                # Ring buffer with tests
│   ├── SringBuffer.h
│   ├── SringBuffer.cpp
│   ├── test_ring_buffer.cpp
│   └── CMakeLists.txt
│
├── findKClosest/              # Binary search algorithm
│   ├── FindKClosest.cpp
│   ├── Readme.md
│   └── CMakeLists.txt
│
├── segmentTree/               # Segment tree structure
│   ├── SegmentTree.h
│   ├── SegmentTree.cpp
│   ├── Readme.md
│   └── CMakeLists.txt
│
└── topologicalSort/           # Graph sorting algorithms
    ├── Graph.cpp
    ├── Readme.md
    └── CMakeLists.txt
```

---

## Building the Project

### Prerequisites
- CMake 3.14 or higher
- C++17 compatible compiler (GCC 7+, Clang 5+, MSVC 2017+)
- Google Test (automatically fetched by CMake)

### Build Instructions

```bash
# Generate CMakeLists for all modules
./generateCMakeLists.sh

# Build all implementations
./build.sh

# Run tests
./run_tests.sh
```

### Building Specific Modules

```bash
mkdir build && cd build
cmake ..
cmake --build .

# Run specific test
./ringBuffer/test_ring_buffer
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
   - Add `CMakeLists.txt` (or use `generateCMakeLists.sh`)
   - Write tests using Google Test if applicable
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
