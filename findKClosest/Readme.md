# Find K Closest Elements

# What is the Problem?
Please refer to https://www.youtube.com/watch?v=o-YDQzHoaKM

# Follow up
If the input array is not sorted, std::multimap is recommended as a solution.
```C++
#include <iostream>
#include <vector>
#include <multimap>
#include <algorithm>

class FindKClosestCorrect {
public:
    std::vector<int> findClosestElements(std::vector<int>& arr, int k, int x) {
        // Use multimap to store value-difference pairs
        std::multimap<int, int> diff_map;  // <difference, original_value>
        
        // Calculate absolute difference from x for each element
        for (int num : arr) {
            int diff = std::abs(num - x);
            diff_map.insert({diff, num});
        }
        
        // Get k elements with smallest differences
        std::vector<int> result;
        auto it = diff_map.begin();
        for (int i = 0; i < k && it != diff_map.end(); ++i) {
            result.push_back(it->second);
            ++it;
        }
        
        // Sort the result for consistent output
        std::sort(result.begin(), result.end());
        return result;
    }
};
```
