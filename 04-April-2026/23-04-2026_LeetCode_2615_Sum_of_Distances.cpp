/*


Date: 23-04-2026
Problem Name: Sum of Distances
Platform: LeetCode
Problem No: 2615
Difficulty: Medium
Tags: HashMap, Prefix Sum, Arrays, Math

============================================================
Problem Summary:
You are given a 0-indexed integer array nums.

For each index i:
arr[i] = sum of |i - j| for all j such that:
nums[j] == nums[i] and j != i

Return the array arr.

------------------------------------------------------------
Methods to Solve:

1. Brute Force
- For every index i, scan whole array.
- If nums[j] == nums[i], add |i-j|
- Time: O(n^2)
- Space: O(1)

2. Better Approach (Grouping + Prefix Sum)
- Store all indices for each value.
- For each group, calculate contribution using prefix sums.
- Time: O(n)
- Space: O(n)

3. Optimal Approach (Two Pass Running Sum)
- Left to right + Right to left.
- More advanced but same O(n).

------------------------------------------------------------
Intuition:

If same number occurs at indices:
[p0, p1, p2, ... pk]

For any position pm:
distance = sum(pm - left positions)
         + sum(right positions - pm)

Using prefix sums:
Left Cost  = m * pm - sum(left indices)
Right Cost = sum(right indices) - (remaining * pm)

------------------------------------------------------------
Dry Run:

nums = [1,3,1,1,2]

Value 1 at indices = [0,2,3]

For index 0:
|0-2| + |0-3| = 5

For index 2:
|2-0| + |2-3| = 3

For index 3:
|3-0| + |3-2| = 4

------------------------------------------------------------
Comparison Table:

Method              TC        SC      Use Case
------------------------------------------------
Brute Force         O(n^2)    O(1)    Small inputs
Grouping Prefix     O(n)      O(n)    Best choice
Two Pass            O(n)      O(n)    Advanced variant

------------------------------------------------------------
Final Recommended Solution:
Use HashMap + Prefix Sum on grouped indices.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<long long> distance(vector<int>& nums) {
        int n = nums.size();

        unordered_map<int, vector<int>> positions;

        // Store indices of each value
        for (int i = 0; i < n; i++) {
            positions[nums[i]].push_back(i);
        }

        vector<long long> answer(n, 0);

        // Process each group
        for (auto& entry : positions) {
            vector<int>& idx = entry.second;
            int m = idx.size();

            // Prefix sums of indices
            vector<long long> prefix(m + 1, 0);
            for (int i = 0; i < m; i++) {
                prefix[i + 1] = prefix[i] + idx[i];
            }

            for (int i = 0; i < m; i++) {
                long long currentIndex = idx[i];

                // Left side contribution
                long long leftCost =
                    1LL * i * currentIndex - prefix[i];

                // Right side contribution
                long long rightCost =
                    (prefix[m] - prefix[i + 1]) -
                    1LL * (m - i - 1) * currentIndex;

                answer[currentIndex] = leftCost + rightCost;
            }
        }

        return answer;
    }
};
