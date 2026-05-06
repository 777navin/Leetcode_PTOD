// 29-04-2026_Maximum_Score_From_Grid_Operations.cpp

/*
Date: 29-04-2026
Problem Name: 3225. Maximum Score From Grid Operations
Platform: LeetCode
Difficulty: Hard
Tags: Dynamic Programming, Prefix Sum, Grid

Problem Summary:
You are given an n x n grid initially colored white. In one operation, you can select 
any column j and color a prefix of its cells black (from the top row 0 down to h_j). 
A white cell at (r, c) contributes its grid value to the total score if it has a 
horizontally adjacent black cell (meaning the black height of col c-1 or col c+1 is > r).
Goal: Find the maximum possible score by optimally choosing the black prefix height 
for each column.

Methods to Solve:
1. DP with 3-Column State (Brute Force Transition) - O(N^4) Time
2. Optimized DP with Prefix/Suffix Maximums - O(N^3) Time

================================================================================
Method 1: DP with 3-Column State (Brute Force Transition)
================================================================================
Intuition:
Since a white cell's score is triggered by its left or right neighbor, the score 
of column `c` fundamentally depends on the heights of columns `c-1`, `c`, and `c+1`. 
We define dp[h_prev][h_curr] for column `c`. To transition to `c+1`, we iterate 
through all possible heights for `c+1` (h_next) and calculate newly unlocked scores.

Approach:
- dp[col][h_prev][h_curr] stores the max score up to `col`.
- Transition to `h_next`: 
  Score added to col+1 (due to left neighbor) + Score added to col (due to right neighbor).
- Requires 4 nested loops: col, h_prev, h_curr, h_next.

Time Complexity: O(N^4)
Space Complexity: O(N^2) (Space optimized to 2 layers)

Why better than previous method: Baseline Dynamic Programming approach.
When to use: When N <= 50.

================================================================================
Method 2: Optimized DP with Prefix/Suffix Maximums (Optimal Approach)
================================================================================
Intuition:
In the O(N^4) approach, the innermost loop calculates the transition:
  f(h_next) = max_{h_prev} (dp[h_prev][h_curr] + S(col, max(h_curr, h_prev), h_next))
Notice that the range sum `S(col, L, R) = PrefixSum[R] - PrefixSum[L]`. We can 
algebraically decouple `h_prev` from `h_next` into three distinct cases based on 
their relative sizes.

Approach:
1. For a fixed `col` and `h_curr`, we precalculate:
   - The maximum DP value where `h_prev <= h_curr`.
   - A suffix maximum array for DP values.
2. As we iterate `h_next` from 0 to n, we maintain a dynamic running maximum of the 
   expression (dp[k][h_curr] - PrefixSum[k]) for `h_curr < k < h_next`.
3. This allows us to compute the transition for each `h_next` in O(1) time.

Visualizing the 3-Column Overlap Resolution:
      c-1         c          c+1
    [h_prev]
      |--|     [h_curr]
      |  |       |--|      [h_next]
      |  |       |  |       |----|
      |  |       |  |       |    |
      |__|       |__|       |____|
* The overlapping white space in column `c` that gets activated by `c-1` and `c+1` 
  is cleanly resolved by the max() logic and dynamic prefix tracking, preventing 
  double-counting without requiring an extra O(N) loop.

Dry Run (Small 2x2 Concept):
- Initial Base Case: dp[0][0..n] = 0.
- Col 0 to 1: we transition from state (h_prev=0, h_curr=0) -> testing h_next=1.
- Max DP extracts the optimal previous state seamlessly in O(1) per h_next using 
  the precomputed suffix/prefix variables.

Time Complexity: O(N^3) - Outer loops N x N, inner decoupled O(N) loop.
Space Complexity: O(N^2) - We only maintain the current and next DP layers.

Why better than previous method: Eliminates the inner O(N) loop via math and 
running-maximum logic, easily passing strict LeetCode Time Limits.
When to use: When N = 100 (Standard constraints for LeetCode Hard problems).

================================================================================
Comparison Table:
Method                    | TC     | SC     | Best Use Case
--------------------------|--------|--------|-----------------------------------
1. Brute Force DP         | O(N^4) | O(N^2) | Small constraints, easier to read
2. Optimized Prefix DP    | O(N^3) | O(N^2) | Best overall, handles N=100 Limits

Final Recommended Solution: Method 2 (Optimized Prefix DP)
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    // Method 1: Brute Force DP Transition (Conceptual/Reference)
    // Included to explicitly map out the O(N^4) logic before the algebraic optimization.
    long long maximumScore_ON4(vector<vector<int>>& grid) {
        int n = grid.size();
        const long long INF = 1e15;
        vector<vector<long long>> dp(n + 1, vector<long long>(n + 1, -INF));
        for (int h0 = 0; h0 <= n; ++h0) dp[0][h0] = 0;
        
        for (int col = 0; col < n - 1; ++col) {
            vector<vector<long long>> next_dp(n + 1, vector<long long>(n + 1, -INF));
            vector<long long> P(n + 1, 0), P_next(n + 1, 0);
            for (int i = 0; i < n; ++i) {
                P[i + 1] = P[i] + grid[i][col];
                P_next[i + 1] = P_next[i] + grid[i][col + 1];
            }
            
            for (int h_curr = 0; h_curr <= n; ++h_curr) {
                for (int h_next = 0; h_next <= n; ++h_next) {
                    for (int h_prev = 0; h_prev <= n; ++h_prev) {
                        if (dp[h_prev][h_curr] == -INF) continue;
                        
                        long long score = 0;
                        if (h_curr > h_next) score += P_next[h_curr] - P_next[h_next];
                        if (h_next > h_curr) {
                            int start = max(h_curr, h_prev);
                            if (h_next > start) score += P[h_next] - P[start];
                        }
                        next_dp[h_curr][h_next] = max(next_dp[h_curr][h_next], dp[h_prev][h_curr] + score);
                    }
                }
            }
            dp = next_dp;
        }
        
        long long ans = 0;
        for (int i = 0; i <= n; ++i) 
            for (int j = 0; j <= n; ++j) 
                ans = max(ans, dp[i][j]);
        return ans;
    }

    // Method 2: Final Recommended Solution - Optimized DP (O(N^3))
    long long maximumScore(vector<vector<int>>& grid) {
        int n = grid.size();
        const long long INF = 1e15; // Represents unreachable/invalid DP states
        
        // dp[h_prev][h_curr]: Max score up to current column where 
        // previous col has height `h_prev` and current col has height `h_curr`
        vector<vector<long long>> dp(n + 1, vector<long long>(n + 1, -INF));
        
        // Base case setup for the first column
        for (int h0 = 0; h0 <= n; ++h0) {
            dp[0][h0] = 0;
        }
        
        // Process sequentially column by column
        for (int col = 0; col < n - 1; ++col) {
            vector<vector<long long>> next_dp(n + 1, vector<long long>(n + 1, -INF));
            
            // 1-indexed Prefix sums for current and next column to calculate range sums in O(1)
            vector<long long> P(n + 1, 0);
            vector<long long> P_next(n + 1, 0);
            for (int i = 0; i < n; ++i) {
                P[i + 1] = P[i] + grid[i][col];
                P_next[i + 1] = P_next[i] + grid[i][col + 1];
            }
            
            for (int h_curr = 0; h_curr <= n; ++h_curr) {
                // Precompute optimal states for fixed h_curr to avoid O(N) h_prev loop
                
                // 1. Max DP where h_prev <= h_curr
                long long max_dp_le = -INF;
                for (int h_prev = 0; h_prev <= h_curr; ++h_prev) {
                    max_dp_le = max(max_dp_le, dp[h_prev][h_curr]);
                }
                
                // 2. Suffix Max array for DP where h_prev >= h_next
                vector<long long> suf_max_dp(n + 2, -INF);
                for (int h_prev = n; h_prev >= 0; --h_prev) {
                    suf_max_dp[h_prev] = max(suf_max_dp[h_prev + 1], dp[h_prev][h_curr]);
                }
                
                // 3. Running max for the volatile middle range: h_curr < h_prev < h_next
                long long running_max_A = -INF;
                
                // Determine `h_next` transition dynamically
                for (int h_next = 0; h_next <= n; ++h_next) {
                    if (h_next <= h_curr) {
                        // Case A: h_next is smaller or equal. Score gained on col+1
                        long long val = suf_max_dp[0]; // Maximum valid DP over all h_prev bounds
                        long long score_col1 = P_next[h_curr] - P_next[h_next]; 
                        next_dp[h_curr][h_next] = max(next_dp[h_curr][h_next], val + score_col1);
                    } else {
                        // Case B: h_next is larger. Score gained strictly on col
                        long long term1 = max_dp_le + P[h_next] - P[h_curr];
                        long long term2 = running_max_A + P[h_next];
                        long long term3 = suf_max_dp[h_next]; // h_prev >= h_next implies 0 score gained
                        
                        long long val = max({term1, term2, term3});
                        next_dp[h_curr][h_next] = max(next_dp[h_curr][h_next], val);
                        
                        // Dynamically update the running maximum for the next iteration step
                        running_max_A = max(running_max_A, dp[h_next][h_curr] - P[h_next]);
                    }
                }
            }
            dp = next_dp;
        }
        
        // The final answer is the maximum value retained in the completed DP table
        long long ans = 0;
        for (int h_prev = 0; h_prev <= n; ++h_prev) {
            for (int h_curr = 0; h_curr <= n; ++h_curr) {
                ans = max(ans, dp[h_prev][h_curr]);
            }
        }
        
        return ans;
    }
};
