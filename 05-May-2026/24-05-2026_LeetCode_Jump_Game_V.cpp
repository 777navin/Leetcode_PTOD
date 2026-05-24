// File Name: 24-05-2026_LeetCode_Jump_Game_V.cpp

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*
Date: 24-05-2026
Problem Name: 1340. Jump Game V
Platform: LeetCode
Difficulty: Hard
Tags: Array, Dynamic Programming, Sorting

Problem Summary:
Given an integer array `arr` and an integer `d`, you can jump from index `i` to `i + x` or `i - x` 
(where 0 < x <= d). A jump is only valid if all elements between the starting index and the destination 
index are strictly smaller than `arr[i]`. You can start at any index. 
Return the maximum number of indices you can visit.

Methods to Solve:
1. Dynamic Programming + Memoization (Top-Down)
2. Dynamic Programming + Sorting (Bottom-Up)

---------------------------------------------------------
Method 1: Dynamic Programming + Memoization (Top-Down)
---------------------------------------------------------
- Intuition: We can view this problem as finding the longest path in a Directed Acyclic Graph (DAG). 
  Since we can only jump to strictly smaller elements, there are no cycles. We can compute the max 
  jumps from each index and cache the results to avoid redundant calculations.
- Approach: 
  Create a `dp` array initialized to 0. 
  For each index `i`, perform a DFS:
    - Check up to `d` steps to the right. Stop early if a taller or equal element is encountered.
    - Check up to `d` steps to the left. Stop early if a taller or equal element is encountered.
    - The result for `i` is 1 + the maximum of the valid recursive jumps.
  Return the maximum value found across all starting indices.
- Dry Run (arr = [6,4,14,6,8,13,9,7,10,6,12], d = 2):
  - Start at 10 (index 8). Valid jumps are to 7 (index 7) or 6 (index 9). 
  - From 7, no valid jumps.
  - Recursion naturally explores these paths, caching the depth at each index.
- Time Complexity: O(N * d), where N is the length of `arr`. For each element, we check at most `2d` neighbors.
- Space Complexity: O(N) for the memoization array `dp` and recursion stack.
- Why better than previous method: It avoids the O(N!) brute force explosion of paths by caching states.
- When to use: When you want an intuitive DFS-style traversal and the constraints allow recursion.

---------------------------------------------------------
Method 2: Dynamic Programming + Sorting (Bottom-Up)
---------------------------------------------------------
- Intuition: Instead of recursive DFS, we can compute the answers in an optimal order. Since jumps only 
  go from larger numbers to smaller numbers, if we process the elements from smallest to largest, the answers 
  for the valid destination indices will already be computed.
- Approach:
  Store pairs of `(arr[i], i)` and sort them in ascending order.
  Iterate through the sorted array. For each original index `i`:
    - Look left up to `d` steps. Update `dp[i] = max(dp[i], 1 + dp[j])`. Break if `arr[j] >= arr[i]`.
    - Look right up to `d` steps. Update `dp[i] = max(dp[i], 1 + dp[j])`. Break if `arr[j] >= arr[i]`.
- Dry Run (arr = [3,3,3,3,3], d = 3):
  - Sorted order process indices.
  - Since all elements are equal, any attempt to look left/right immediately breaks.
  - DP array remains filled with 1s. Max is 1.
- Time Complexity: O(N log N + N * d) for sorting the array, then checking neighbors.
- Space Complexity: O(N) for the DP array and the pairs array.
- Why better than previous method: Avoids recursion stack overhead, which can be safer for very deep graphs.
- When to use: When iterative DP is preferred or recursion depth limits are a concern.

Comparison Table:
Method                     | TC                  | SC   | Best Use Case
---------------------------|---------------------|------|---------------------------------------
1. DP + Memoization        | O(N * d)            | O(N) | Default choice, elegant and very fast.
2. DP + Sorting            | O(N log N + N * d)  | O(N) | Strict environment with limited stack.

Final Recommended Solution: Method 1 (DP + Memoization) is generally cleaner to write for this specific problem and slightly faster in practice since it drops the O(N log N) sorting step. Both are included below.
*/

class Solution {
private:
    int dfs(int i, int d, const vector<int>& arr, vector<int>& dp) {
        if (dp[i] != 0) return dp[i];
        
        int max_jumps = 1;
        int n = arr.size();
        
        // Check right
        for (int j = i + 1; j <= min(i + d, n - 1) && arr[j] < arr[i]; ++j) {
            max_jumps = max(max_jumps, 1 + dfs(j, d, arr, dp));
        }
        
        // Check left
        for (int j = i - 1; j >= max(i - d, 0) && arr[j] < arr[i]; --j) {
            max_jumps = max(max_jumps, 1 + dfs(j, d, arr, dp));
        }
        
        return dp[i] = max_jumps;
    }

public:
    // Method 1: Top-Down DP
    int maxJumps(vector<int>& arr, int d) {
        int n = arr.size();
        vector<int> dp(n, 0);
        int result = 1;
        
        for (int i = 0; i < n; ++i) {
            result = max(result, dfs(i, d, arr, dp));
        }
        
        return result;
    }

    // Method 2: Bottom-Up DP with Sorting (Alternative Approach)
    int maxJumpsBottomUp(vector<int>& arr, int d) {
        int n = arr.size();
        vector<pair<int, int>> sorted_arr;
        for (int i = 0; i < n; ++i) {
            sorted_arr.push_back({arr[i], i});
        }
        
        sort(sorted_arr.begin(), sorted_arr.end());
        vector<int> dp(n, 1);
        int result = 1;
        
        for (auto& p : sorted_arr) {
            int i = p.second;
            
            // Check right
            for (int j = i + 1; j <= min(i + d, n - 1) && arr[j] < arr[i]; ++j) {
                dp[i] = max(dp[i], 1 + dp[j]);
            }
            
            // Check left
            for (int j = i - 1; j >= max(i - d, 0) && arr[j] < arr[i]; --j) {
                dp[i] = max(dp[i], 1 + dp[j]);
            }
            
            result = max(result, dp[i]);
        }
        
        return result;
    }
};

// Driver Code to make it a fully standalone runnable file
int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    Solution sol;

    // Test Case 1
    vector<int> arr1 = {6, 4, 14, 6, 8, 13, 9, 7, 10, 6, 12};
    int d1 = 2;
    cout << "Test Case 1 Output: " << sol.maxJumps(arr1, d1) << " (Expected: 4)\n";

    // Test Case 2
    vector<int> arr2 = {3, 3, 3, 3, 3};
    int d2 = 3;
    cout << "Test Case 2 Output: " << sol.maxJumps(arr2, d2) << " (Expected: 1)\n";

    // Test Case 3
    vector<int> arr3 = {7, 6, 5, 4, 3, 2, 1};
    int d3 = 1;
    cout << "Test Case 3 Output: " << sol.maxJumps(arr3, d3) << " (Expected: 7)\n";

    return 0;
}
