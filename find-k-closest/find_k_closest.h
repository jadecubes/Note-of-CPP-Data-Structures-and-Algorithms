#ifndef FIND_K_CLOSEST_H
#define FIND_K_CLOSEST_H

#include <vector>

// Returns the k elements of the sorted array arr closest to x, in ascending
// order (ties prefer the smaller element). Binary-searches the left edge of
// the answer window: O(log(n - k) + k).
// Returns {} for k <= 0; returns the whole array for k >= arr.size().
std::vector<int> findClosestElements(const std::vector<int> &arr, int k, int x);

#endif // FIND_K_CLOSEST_H
