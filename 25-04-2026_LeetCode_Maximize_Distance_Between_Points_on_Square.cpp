/*
Date: 25-04-2026
Problem Name: Maximize the Distance Between Points on a Square
Platform: LeetCode
Difficulty: Hard
Tags: Array, Binary Search, Two Pointers, Sparse Table (Binary Lifting), Greedy

Problem Summary:
Given `n` unique points on the boundary of a square of edge length `side`, select exactly `k` points 
such that the minimum Manhattan distance between any two selected points is maximized.

Methods to Solve:

1. Brute Force (Combinations)
   - Intuition: Generate all combinations of picking `k` points out of `n` points. Find the minimum 
     distance for each combination, and take the maximum of these minimums.
   - Approach: Backtracking / Recursion.
   - Dry Run (Small Example): N=4, K=4. Only 1 combination. Calculate distance between all adjacent pairs, return min.
   - Time Complexity: O(N choose K)
   - Space Complexity: O(K) for recursion depth.
   - Why better than previous method: N/A.
   - When to use: Never. Constraints (N, K <= 10^5) will immediately TLE.

2. Better Approach (Binary Search + Linear Jump Simulation)
   - Intuition: It's easier to verify if a distance `d` is possible than to find the max distance directly. 
     We can binary search the answer `d`. To verify `d`, unroll the square perimeter into a 1D array.
   - Approach: For a target distance `d`, iterate through each point as a starting position. Greedily 
     jump to the next point that is at least `d` distance away. Do this `k-1` times.
   - Time Complexity: O(N log N) + O(N * K * log(Max_Distance))
   - Space Complexity: O(N)
   - Why better than previous method: Avoids combinatorial explosion.
   - When to use: When `K` is very small (K <= 50). Fails here because K <= 10^5.

3. Optimal Approach (Binary Search + Binary Lifting / Sparse Table)
   - Intuition: The linear jump simulation is too slow. Since the "next valid point" for a fixed `d` 
     is deterministic and monotonic, we can precompute jumps in powers of 2 (Binary Lifting).
   - Approach: 
     a. Map 2D perimeter coordinates to a 1D line `[0, 4*side)`.
     b. Duplicate the array to handle circular wrap-around seamlessly (`2*N`).
     c. Binary search distance `d`.
     d. In `check(d)`, use two pointers to find the 1st jump `up[0][i]`.
     e. Build a Sparse Table where `up[step][i] = up[step-1][up[step-1][i]]`.
     f. For each start point, simulate `k` jumps in O(log k) using bitwise shifts.
   - Dry Run: d=5. `up[0][i]` gives next point >= P[i]+5. If k=5 (binary 101), we jump using 
     `up[2]` (4 jumps) then `up[0]` (1 jump). If final pos <= i + n, `d` is valid!
   - Time Complexity: O(N log N) for sort. Check takes O(N log K). Total: O(N log N + N * log K * log(Max_Distance)).
   - Space Complexity: O(N log K) for the Binary Lifting table.
   - Why better than previous method: Reduces jump simulation from O(K) to O(log K), eliminating TLE.
   - When to use: Standard competitive programming technique for jumping along graphs/arrays.

Comparison Table:
Method               | TC                                   | SC         | Best Use Case
---------------------|--------------------------------------|------------|---------------------------------
Brute Force          | O(N choose K)                        | O(K)       | Educational only
Linear Jump          | O(N log N + N * K * log(Max_Dist))   | O(N)       | Small K values
Binary Lifting       | O(N log N + N * logK * log(Max_Dist))| O(N log K) | Large constraints (N, K <= 10^5)

Final Recommended Solution: Binary Search + Binary Lifting (Optimal Approach)
*/

#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

class Solution {
public:
    int maxDistance(int side, vector<vector<int>>& points, int k) {
        int n = points.size();
        long long perim = 4LL * side;
        vector<long long> P(n);
        
        // 1. Flatten the 2D square boundary into a 1D circular perimeter segment
        for (int i = 0; i < n; i++) {
            long long x = points[i][0], y = points[i][1];
            if (y == 0 && x < side) P[i] = x;
            else if (x == side && y < side) P[i] = side + y;
            else if (y == side && x > 0) P[i] = 3LL * side - x;
            else P[i] = 4LL * side - y;
        }
        
        // Sort points along the perimeter
        sort(P.begin(), P.end());
        
        // 2. Unroll the circular array to handle wrap-around gracefully
        vector<long long> p2(2 * n);
        for (int i = 0; i < n; ++i) {
            p2[i] = P[i];
            p2[i + n] = P[i] + perim;
        }
        
        // Calculate max steps needed for binary lifting
        int LOG = 32 - __builtin_clz(k);
        
        // up[step][i] will store the index after making (2^step) jumps starting from i
        vector<vector<int>> up(LOG, vector<int>(2 * n + 1, 2 * n));
        
        // Helper lambda to check if a minimum distance 'd' is achievable
        auto check = [&](long long d) -> bool {
            
            // Base Case for Jumps (2^0 = 1 jump) using Two Pointers
            for (int i = 0, j = 0; i < 2 * n; i++) {
                while (j < 2 * n && p2[j] - p2[i] < d) {
                    j++;
                }
                up[0][i] = j;
            }
            up[0][2 * n] = 2 * n; // Sink/Out-of-bounds state
            
            // Build the Sparse Table (Binary Lifting)
            for (int step = 1; step < LOG; step++) {
                for (int i = 0; i <= 2 * n; i++) {
                    up[step][i] = up[step - 1][up[step - 1][i]];
                }
            }
            
            // Validate if ANY starting point allows 'k' valid jumps within one full perimeter revolution
            for (int i = 0; i < n; i++) {
                int curr = i;
                for (int step = 0; step < LOG; step++) {
                    // If the step-th bit of k is set, take 2^step jumps
                    if ((k >> step) & 1) {
                        curr = up[step][curr];
                    }
                }
                // If we placed k points and haven't exceeded the unrolled array's length (i + n)
                if (curr <= i + n) return true;
            }
            return false;
        };
        
        // 3. Binary Search over the Answer Space
        long long lo = 1, hi = perim / k, ans = 1;
        
        while (lo <= hi) {
            long long mid = lo + (hi - lo) / 2;
            
            if (check(mid)) {
                ans = mid;       // Valid distance, try to push for a larger one
                lo = mid + 1; 
            } else {
                hi = mid - 1;    // Distance too large, scale back
            }
        }
        
        return ans;
    }
};
