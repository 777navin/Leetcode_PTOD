/*
Date: 09-05-2026
Problem Name: Cyclically Rotating a Grid (LeetCode 1914)
Platform: LeetCode
Difficulty: Medium
Tags: Array, Matrix, Simulation

Problem Summary:
You are given an m x n integer matrix where m and n are even, along with an integer k. 
The matrix consists of several concentric layers. You need to apply a cyclic rotation to each 
layer of the matrix in a counter-clockwise direction by k steps. Return the modified matrix.

Methods to Solve:
1. Brute Force (Step-by-step Simulation)
2. Optimal Approach (1D Array Extraction & Modulo Arithmetic)

===============================================================================
1. Brute Force (Step-by-step Simulation)
===============================================================================
- Intuition: The most straightforward way is to simulate the rotation exactly as 
  described, moving every element in a layer counter-clockwise by 1 step, and 
  repeating this process k times.
- Approach: For each layer, store the top-left element, shift the top row left, 
  right column up, bottom row right, and left column down. Place the stored element. 
  Repeat k times.
- Time Complexity: $O(K \times M \times N)$ - We touch the perimeter elements k times.
- Space Complexity: $O(1)$ - In-place updates.
- Why better/worse: This method will result in a Time Limit Exceeded (TLE) because k 
  can be up to 10^9. It does unnecessary work wrapping around the matrix repeatedly.
- When to use: Never for large k. Only viable if k is guaranteed to be very small.

===============================================================================
2. Optimal Approach (1D Array Extraction & Modulo Arithmetic)
===============================================================================
- Intuition: Since k can be incredibly large (up to 10^9), full rotations of a layer 
  (where it ends up exactly where it started) are redundant. We can eliminate redundant 
  rotations by taking `k % layer_length`.
- Approach: 
  1. Iterate layer by layer from the outside in.
  2. For a specific layer defined by bounds (top, bottom, left, right), extract all 
     its elements in counter-clockwise order into a 1D vector.
  3. Calculate the effective rotations needed: `effective_k = k % vector.size()`.
  4. Traverse the same layer bounds and place the elements back from the 1D vector, 
     starting at index `effective_k` and wrapping around.
- Dry Run (Small Example): 
  Matrix 2x2, k=1. Layer is extracted as: [grid[0][0], grid[1][0], grid[1][1], grid[0][1]] 
  -> [40, 30, 20, 10]. k=1 % 4 = 1. We put elements back starting from index 1.
- Time Complexity: $O(M \times N)$ - Every element is extracted once and inserted once.
- Space Complexity: $O(M + N)$ - Space needed for the 1D vector of the outermost layer.
- Why better: Easily handles k = 10^9 natively in standard O(M x N) time.
- When to use: This is the definitive solution for this problem.

Comparison Table:
Method         | TC                | SC         | Best Use Case
-------------------------------------------------------------------------------
Brute Force    | $O(K \times M \times N)$ | $O(1)$     | Small k constraints
Optimal Method | $O(M \times N)$   | $O(M + N)$ | Large k, optimal performance

Final Recommended Solution: Optimal Approach (Implemented below)
*/

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    // Optimal Approach: 1D Array Extraction
    vector<vector<int>> rotateGrid(vector<vector<int>>& grid, int k) {
        int m = grid.size();
        int n = grid[0].size();
        
        // Number of layers is min(m, n) / 2
        int num_layers = min(m, n) / 2;
        
        for (int l = 0; l < num_layers; ++l) {
            int top = l;
            int bottom = m - 1 - l;
            int left = l;
            int right = n - 1 - l;
            
            vector<int> layer;
            
            // 1. Extract the layer counter-clockwise
            // Top row (Left to Right)
            for (int j = left; j <= right; ++j) {
                layer.push_back(grid[top][j]);
            }
            // Right column (Top+1 to Bottom)
            for (int i = top + 1; i <= bottom; ++i) {
                layer.push_back(grid[i][right]);
            }
            // Bottom row (Right-1 to Left)
            for (int j = right - 1; j >= left; --j) {
                layer.push_back(grid[bottom][j]);
            }
            // Left column (Bottom-1 to Top+1)
            for (int i = bottom - 1; i > top; --i) {
                layer.push_back(grid[i][left]);
            }
            
            // 2. Calculate effective rotations
            int len = layer.size();
            int effective_k = k % len;
            
            // 3. Put elements back shifted by effective_k
            int idx = effective_k;
            auto get_next_val = [&]() {
                int val = layer[idx];
                idx = (idx + 1) % len;
                return val;
            };
            
            // Top row (Left to Right)
            for (int j = left; j <= right; ++j) {
                grid[top][j] = get_next_val();
            }
            // Right column (Top+1 to Bottom)
            for (int i = top + 1; i <= bottom; ++i) {
                grid[i][right] = get_next_val();
            }
            // Bottom row (Right-1 to Left)
            for (int j = right - 1; j >= left; --j) {
                grid[bottom][j] = get_next_val();
            }
            // Left column (Bottom-1 to Top+1)
            for (int i = bottom - 1; i > top; --i) {
                grid[i][left] = get_next_val();
            }
        }
        
        return grid;
    }
};
