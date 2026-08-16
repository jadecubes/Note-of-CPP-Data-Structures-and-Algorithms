#include "FindKClosest.h"

std::vector<int> findClosestElements(const std::vector<int> &arr, int k, int x) {
  int n = static_cast<int>(arr.size());
  if (k <= 0) {
    return {};
  }
  if (k >= n) {
    return arr;
  }

  // Invariant: the answer window starts in [l, h]. Compare the candidates at
  // the two window edges: if arr[m] is farther from x than arr[m + k], the
  // window must start right of m.
  int l = 0;
  int h = n - k;
  while (l < h) {
    int m = l + (h - l) / 2;
    if (x - arr[m] > arr[m + k] - x) {
      l = m + 1;
    } else {
      h = m;
    }
  }

  return {arr.begin() + l, arr.begin() + l + k};
}
