#include <list>
#include <unordered_map>
class Lru {
private:
  size_t capacity;
  std::list<std::pair<int, int>> list;
  std::unordered_map<int, std::list<std::pair<int, int>>::iterator> map;

public:
  Lru(int cap) : capacity(cap) {
    if (capacity <= 0) {
      throw std::invalid_argument("capacity errors");
    }
  }
  int get(int key) {
    auto it = map.find(key);
    if (it == map.end()) {
      return -1;
    }
    list.splice(list.begin(), list, it->second);
    return it->second->second;
  }

  void put(int key, int value) {
    auto foundIterator = map.find(key);
    if (foundIterator != map.end()) {
      foundIterator->second->second = value;
      list.splice(list.begin(), list, foundIterator->second);
      return;
    }
    if (list.size() == capacity) {
      map.erase(list.back().first);
      list.pop_back();
    }
    list.emplace_front(key, value);
    map.insert_or_assign(key, list.begin());
  }

  void remove(int key) {
    auto it = map.find(key);
    if (it == map.end()) {
      return;
    }
    list.erase(it->second);
    map.erase(it);
  }
};