/*
Date: 14-05-2026
Problem Name: Check if Array is Good
Platform: LeetCode
Difficulty: Easy
Tags: Array, Hash Table, Sorting, Counting

Problem Summary:
An array is considered "good" if it is a permutation of base[n] = [1, 2, ..., n-1, n, n].
This means for an array of length len, n must be len - 1. 
The array must contain numbers from 1 to n-1 exactly once, and the number n exactly twice.

Methods to Solve:
1. Sorting Approach: Sort the array and check if the first len-1 elements match 1 to n, and the last element also equals n.
2. Counting/Frequency Array: Count occurrences of each number and verify against the base[n] requirements.
3. Frequency Array (Optimal): Since constraints are small (nums.length <= 100), a simple frequency array is highly efficient.

Method 1: Sorting Approach
- Intuition: If we sort the array, a "good" array must look exactly like [1, 2, 3, ..., n, n].
- Approach: Sort the array. Check if nums[i] == i + 1 for all i < len - 1, and nums[len - 1] == len - 1.
- Dry Run: nums = [1, 3, 3, 2] -> Sorted: [1, 2, 3, 3]. len=4, n=3.
           Indices 0,1,2 match 1,2,3. Last element (index 3) is 3. Result: True.
- Time Complexity: O(N log N) due to sorting.
- Space Complexity: O(1) or O(N) depending on the sorting algorithm implementation.
- Why better than previous method: N/A
- When to use: When space is a major constraint and modifying the input is allowed.

Method 2: Frequency Array (Optimal)
- Intuition: Use the property that we know exactly how many times each number should appear.
- Approach: 
    1. Find max element 'n'. 
    2. Check if array length is exactly n + 1. 
    3. Use a frequency array to count occurrences. 
    4. Verify 1 to n-1 appear once, and n appears twice.
- Dry Run: nums = [2, 1, 3], max=3. Length is 3, but base[3] needs length 4. Result: False.
- Time Complexity: O(N) to traverse the array.
- Space Complexity: O(N) to store frequencies.
- Why better than previous method: Faster execution time (Linear vs Log-linear).
- When to use: Default choice for most competitive programming scenarios with these constraints.

Comparison Table:
Method           | TC       | SC   | Best Use Case
-----------------------------------------------------------
Sorting          | O(N logN)| O(1) | Space-constrained environments.
Frequency Array  | O(N)     | O(N) | Optimal time performance.

Final Recommended Solution:
The Frequency Array approach is recommended for its O(N) efficiency and simplicity given the constraints.
*/

#include <vector>
#include <algorithm>
#include <map>

using namespace std;

class Solution {
public:
    /**
     * @brief Checks if the given array is a permutation of base[n] = [1, 2, ..., n-1, n, n].
     * * @param nums Vector of integers to check.
     * @return true if the array is "good", false otherwise.
     */
    bool isGood(vector<int>& nums) {
        int n_plus_one = nums.size();
        if (n_plus_one < 2) return false; // base[n] length is at least 2 ([1,1])

        int n = n_plus_one - 1;
        vector<int> count(n + 1, 0);

        for (int x : nums) {
            // If any number exceeds n, it cannot be a permutation of base[n]
            if (x > n || x < 1) return false;
            count[x]++;
        }

        // Check frequency requirements:
        // 1 to n-1 must appear exactly once
        for (int i = 1; i < n; ++i) {
            if (count[i] != 1) return false;
        }

        // n must appear exactly twice
        return count[n] == 2;
    }

    /* Alternative implementation using Sorting (GitHub Ready)
    bool isGoodSorting(vector<int>& nums) {
        int len = nums.size();
        sort(nums.begin(), nums.end());
        int n = len - 1;
        
        for (int i = 0; i < n; i++) {
            if (nums[i] != i + 1) return false;
        }
        return nums[len - 1] == n;
    }
    */
};
