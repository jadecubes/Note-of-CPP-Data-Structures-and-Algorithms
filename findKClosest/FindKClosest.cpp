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
  // window must start right of m. Distances are computed in long long: with
  // int, x = INT_MAX against negative elements overflows (UB) and picks the
  // farthest window instead of the closest.
  int l = 0;
  int h = n - k;
  while (l < h) {
    int m = l + (h - l) / 2;
    if (static_cast<long long>(x) - arr[m] >
        static_cast<long long>(arr[m + k]) - x) {
      l = m + 1;
    } else {
      h = m;
    }
  }

  return {arr.begin() + l, arr.begin() + l + k};
}
