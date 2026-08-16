# Segment Tree

## Explanation
Explanation of key section of code,
```c++
void SegmentTree::updateUtil(int i, int s, int e, int L, int R, int val) {
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
```
A leaf is always either fully contained or non-overlapping (its range is a
single index), so the fully-contained check doubles as the leaf base case and
no explicit `s < e` guard is needed before recursing.
