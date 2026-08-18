#include "lru.h"

#include <stdexcept>

Lru::Lru(int cap) {
  // Validate as int: a negative cap converted to size_t first would wrap to
  // a huge value and pass a size_t comparison.
  if (cap <= 0) {
    throw std::invalid_argument("Lru capacity must be positive");
  }
  capacity = static_cast<std::size_t>(cap);
}

int Lru::get(int key) {
  auto it = index.find(key);
  if (it == index.end()) {
    return -1;
  }
  entries.splice(entries.begin(), entries, it->second);
  return it->second->second;
}

void Lru::put(int key, int value) {
  auto it = index.find(key);
  if (it != index.end()) {
    it->second->second = value;
    entries.splice(entries.begin(), entries, it->second);
    return;
  }
  if (entries.size() == capacity) {
    // entries cannot be empty here: the constructor rejects capacity 0.
    index.erase(entries.back().first);
    entries.pop_back();
  }
  entries.emplace_front(key, value);
  index[key] = entries.begin();
}

void Lru::remove(int key) {
  auto it = index.find(key);
  if (it == index.end()) {
    return;
  }
  entries.erase(it->second);
  index.erase(it);
}
