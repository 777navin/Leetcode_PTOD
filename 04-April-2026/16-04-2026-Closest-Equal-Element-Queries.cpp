# Closest Equal Element Queries

Solved LeetCode 3488. Closest Equal Element Queries using C++.

## Problem Statement

You are given a circular array `nums` and multiple query indices.

For each query index `i`, find the minimum circular distance between `nums[i]` and any other index `j` where:

- `nums[i] == nums[j]`
- `i != j`

If no such index exists, return `-1`.

---

## Approach

### Key Idea

Store all positions of every value using a hash map.

For each query:

- Get all indices where current value appears.
- Use binary search to locate current index.
- Check previous and next occurrence.
- Since array is circular, calculate both direct and wrap-around distance.

### Why Efficient?

Instead of checking all indices every time, we directly jump to nearest equal elements.

---

## Data Structures Used

- `unordered_map<int, vector<int>>` → stores positions of values  
- `lower_bound()` → binary search for nearest index
  Time Complexity of Code
Building hashmap: O(n)
Each query uses binary search: O(log k)

Overall:

O(n + q log k)

Space Complexity of Code
HashMap stores all indices: O(n)
Answer array: O(q)

Overall:

O(n + q)

Final Complexity
Time Complexity: O(n + q log k)
Space Complexity: O(n + q)

---

## C++ Code

```cpp
class Solution {
public:
    vector<int> solveQueries(vector<int>& nums, vector<int>& queries) {
        int n = nums.size();

        unordered_map<int, vector<int>> pos;

        for (int i = 0; i < n; i++) {
            pos[nums[i]].push_back(i);
        }

        vector<int> ans;

        for (int q : queries) {
            vector<int>& arr = pos[nums[q]];

            if (arr.size() == 1) {
                ans.push_back(-1);
                continue;
            }

            int idx = lower_bound(arr.begin(), arr.end(), q) - arr.begin();

            int prev = arr[(idx - 1 + arr.size()) % arr.size()];
            int next = arr[(idx + 1) % arr.size()];

            int d1 = abs(q - prev);
            d1 = min(d1, n - d1);

            int d2 = abs(q - next);
            d2 = min(d2, n - d2);

            ans.push_back(min(d1, d2));
        }

        return ans;
    }
};
