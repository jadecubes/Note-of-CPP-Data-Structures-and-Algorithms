#include <vector>
class FindKClosest {
public:
  std::vector<int> findClosestElements(std::vector<int> &arr, int k, int x) {
    int n = arr.size();
    int l = 0, h = n - k;

    while (l < h) {
      int m = (l + h) / 2;
      if (x - arr[m] > arr[m + k] - x)
        l = m + 1;
      else
        h = m;
    }

    return {arr.begin() + l, arr.begin() + l + k};
  }
};