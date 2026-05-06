// 28-04-2026_LeetCode_Minimum_Operations_to_Make_a_Uni_Value_Grid.cpp

/*
Date: 28-04-2026
Problem Name: Minimum Operations to Make a Uni-Value Grid (2033)
Platform: LeetCode
Difficulty: Medium
Tags: Array, Math, Matrix, Sorting

Problem Summary:
You are given an m x n 2D integer grid and an integer x. In one operation, you can add x to 
or subtract x from any element in the grid. A uni-value grid is a grid where all the elements 
of it are equal. The goal is to return the minimum number of operations to make the grid uni-value. 
If it is impossible, return -1.

=================================================================================================
Methods to Solve:
=================================================================================================

1. Brute Force (Conceptual)
---------------------------
- Intuition: Check every single element in the grid as a potential target value.
- Approach: Flatten the grid. For every element `arr[i]`, iterate through all other elements 
  `arr[j]` to calculate the operations needed to make `arr[j]` equal to `arr[i]`. Track the minimum.
- Dry Run: Not applicable due to extreme inefficiency.
- Time Complexity: O((M*N)^2), where M and N are the dimensions of the grid.
- Space Complexity: O(M*N) to store the flattened grid.
- Why better than previous method: It is the baseline.
- When to use: Never use in a real contest/interview (will result in Time Limit Exceeded).

2. Better Approach (Sorting & Median)
-------------------------------------
- Intuition: To minimize the sum of absolute differences to a target value, the mathematical 
  ideal target is the MEDIAN of the dataset. Furthermore, to reach this target by adding/subtracting 
  `x`, every element MUST have the same remainder when divided by `x`.
- Approach:
  1. Flatten the 2D grid into a 1D vector `arr`.
  2. Check the base condition: calculate `rem = arr[0] % x`. Iterate through `arr`. If any element 
     has a different remainder (`arr[i] % x != rem`), it's impossible to make them equal. Return -1.
  3. Sort the 1D vector `arr`.
  4. Find the median value: `target = arr[arr.size() / 2]`.
  5. Calculate the total operations: sum of `abs(arr[i] - target) / x` for all elements.
- Dry Run (Example 1: grid = [[2,4],[6,8]], x = 2):
  - Flatten: [2, 4, 6, 8]
  - Modulo check: 2%2=0, 4%2=0, 6%2=0, 8%2=0 (All valid).
  - Sorted: [2, 4, 6, 8]
  - Median index = 4 / 2 = 2. arr[2] = 6 (arr[1]=4 also works perfectly for even lengths).
  - Target = 6.
  - Ops: |2-6|/2 = 2; |4-6|/2 = 1; |6-6|/2 = 0; |8-6|/2 = 1. Total = 4.
- Time Complexity: O(K log K) where K = M*N. Dominated by sorting.
- Space Complexity: O(K) to store the 1D array.
- Why better than previous method: Drastically reduces time complexity by leveraging mathematical 
  properties of the median instead of checking all pairs.
- When to use: Standard interviews and coding contests. Highly reliable and easy to implement.

3. Optimal Approach (Quickselect / nth_element)
-----------------------------------------------
- Intuition: We don't need to fully sort the array to find the median. We only need the element 
  that would be at the middle index if it were sorted.
- Approach: Same as Approach 2, but use `std::nth_element` to find the median in linear time 
  instead of `std::sort`.
- Dry Run: Similar to Approach 2, but bypassing full sorting overhead.
- Time Complexity: O(K) average case, where K = M*N.
- Space Complexity: O(K) for the 1D array.
- Why better than previous method: Replaces O(K log K) sorting with an average O(K) selection algorithm.
- When to use: When maximum optimization is required, or in system-level code where large inputs 
  are expected.

=================================================================================================
Comparison Table:
=================================================================================================
+-----------------+-------------------+-------------------+---------------------------------+
| Method          | Time Complexity   | Space Complexity  | Best Use Case                   |
+-----------------+-------------------+-------------------+---------------------------------+
| 1. Brute Force  | O((M*N)^2)        | O(M*N)            | Purely theoretical              |
| 2. Sorting      | O(M*N log(M*N))   | O(M*N)            | Standard interviews/contests    |
| 3. Quickselect  | O(M*N) avg        | O(M*N)            | Max optimization / Production   |
+-----------------+-------------------+-------------------+---------------------------------+

Final Recommended Solution: Approach 3 (implemented using std::nth_element for peak performance, 
though Approach 2 is completely acceptable for LeetCode constraints).
*/

#include <vector>
#include <cmath>
#include <algorithm>
#include <iostream>

using namespace std;

class Solution {
public:
    // Implementation of the Final Recommended Solution (Approach 3 / Quickselect)
    int minOperations(vector<vector<int>>& grid, int x) {
        int m = grid.size();
        int n = grid[0].size();
        int totalElements = m * n;
        
        vector<int> arr;
        arr.reserve(totalElements);
        
        // 1. Flatten the grid
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                arr.push_back(grid[i][j]);
            }
        }
        
        // 2. Modulo check to see if uni-value is possible
        // Handling negative values safely with ((val % x) + x) % x just in case, 
        // though LeetCode constraints are usually strictly positive.
        int rem = ((arr[0] % x) + x) % x;
        for (int i = 1; i < totalElements; ++i) {
            if (((arr[i] % x) + x) % x != rem) {
                return -1;
            }
        }
        
        // 3. Find median using Quickselect (std::nth_element is average O(N))
        int medianIndex = totalElements / 2;
        nth_element(arr.begin(), arr.begin() + medianIndex, arr.end());
        int median = arr[medianIndex];
        
        // 4. Calculate total operations needed to reach median
        int operations = 0;
        for (int val : arr) {
            operations += abs(val - median) / x;
        }
        
        return operations;
    }

    // Alternative: Approach 2 (Standard Sorting)
    // Included for reference and completeness.
    int minOperationsSorting(vector<vector<int>>& grid, int x) {
        vector<int> arr;
        for (const auto& row : grid) {
            for (int val : row) {
                arr.push_back(val);
            }
        }
        
        int rem = arr[0] % x;
        for (int val : arr) {
            if (val % x != rem) return -1;
        }
        
        sort(arr.begin(), arr.end());
        
        int median = arr[arr.size() / 2];
        int operations = 0;
        
        for (int val : arr) {
            operations += abs(val - median) / x;
        }
        
        return operations;
    }
};
