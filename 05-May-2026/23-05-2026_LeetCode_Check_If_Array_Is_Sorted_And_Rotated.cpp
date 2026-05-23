/*
Date: 23-05-2026
Problem Name: Check if Array Is Sorted and Rotated (LeetCode 1752)
Platform: LeetCode
Difficulty: Easy
Tags: Array

Problem Summary:
Given an array `nums`, return true if the array was originally sorted in 
non-decreasing order, then rotated some number of positions (including zero). 
Otherwise, return false. Duplicates may exist in the array.

Methods to Solve:
1. Brute Force (Check all rotations)
2. Optimal Approach (Count inversion/drop-off points)

--------------------------------------------------------------------------------

Method 1: Brute Force Approach
- Intuition:
  An array of size N can be rotated at most N times. We can simulate each 
  rotation and check if any resulting array configuration is sorted in 
  non-decreasing order.
- Approach:
  1. Loop through all possible rotation offsets `i` from 0 to N-1.
  2. For each offset, construct or simulate the rotated array.
  3. Validate if the simulated array is sorted. If it is, return true.
  4. If no rotation yields a sorted array after checking all offsets, return false.
- Dry Run:
  nums = [3,4,5,1,2]
  - Rotate by 0: [3,4,5,1,2] -> Not sorted
  - Rotate by 1: [4,5,1,2,3] -> Not sorted
  - Rotate by 2: [1,2,3,4,5] -> Sorted! -> Returns true.
- Time Complexity: O(N^2) - N rotations, and each check takes O(N) time.
- Space Complexity: O(N) - To store the rotated array copy.
- Why better than previous method: Base baseline approach.
- When to use: When constraints are extremely small (N <= 20).

--------------------------------------------------------------------------------

Method 2: Optimal Approach (Count Inversions)
- Intuition:
  If a non-decreasing sorted array is rotated, it can possess at most ONE 
  "drop-off" point (an element that is strictly greater than its next element). 
  If it has zero drop-offs, it's already sorted. If it has one drop-off, the 
  rotation broke the sequence exactly once. If it has more than one, it cannot 
  be a single rotation of a sorted array.
- Approach:
  1. Initialize a `count` variable to 0.
  2. Traverse the array and compare `nums[i]` with the next element.
  3. Use modulo arithmetic `nums[(i + 1) % n]` to naturally check the boundary condition 
     where the last element wraps around to compare with the first element.
  4. If `nums[i] > nums[(i + 1) % n]`, increment `count`.
  5. If at any point `count > 1`, we can early-exit and return false.
  6. Return true if `count <= 1`.
- Dry Run:
  nums = [3,4,5,1,2], n = 5
  - i = 0: 3 <= 4 (count = 0)
  - i = 1: 4 <= 5 (count = 0)
  - i = 2: 5 > 1  (count = 1) -> Drop-off found!
  - i = 3: 1 <= 2 (count = 1)
  - i = 4: 2 <= 3 (nums[4] <= nums[0]) (count = 1)
  End loop. count is 1. Returns true.
- Time Complexity: O(N) - Single pass traversal.
- Space Complexity: O(1) - Uses only constant auxiliary variables.
- Why better than previous method: Drops time from quadratic to linear and uses no extra memory.
- When to use: Ideal choice for production and technical interviews.

--------------------------------------------------------------------------------

Comparison Table:
Method       | TC     | SC   | Best Use Case
------------------------------------------------------
Brute Force  | O(N^2) | O(N) | Educational/Testing
Optimal      | O(N)   | O(1) | Production & Interview

Final Recommended Solution: Method 2 (Optimal Approach)
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    // Approach 2: Optimal Tracking of Inversion Points
    bool check(vector<int>& nums) {
        int dropCount = 0;
        int n = nums.size();
        
        for (int i = 0; i < n; ++i) {
            // Check if current element is greater than the next element (circularly)
            if (nums[i] > nums[(i + 1) % n]) {
                dropCount++;
            }
            
            // Early optimization: More than 1 drop means it can't be a single rotation of a sorted array
            if (dropCount > 1) {
                return false;
            }
        }
        
        return true;
    }

    // Approach 1: Brute Force (Included for comprehensive documentation references)
    bool checkBruteForce(vector<int>& nums) {
        int n = nums.size();
        for (int offset = 0; offset < n; ++offset) {
            bool isSorted = true;
            for (int i = 0; i < n - 1; ++i) {
                if (nums[(offset + i) % n] > nums[(offset + i + 1) % n]) {
                    isSorted = false;
                    break;
                }
            }
            if (isSorted) return true;
        }
        return false;
    }
};
