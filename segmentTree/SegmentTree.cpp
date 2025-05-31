#include <cmath>
#include <vector>

class SegmentTree {
private:
  std::vector<int> tree;
  int N;

  static std::vector<int> createTreeVector(int n) {
    int rangeStart = 0;
    int rangeEnd = n - 1;
    int rangeSize = rangeEnd - rangeStart + 1;
    int levels = static_cast<int>(std::ceil(std::log(rangeSize) / std::log(2)));
    int totalNodes = static_cast<int>(std::pow(2, levels + 1));
    return {totalNodes, 0};
  }

public:
  SegmentTree(int N) : N(N), tree(createTreeVector(N)) {
    // Constructor body remains empty
  }

  void update(int L, int R, int val) { updateUtil(0, 0, N - 1, L, R, val); }

private:
  void updateUtil(int i, int s, int e, int L, int R, int val) {
    if (s > R || e < L)
      return;
    if (s >= L && e <= R) {
      tree[i] = std::max(tree[i], val);
      return;
    }
    if (s < e) {
      int mid = s + (e - s) / 2;
      updateUtil(2 * i + 1, s, mid, L, R, val);
      updateUtil(2 * i + 2, mid + 1, e, L, R, val);
    }
  }

public:
  int query(int index) { return queryUtil(0, 0, N - 1, index); }

private:
  int queryUtil(int i, int s, int e, int index) {
    if (s == e)
      return tree[i];
    int mid = s + (e - s) / 2;
    int ret = (index <= mid) ? queryUtil(2 * i + 1, s, mid, index)
                             : queryUtil(2 * i + 2, mid + 1, e, index);
    return std::max(ret, tree[i]);
  }
};