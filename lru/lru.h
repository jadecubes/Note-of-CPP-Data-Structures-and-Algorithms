#ifndef LRU_H
#define LRU_H

#include <cstddef>
#include <list>
#include <unordered_map>

// LRU cache: O(1) get/put/remove via std::list (recency order, most recent
// at the front) + std::unordered_map (key -> list node).
class Lru {
public:
  // Throws std::invalid_argument if cap <= 0.
  explicit Lru(int cap);

  // Returns the value for key and marks it most recently used; -1 if absent.
  int get(int key);

  // Inserts or updates key, marking it most recently used. Evicts the least
  // recently used entry when inserting into a full cache.
  void put(int key, int value);

  // Erases key if present; no effect otherwise.
  void remove(int key);

private:
  std::size_t capacity;
  std::list<std::pair<int, int>> entries;  // front = most recently used
  std::unordered_map<int, std::list<std::pair<int, int>>::iterator> index;
};

#endif // LRU_H
