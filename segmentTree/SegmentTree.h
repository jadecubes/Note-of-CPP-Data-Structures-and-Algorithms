#ifndef SEGMENT_TREE_H
#define SEGMENT_TREE_H

#include <vector>

// Segment tree over indices [0, n) supporting range *max-assignment* updates
// and point queries, both O(log n): update(L, R, val) raises every index in
// [L, R] to at least val; query(i) returns the maximum val applied to i.
// No lazy propagation is needed: updates write max(tree[node], val) at the
// covering nodes and queries take the max along the root-to-leaf path.
class SegmentTree {
public:
  // Throws std::invalid_argument if n <= 0.
  explicit SegmentTree(int n);

  void update(int L, int R, int val);
  int query(int index) const;

private:
  static std::vector<int> createTreeVector(int n);

  void updateUtil(int i, int s, int e, int L, int R, int val);
  int queryUtil(int i, int s, int e, int index) const;

  std::vector<int> tree;
  int N;
};

#endif // SEGMENT_TREE_H
