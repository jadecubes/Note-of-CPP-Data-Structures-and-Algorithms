# Segment Tree

## Explanation
Explanation of key section of code,
```c++
    void updateUtil(int i, int s, int e, int L, int R, int val) {
        if (s > R || e < L) return; // No overlap
        if (s >= L && e <= R) {     // Fully contained
            tree[i] = std::max(tree[i], val);
            return;                 // No need to recurse further
        }
        if (s < e) { // Partial overlap, recurse, not leaf
            int mid = s + (e - s) / 2;
            updateUtil(2 * i + 1, s, mid, L, R, val);
            updateUtil(2 * i + 2, mid + 1, e, L, R, val);
        }
    }
```
