/**
 * File: 30-04-2026_LeetCode_Maximum_Path_Score_in_a_Grid.cpp
 * --------------------------------------------------------
 * Problem: 3742. Maximum Path Score in a Grid
 * Description: Find a path from (0,0) to (m-1, n-1) moving only Right or Down.
 * Maximize score while keeping total cost <= k.
 * 
 * Cell Values:
 * 0: Score +0, Cost +0
 * 1: Score +1, Cost +1
 * 2: Score +2, Cost +1
 * 
 * Author: Navinkumar Tirupati Tumma
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    /**
     * Approach: Dynamic Programming with Space Optimization
     * State: dp[j][c] = Max score at column 'j' with total cost 'c'
     * Complexity: Time O(M * N * K), Space O(N * K)
     */
    int maxPathScore(vector<vector<int>>& grid, int k) {
        int m = grid.size();
        int n = grid[0].size();

        // Constraint Optimization: Max possible cost is limited by path length
        k = min(k, m + n - 1);

        // dp[j][cost] stores the max score for the current row at column j
        // Initialized to -1 (unreachable state)
        vector<vector<int>> dp(n, vector<int>(k + 1, -1));

        // Start Cell (0, 0) logic
        int v0 = grid[0][0];
        int s0 = (v0 == 2) ? 2 : (v0 == 1 ? 1 : 0);
        int c0 = (v0 > 0) ? 1 : 0;

        if (c0 <= k) dp[0][c0] = s0;
        else return -1;

        // Process First Row (only movement from left)
        for (int j = 1; j < n; ++j) {
            int val = grid[0][j];
            int curr_s = (val == 2) ? 2 : (val == 1 ? 1 : 0);
            int curr_c = (val > 0) ? 1 : 0;

            for (int c = curr_c; c <= k; ++c) {
                if (dp[j - 1][c - curr_c] != -1) {
                    dp[j][c] = dp[j - 1][c - curr_c] + curr_s;
                }
            }
        }

        // Process Remaining Rows
        for (int i = 1; i < m; ++i) {
            vector<vector<int>> next_dp(n, vector<int>(k + 1, -1));
            for (int j = 0; j < n; ++j) {
                int val = grid[i][j];
                int curr_s = (val == 2) ? 2 : (val == 1 ? 1 : 0);
                int curr_c = (val > 0) ? 1 : 0;

                for (int c = curr_c; c <= k; ++c) {
                    // Transition 1: From Top (previous row 'dp')
                    if (dp[j][c - curr_c] != -1) {
                        next_dp[j][c] = max(next_dp[j][c], dp[j][c - curr_c] + curr_s);
                    }
                    // Transition 2: From Left (current row 'next_dp')
                    if (j > 0 && next_dp[j - 1][c - curr_c] != -1) {
                        next_dp[j][c] = max(next_dp[j][c], next_dp[j - 1][c - curr_c] + curr_s);
                    }
                }
            }
            dp = move(next_dp);
        }

        // Final Extraction: Find the highest score at the last cell within budget
        int result = -1;
        for (int c = 0; c <= k; ++c) {
            result = max(result, dp[n - 1][c]);
        }

        return result;
    }
};

/* 
================================================================================
EXAM NOTES & CONCLUSION:
--------------------------------------------------------------------------------
1. DEFINITION: This problem is a Resource-Constrained Shortest Path variation.
2. OPTIMAL SUBSTRUCTURE: The max score at (i, j, cost) depends on the max scores 
   at (i-1, j, cost - cell_cost) and (i, j-1, cost - cell_cost).
3. SPACE OPTIMIZATION: Instead of an O(M*N*K) 3D array, we use O(N*K) by 
   observing that we only need the previous row to calculate the current one.
4. EDGE CASES: Start cell cost > k (return -1), grid with all 0s, and k=0.
================================================================================
*/

int main() {
    Solution sol;
    // Example 1: grid = [[0, 1], [2, 0]], k = 1
    vector<vector<int>> grid = {{0, 1}, {2, 0}};
    int k = 1;
    std::cout << "Maximum Path Score: " << sol.maxPathScore(grid, k) << std::endl;
    return 0;
}
