#ifndef SEGMENT_TREE_H
#define SEGMENT_TREE_H

#include <vector>

class SegmentTree {
private:
  std::vector<int> tree;
  int N;

  static std::vector<int> createTreeVector(int n);

  void updateUtil(int i, int s, int e, int L, int R, int val);
  int queryUtil(int i, int s, int e, int index);

public:
  explicit SegmentTree(int N);
  void update(int L, int R, int val);
  int query(int index);
};

#endif // SEGMENT_TREE_H
