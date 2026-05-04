/*
Date: 04-05-2026
Problem Name: 48. Rotate Image
Platform: LeetCode
Difficulty: Medium
Tags: Array, Math, Matrix

Problem Summary:
Given an n x n 2D matrix representing an image, rotate the image by 90 degrees (clockwise). 
You must rotate the image in-place, meaning you modify the input 2D matrix directly without allocating another 2D matrix.

Methods to Solve:
1. Brute Force (Using extra space)
2. Optimal Approach (Transpose + Reverse)

---------------------------------------------------------
Method 1: Brute Force
- Intuition: The first row of the original matrix becomes the last column of the rotated matrix, the second row becomes the second-to-last column, and so on.
- Approach: Create a temporary n x n matrix. Traverse the original matrix and place matrix[i][j] into new_matrix[j][n - 1 - i]. Finally, copy the elements back to the original matrix.
- Dry Run (Small Example):
  Input: [[1, 2], [3, 4]]
  (i=0, j=0) -> new_matrix[0][1] = 1
  (i=0, j=1) -> new_matrix[1][1] = 2
  (i=1, j=0) -> new_matrix[0][0] = 3
  (i=1, j=1) -> new_matrix[1][0] = 4
  Output: [[3, 1], [4, 2]]
- Time Complexity: O(N^2) where N is the number of rows/cols.
- Space Complexity: O(N^2) to store the intermediate matrix.
- Why better than previous method: N/A (Baseline).
- When to use: When you are allowed to use extra space and want the most straightforward mapping (fails this problem's strict in-place constraint).

Method 2: Optimal Approach
- Intuition: Rotating a matrix by 90 degrees clockwise is mathematically equivalent to first taking its transpose and then reflecting it horizontally (reversing each row).
- Approach: 
  1. Transpose the matrix: Swap matrix[i][j] with matrix[j][i] for all elements above the main diagonal.
  2. Reverse each row: Swap elements symmetrically within each row.
- Dry Run (Small Example):
  Input: [[1, 2], [3, 4]]
  After Transpose: [[1, 3], [2, 4]]
  After Reversing rows: [[3, 1], [4, 2]]
- Time Complexity: O(N^2) - We iterate through the matrix twice (once for transpose, once for reverse).
- Space Complexity: O(1) - All modifications are done in-place.
- Why better than previous method: Achieves the rotation without any extra memory allocation, fulfilling the O(1) auxiliary space constraint.
- When to use: This is the standard, most optimal way to perform in-place 90-degree matrix rotations.

Comparison Table:
Method          | TC     | SC     | Best Use Case
----------------|--------|--------|------------------------------
Brute Force     | O(N^2) | O(N^2) | When extra space is allowed
Optimal         | O(N^2) | O(1)   | Strict in-place requirements

Final Recommended Solution: Optimal Approach (Method 2)
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    // Method 1: Brute Force (Commented out as it violates the in-place constraint, kept for reference)
    /*
    void rotateBruteForce(vector<vector<int>>& matrix) {
        int n = matrix.size();
        vector<vector<int>> ans(n, vector<int>(n, 0));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                ans[j][n - 1 - i] = matrix[i][j];
            }
        }
        matrix = ans;
    }
    */

    // Method 2: Optimal Approach (Transpose + Reverse)
    void rotate(vector<vector<int>>& matrix) {
        int n = matrix.size();
        
        // Step 1: Transpose the matrix
        // Swap matrix[i][j] with matrix[j][i]
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                swap(matrix[i][j], matrix[j][i]);
            }
        }
        
        // Step 2: Reverse each row
        for (int i = 0; i < n; i++) {
            reverse(matrix[i].begin(), matrix[i].end());
        }
    }
};
