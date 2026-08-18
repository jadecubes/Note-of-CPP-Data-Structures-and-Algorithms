#include "SegmentTree.h"

#include <algorithm>
#include <cstddef>
#include <stdexcept>

std::vector<int> SegmentTree::createTreeVector(int n) {
  if (n <= 0) {
    throw std::invalid_argument("SegmentTree size must be positive");
  }
  // Round n up to a power of two; a complete tree over that many leaves has
  // 2 * leaves nodes (integer arithmetic avoids float log/pow rounding).
  std::size_t leaves = 1;
  while (leaves < static_cast<std::size_t>(n)) {
    leaves *= 2;
  }
  return std::vector<int>(2 * leaves, 0);
}

SegmentTree::SegmentTree(int n) : tree(createTreeVector(n)), N(n) {}

void SegmentTree::update(int L, int R, int val) {
  if (L < 0 || R >= N || L > R) {
    throw std::out_of_range("SegmentTree::update range invalid");
  }
  updateUtil(0, 0, N - 1, L, R, val);
}

void SegmentTree::updateUtil(std::size_t i, int s, int e, int L, int R,
                             int val) {
  if (s > R || e < L) { // no overlap
    return;
  }
  if (s >= L && e <= R) { // fully contained: record and stop
    tree[i] = std::max(tree[i], val);
    return;
  }
  int mid = s + (e - s) / 2; // partial overlap: recurse
  updateUtil(2 * i + 1, s, mid, L, R, val);
  updateUtil(2 * i + 2, mid + 1, e, L, R, val);
}

int SegmentTree::query(int index) const {
  if (index < 0 || index >= N) {
    throw std::out_of_range("SegmentTree::query index invalid");
  }
  return queryUtil(0, 0, N - 1, index);
}

int SegmentTree::queryUtil(std::size_t i, int s, int e, int index) const {
  if (s == e) {
    return tree[i];
  }
  int mid = s + (e - s) / 2;
  int ret = (index <= mid) ? queryUtil(2 * i + 1, s, mid, index)
                           : queryUtil(2 * i + 2, mid + 1, e, index);
  return std::max(ret, tree[i]);
}
