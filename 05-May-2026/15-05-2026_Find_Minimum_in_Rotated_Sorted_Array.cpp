/*
Date: 15-05-2026
Problem Name: Find Minimum in Rotated Sorted Array
Platform: LeetCode
Difficulty: Medium
Tags: Array, Binary Search

Problem Summary:
Suppose an array of length n sorted in ascending order is rotated between 1 and n times. 
Given the sorted rotated array 'nums' of unique elements, return the minimum element 
of this array. The algorithm must run in O(log n) time.

Methods to Solve:
1. Brute Force (Linear Search)
2. Optimal Approach (Binary Search)

--------------------------------------------------------------------------------
1. Brute Force
- Intuition: Since we need to find the minimum element, we can simply traverse the entire 
  array and keep track of the minimum value encountered.
- Approach: Initialize a variable 'minVal' with the first element. Iterate through the 
  array from index 1 to n-1. Update 'minVal' if a smaller element is found.
- Dry Run: nums = [3,4,5,1,2] -> min starts at 3, updates to 1. Returns 1.
- Time Complexity: O(n)
- Space Complexity: O(1)
- Why better than previous method: N/A (Baseline)
- When to use: Only if the array is unsorted or very small where O(n) is acceptable.

--------------------------------------------------------------------------------
2. Optimal Approach (Binary Search)
- Intuition: In a rotated sorted array, there is an inflection point where the 
  sorted order breaks (e.g., [4,5,6,7, 0,1,2]). The element at the inflection point 
  is the minimum. We can use binary search to find this point by comparing the 
  middle element with the rightmost element.
- Approach: 
    - Use two pointers, 'low' and 'high'.
    - While 'low < high':
        - Calculate 'mid = low + (high - low) / 2'.
        - If 'nums[mid] > nums[high]', the minimum must be in the right half 
          (excluding mid), so 'low = mid + 1'.
        - Otherwise, the minimum is either 'mid' or to the left of it, 
          so 'high = mid'.
    - Return 'nums[low]'.
- Dry Run: nums = [4,5,6,7,0,1,2]
    - low=0, high=6, mid=3 (val=7). 7 > 2? Yes -> low = 4.
    - low=4, high=6, mid=5 (val=1). 1 > 2? No -> high = 5.
    - low=4, high=5, mid=4 (val=0). 0 > 1? No -> high = 4.
    - low == high. Return nums[4] = 0.
- Time Complexity: O(log n)
- Space Complexity: O(1)
- Why better than previous method: Reduces search time from linear to logarithmic, 
  meeting the problem's strict constraint.
- When to use: Always preferred for sorted or rotated sorted arrays with unique elements.

--------------------------------------------------------------------------------
Comparison Table:
Method         | TC       | SC   | Best Use Case
---------------------------------------------------------
Brute Force    | O(n)     | O(1) | Unsorted arrays
Binary Search  | O(log n) | O(1) | Rotated sorted arrays (Optimal)

Final Recommended Solution: Binary Search
*/

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    /**
     * @brief Finds the minimum element in a rotated sorted array using Binary Search.
     * * @param nums Vector of unique integers.
     * @return int The minimum element in the array.
     */
    int findMin(vector<int>& nums) {
        int low = 0;
        int high = nums.size() - 1;

        // Binary Search range-based approach
        while (low < high) {
            // Check if the current range is already sorted
            // If nums[low] < nums[high], the minimum is nums[low]
            if (nums[low] < nums[high]) {
                return nums[low];
            }

            int mid = low + (high - low) / 2;

            // If mid element is greater than the high element, 
            // the inflection point (minimum) is in the right half.
            if (nums[mid] > nums[high]) {
                low = mid + 1;
            } 
            // Otherwise, the minimum is in the left half (including mid).
            else {
                high = mid;
            }
        }

        return nums[low];
    }

    /**
     * @brief Alternative approach: One-pass Linear Search (Brute Force).
     * Provided for comparison as requested in documentation.
     */
    int findMinBruteForce(vector<int>& nums) {
        int minVal = nums[0];
        for (int i = 1; i < nums.size(); ++i) {
            if (nums[i] < minVal) {
                minVal = nums[i];
            }
        }
        return minVal;
    }
};
