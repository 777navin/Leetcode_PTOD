/*
Date: 06-05-2026
Problem Name: 1861. Rotating the Box
Platform: LeetCode
Difficulty: Medium
Tags: Array, Two Pointers, Matrix

Problem Summary:
Given an m x n matrix representing a side-view of a box with stones ('#'), stationary obstacles ('*'), and empty spaces ('.'). The box is rotated 90 degrees clockwise, causing stones to fall due to gravity until they hit an obstacle, another stone, or the bottom. Gravity does not affect horizontal positions, and obstacles don't move. Return the n x m matrix after rotation and gravity.

Methods to Solve:
1. Brute Force (Rotate then Apply Gravity)
2. Optimal Approach (Apply Gravity then Rotate)

---------------------------------------------------------
Method 1: Rotate then Apply Gravity (Brute Force)
---------------------------------------------------------
- Intuition: Directly simulate the real-world action. First, rotate the entire box 90 degrees. Then, for each column in the rotated box, let the stones fall downwards.
- Approach: 
  1. Create a new n x m matrix and populate it by rotating the original grid 90 degrees clockwise.
  2. Iterate through each column of the new matrix from bottom to top. 
  3. Whenever a stone ('#') is found, shift it down as far as possible until it hits an obstacle, another stone, or the floor.
- Dry Run (Concept):
  Grid: ["#", ".", "*", "."]
  Rotated column: 
  [.]
  [*]
  [.]
  [#] <- moves down until it hits the obstacle or bottom.
- Time Complexity: O(m * n^2) in the worst case (if implemented naively where every stone checks every position below it).
- Space Complexity: O(m * n) for the resultant rotated matrix.
- Why better than previous method: N/A.
- When to use: When ease of implementation is prioritized over performance, though it may TLE on larger constraints.

---------------------------------------------------------
Method 2: Optimal Approach (Apply Gravity then Rotate)
---------------------------------------------------------
- Intuition: Instead of dealing with vertical gravity after rotation, we can treat gravity as a horizontal shift to the right in the original matrix. A stone falls to the bottom of a rotated column, which is equivalent to moving to the extreme right of its original row.
- Approach:
  1. Process the original `boxGrid` row by row.
  2. Use a two-pointer technique for each row. Maintain an `emptyPos` pointer starting from the rightmost index (n - 1).
  3. Iterate from right to left:
     - If we encounter an obstacle ('*'), it blocks stones. Update `emptyPos` to just before the obstacle (current index - 1).
     - If we encounter a stone ('#'), move it to `emptyPos`, place a '.' at the current index, and decrement `emptyPos`.
     - If we encounter an empty space ('.'), just continue.
  4. After all rows are processed, create the n x m result matrix and perform the 90-degree clockwise rotation.
- Dry Run (Small Example):
  Row: ["#", ".", "*", "."]
  Right to left traversal:
  - i = 3 ('.'): emptyPos stays 3.
  - i = 2 ('*'): obstacle found, emptyPos = 2 - 1 = 1.
  - i = 1 ('.'): emptyPos stays 1.
  - i = 0 ('#'): move stone to emptyPos (1). Grid becomes [".", "#", "*", "."]. emptyPos = 0.
  Rotation turns this processed row into the correct falling column.
- Time Complexity: O(m * n) - We visit each cell a constant number of times (once for gravity, once for rotation).
- Space Complexity: O(m * n) to store and return the final rotated box.
- Why better than previous method: Prevents repeated traversal of paths when simulating gravity, bringing the time complexity down to linear with respect to the number of cells.
- When to use: This is the optimal and recommended solution for competitive programming and interviews.

Comparison Table:
Method         | TC         | SC       | Best Use Case
-----------------------------------------------------------------
Brute Force    | O(m * n^2) | O(m * n) | Small grids / basic intuition
Optimal        | O(m * n)   | O(m * n) | Standard constraints (m, n <= 500)

Final Recommended Solution: Method 2 (Optimal Approach)
*/

#include <vector>

using namespace std;

class Solution {
public:
    vector<vector<char>> rotateTheBox(vector<vector<char>>& boxGrid) {
        int m = boxGrid.size();
        int n = boxGrid[0].size();
        
        // Step 1: Apply gravity row by row (shifting stones to the right)
        for (int i = 0; i < m; ++i) {
            int emptyPos = n - 1; // Pointer to the lowest available empty spot
            
            // Traverse from right to left
            for (int j = n - 1; j >= 0; --j) {
                if (boxGrid[i][j] == '*') {
                    // Obstacle resets the lowest empty position to just above it
                    emptyPos = j - 1;
                } else if (boxGrid[i][j] == '#') {
                    // Move the stone to the lowest empty position
                    boxGrid[i][j] = '.'; 
                    boxGrid[i][emptyPos] = '#';
                    emptyPos--; // Decrement the available empty position
                }
            }
        }
        
        // Step 2: Rotate the box 90 degrees clockwise
        vector<vector<char>> rotatedBox(n, vector<char>(m));
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                // Mapping: row 'i' becomes column 'm - 1 - i', column 'j' becomes row 'j'
                rotatedBox[j][m - 1 - i] = boxGrid[i][j];
            }
        }
        
        return rotatedBox;
    }
};
