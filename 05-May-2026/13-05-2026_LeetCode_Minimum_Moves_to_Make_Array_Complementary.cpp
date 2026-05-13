/*
Date: 13-05-2026
Problem Name: Minimum Moves to Make Array Complementary
Platform: LeetCode (Problem 1674)
Difficulty: Medium
Tags: Array, Hash Table, Prefix Sum, Difference Array

Problem Summary:
Given an even-length array 'nums' and an integer 'limit', we want to make the array 
"complementary." An array is complementary if nums[i] + nums[n-1-i] equals the 
same target sum 'S' for all pairs. We can replace any element with a value 
between 1 and 'limit'. The goal is to find the minimum moves required.

Methods to Solve:
1. Brute Force (Target Sum Enumeration)
2. Difference Array / Prefix Sum (Optimal)

---------------------------------------------------------------------------
1. Brute Force
- Intuition: Iterate through every possible target sum 'S' from 2 to 2*limit.
- Approach: For each target sum, calculate the moves required for every pair 
  (nums[i], nums[n-1-i]).
- Time Complexity: O(limit * N)
- Space Complexity: O(1)
- Why better: It isn't; it will result in TLE (Time Limit Exceeded) for large constraints.
- When to use: Only for very small N and limit.

---------------------------------------------------------------------------
2. Optimal Approach (Difference Array / Sweep Line)
- Intuition: For any pair (a, b), the number of moves needed to reach a target sum S 
  changes at specific "boundary" sums. We can use a difference array to track 
  these transitions across all possible sums [2, 2*limit].
  
- Approach:
  Let min_val = min(a, b) and max_val = max(a, b).
  - Range [2, 2*limit]: Default to 2 moves per pair.
  - Range [1 + min_val, limit + max_val]: Only 1 move is needed (replace the smaller 
    val with 1 or the larger with limit).
  - At exactly S = a + b: 0 moves are needed.
  
  Using a difference array `diff`:
  1. For each pair, start by assuming 2 moves: diff[2] += 2.
  2. Transition to 1 move at (1 + min_val): diff[1 + min_val] -= 1.
  3. Transition to 0 moves at (a + b): diff[a + b] -= 1.
  4. Transition back to 1 move at (a + b + 1): diff[a + b + 1] += 1.
  5. Transition back to 2 moves at (limit + max_val + 1): diff[limit + max_val + 1] += 1.
  
- Dry Run: nums = [1,2,4,3], limit = 4. Pair (1,3), (2,4).
  Pair (1,3): min=1, max=3. Sum=4.
  Moves: [2,2] (2 moves), [2, 5] (1 move), [4] (0 moves), [6, 8] (2 moves).
  Difference array tracks these shifts.
  
- Time Complexity: O(N + limit) - One pass over pairs, one pass over the diff array.
- Space Complexity: O(limit) - To store the difference array up to 2*limit.
- Why better: It processes each pair in O(1) and finds the global minimum in one linear scan.
- When to use: Best for large constraints where N and limit are up to 10^5.

---------------------------------------------------------------------------
Comparison Table:
Method         | TC           | SC       | Best Use Case
-------------------------------------------------------
Brute Force    | O(limit * N) | O(1)     | Small constraints
Optimal (Diff) | O(N + limit) | O(limit) | Competitive Programming / Large Data

Final Recommended Solution: Difference Array (Method 2)
*/

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    /**
     * @brief Calculates the minimum moves to make the array complementary.
     * uses the Difference Array technique to track move requirements across
     * all possible target sums.
     */
    int minMoves(vector<int>& nums, int limit) {
        int n = nums.size();
        // Difference array to track moves for target sums from 2 to 2*limit
        // Size is 2*limit + 2 to handle boundaries safely
        vector<int> diff(2 * limit + 2, 0);

        for (int i = 0; i < n / 2; ++i) {
            int a = nums[i];
            int b = nums[n - 1 - i];

            // Boundaries for transitions
            int min_val = min(a, b);
            int max_val = max(a, b);

            // 1. For all sums [2, 2*limit], we need at most 2 moves.
            diff[2] += 2;
            
            // 2. For sums in range [min_val + 1, max_val + limit], 
            // we only need 1 move (change one element).
            // We subtract 1 from the 2 moves we just added.
            diff[min_val + 1] -= 1;
            
            // 3. For the exact sum (a + b), we need 0 moves.
            // We subtract another 1 from the 1 move state.
            diff[a + b] -= 1;
            
            // 4. After the exact sum (a + b), we go back to 1 move.
            diff[a + b + 1] += 1;
            
            // 5. After (max_val + limit), we go back to 2 moves.
            diff[max_val + limit + 1] += 1;
        }

        int min_moves = n; // Max possible moves is N
        int current_moves = 0;

        // Sweep through the difference array to find the minimum moves
        for (int s = 2; s <= 2 * limit; ++s) {
            current_moves += diff[s];
            min_moves = min(min_moves, current_moves);
        }

        return min_moves;
    }
};
