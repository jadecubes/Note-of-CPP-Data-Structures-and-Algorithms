#ifndef LRU_H
#define LRU_H

#include <list>
#include <stdexcept>
#include <unordered_map>

class Lru {
private:
  size_t capacity;
  std::list<std::pair<int, int>> list;
  std::unordered_map<int, std::list<std::pair<int, int>>::iterator> map;

public:
  explicit Lru(int cap);
  int get(int key);
  void put(int key, int value);
  void remove(int key);
};

#endif // LRU_H
