/*
Date: 01-05-2026
Problem Name: 396. Rotate Function
Platform: LeetCode
Difficulty: Medium
Tags: Array, Math, Dynamic Programming

Problem Summary:
Given an integer array 'nums' of length 'n', we define a rotation function F(k) 
where arr_k is the array obtained by rotating 'nums' by k positions clockwise.
F(k) = (0 * arr_k[0]) + (1 * arr_k[1]) + ... + ((n-1) * arr_k[n-1]).
The goal is to return the maximum value of F(0), F(1), ..., F(n-1).

Methods to Solve:
1. Brute Force (Simulation)
2. Optimal Mathematical Approach (Sliding Window/DP Pattern)

-------------------------------------------------------------------------------
1. Method: Brute Force
- Intuition: Literally rotate the array 'k' times and calculate the sum for each.
- Approach: Use a nested loop where the outer loop runs 'n' times for each k, 
            and the inner loop calculates the sum.
- Time Complexity: O(n²)
- Space Complexity: O(1) (if calculating on the fly) or O(n) (if rotating)
- Why better than previous: N/A (Baseline)
- When to use: Only when n is very small (n < 1000).

2. Method: Optimal Mathematical Approach
- Intuition: Find a relationship between F(k) and F(k-1) to avoid re-calculation.
- Approach: 
    Let S = sum of all elements in nums.
    F(0) = 0*a + 1*b + 2*c + 3*d
    F(1) = 0*d + 1*a + 2*b + 3*c
    F(1) - F(0) = a + b + c - 3*d
    Adding and subtracting 'd':
    F(1) - F(0) = (a + b + c + d) - 4*d
    F(1) = F(0) + S - n * nums[n-1]
    General Formula: F(k) = F(k-1) + S - n * nums[n-k]
- Dry Run: nums = [4,3,2,6], n=4
    S = 15
    F(0) = (0*4)+(1*3)+(2*2)+(3*6) = 25
    F(1) = 25 + 15 - 4*6 = 25 + 15 - 24 = 16
    F(2) = 16 + 15 - 4*2 = 16 + 15 - 8 = 23
    F(3) = 23 + 15 - 4*3 = 23 + 15 - 12 = 26
    Max = 26.
- Time Complexity: O(n)
- Space Complexity: O(1)
- Why better than previous: Reduces time from quadratic to linear by using 
                            the prefix sum property.
- When to use: Always for this problem.

-------------------------------------------------------------------------------
Comparison Table:
Method         | TC    | SC   | Best Use Case
---------------|-------|------|-------------------------
Brute Force    | O(n²) | O(1) | Small constraints
Optimal Math   | O(n)  | O(1) | Large arrays (GitHub Ready)

Final Recommended Solution: Optimal Mathematical Approach
*/

#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

class Solution {
public:
    /**
     * @brief Calculates the maximum value of the rotation function F(k).
     * Uses the mathematical recurrence: F(k) = F(k-1) + sum(nums) - n * last_element_of_rotation
     * 
     * @param nums Input integer array
     * @return Maximum value of F(k) for all k in [0, n-1]
     */
    int maxRotateFunction(vector<int>& nums) {
        long long n = nums.size();
        if (n == 0) return 0;

        long long current_f = 0;
        long long array_sum = 0;

        // Calculate F(0) and the total sum of the array
        for (int i = 0; i < n; ++i) {
            array_sum += nums[i];
            current_f += (long long)i * nums[i];
        }

        long long max_f = current_f;

        // Iterate from 1 to n-1 to find F(k) using the transition formula
        // We go backwards through the array to pick the element that drops its 
        // multiplier from (n-1) to 0 in each rotation.
        for (int k = 1; k < n; ++k) {
            // Formula: F(k) = F(k-1) + Sum - n * nums[n-k]
            current_f = current_f + array_sum - n * nums[n - k];
            max_f = max(max_f, current_f);
        }

        return (int)max_f;
    }
};
