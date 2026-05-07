/*
Date: 07-05-2026
Problem Name: Jump Game IX
Platform: LeetCode
Difficulty: Medium
Tags: Array, Dynamic Programming, Stack, Monotonic Stack

Problem Summary:
Given an integer array 'nums', you can jump from index i to index j under two conditions:
1. Forward jump (j > i): Allowed only if nums[j] < nums[i].
2. Backward jump (j < i): Allowed only if nums[j] > nums[i].
The goal is to find the maximum value in 'nums' reachable from each index i.

Methods to Solve:
1. Graph Construction + BFS/DFS (Brute Force)
2. Monotonic Stack + Strongly Connected Components (Optimal)

---------------------------------------------------------------------------
Method 1: Graph Construction + BFS/DFS
- Intuition: Treat each valid jump as a directed edge in a graph. For each node, perform a traversal to find the maximum value node in its reachable set.
- Approach: Build an adjacency list based on the two jump rules. Run a DFS/BFS from every single index.
- Time Complexity: O(N * (N + E)), where E is the number of edges. In worst case O(N^2).
- Space Complexity: O(N + E) for the graph.
- When to use: Small constraints where N < 1000.

---------------------------------------------------------------------------
Method 2: Monotonic Stack + Range Components (Optimal)
- Intuition: The jump rules create a structure where you can move to any smaller value forward and any larger value backward. This effectively means you can reach any value within a "component" where a certain maximum is maintainable. 
- Approach:
    - A "cut" or barrier occurs between index i and i+1 if all elements to the left are less than or equal to all elements to the right. 
    - Within such a segment, any element can eventually reach the maximum of that segment.
    - We use prefix maximums and suffix minimums to identify these boundaries.
    - If prefixMax[i] <= suffixMin[i+1], no jump can cross this point from left to right (forward jumps require smaller) or right to left (backward jumps require larger).
- Dry Run: 
    nums = [2, 3, 1]
    Prefix Max: [2, 3, 3]
    Suffix Min: [1, 1, 1]
    No i satisfies prefixMax[i] <= suffixMin[i+1].
    Entire array is one component. Max value = 3. Result: [3, 3, 3].
- Time Complexity: O(N) to compute prefix/suffix arrays and linear scan.
- Space Complexity: O(N) to store auxiliary arrays.
- Why better than previous method: Avoids O(N^2) graph traversals; utilizes the mathematical property of the jump constraints.
- When to use: Large constraints (N up to 10^5).

Comparison Table:
Method           | TC       | SC       | Best Use Case
-------------------------------------------------------
Graph Traversal  | O(N^2)   | O(N^2)   | Small N
Prefix/Suffix    | O(N)     | O(N)     | Large N (Optimal)

Final Recommended Solution: Method 2
*/

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    /**
     * Calculates the maximum reachable value for each index based on jump rules.
     * Rule 1: Forward jump to smaller value.
     * Rule 2: Backward jump to larger value.
     */
    vector<int> maxValue(vector<int>& nums) {
        int n = nums.size();
        if (n == 0) return {};

        vector<int> prefMax(n);
        vector<int> suffMin(n);

        // Precompute Prefix Maximums
        prefMax[0] = nums[0];
        for (int i = 1; i < n; ++i) {
            prefMax[i] = max(prefMax[i - 1], nums[i]);
        }

        // Precompute Suffix Minimums
        suffMin[n - 1] = nums[n - 1];
        for (int i = n - 2; i >= 0; --i) {
            suffMin[i] = min(suffMin[i + 1], nums[i]);
        }

        vector<int> ans(n);
        int start = 0;

        // Identify independent components
        for (int i = 0; i < n; ++i) {
            // A cut happens if all elements to the left are <= all elements to the right.
            // This means no jump can ever cross this boundary.
            if (i == n - 1 || prefMax[i] <= suffMin[i + 1]) {
                int currentComponentMax = 0;
                
                // Find max in the current isolated segment
                for (int j = start; j <= i; ++j) {
                    currentComponentMax = max(currentComponentMax, nums[j]);
                }
                
                // Assign the max of this component to all indices within it
                for (int j = start; j <= i; ++j) {
                    ans[j] = currentComponentMax;
                }
                
                start = i + 1;
            }
        }

        return ans;
    }
};
