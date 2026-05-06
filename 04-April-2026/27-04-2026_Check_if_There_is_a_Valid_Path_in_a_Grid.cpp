/*
Date: 27-04-2026
Problem Name: 1391. Check if There is a Valid Path in a Grid
Platform: LeetCode
Difficulty: Medium
Tags: Array, Breadth-First Search, Depth-First Search, Graph, Matrix

Problem Summary:
You are given an `m x n` grid where each cell represents a street type (from 1 to 6). 
Each street type connects two specific directions (e.g., Left-Right, Up-Down, Left-Down, etc.).
You need to determine if there is a valid path starting from the top-left cell (0, 0) to 
the bottom-right cell (m-1, n-1). A path is valid if the streets connect properly 
(i.e., if cell A connects to cell B, cell B must also have an opening connecting back to cell A).

Methods to Solve:
1. Depth-First Search (DFS)
2. Breadth-First Search (BFS)

-------------------------------------------------------------------------------
Method 1: Depth-First Search (DFS)
-------------------------------------------------------------------------------
Intuition:
We can treat the grid as a graph where each cell is a node, and valid connections 
are undirected edges. We can use DFS to explore paths from (0, 0). Before moving 
from the current cell to an adjacent cell, we must verify two things:
1. The current cell's street type allows movement in that specific direction.
2. The destination cell's street type has an opening facing the opposite direction 
   (reciprocal connection).

Approach:
- Define a mapping of directions for each of the 6 street types.
- Use a recursive DFS function, passing the current coordinates and a `visited` matrix.
- Iterate through the allowed directions of the current street type.
- Calculate the next coordinates `(nx, ny)`.
- If `(nx, ny)` is within bounds and unvisited, check if the street at `(nx, ny)` 
  has a direction `(-dx, -dy)` that points back to `(x, y)`.
- If a valid connection exists, mark it as visited and recursively call DFS.

Dry Run (small example):
Grid: [[2, 4, 3], [6, 5, 2]]
- Start at (0, 0), val = 2 (Up/Down). Allowed moves: Down to (1, 0).
- Check (1, 0), val = 6 (Right/Up). It has 'Up', which connects back to 'Down'. Valid.
- Move to (1, 0). Allowed moves: Right to (1, 1).
- Check (1, 1), val = 5 (Left/Up). It has 'Left', which connects back to 'Right'. Valid.
- DFS continues until target is reached or paths exhaust.

Time Complexity: O(M * N) - Where M is rows and N is columns. We visit each cell at most once.
Space Complexity: O(M * N) - For the visited array and the recursion stack in the worst case.
Why better than previous method: N/A (Standard approach).
When to use: When you want to explore paths deeply and quickly reach the destination if a 
direct path exists. Space can be an issue for massive grids due to recursion depth.

-------------------------------------------------------------------------------
Method 2: Breadth-First Search (BFS) [Optimal for Shortest Path / Iterative]
-------------------------------------------------------------------------------
Intuition:
Similar to DFS, but we explore the grid level by level using a Queue. This is generally 
safer for very large grids to avoid stack overflow issues inherent to deep recursion.

Approach:
- Initialize a queue and push the starting cell `(0, 0)`. Mark it as visited.
- While the queue is not empty, pop the front cell.
- If it's the target `(m-1, n-1)`, return true.
- Loop through the valid outgoing directions of the current cell.
- Check bounds, visited status, and the reciprocal connection of the neighbor.
- If valid, push the neighbor to the queue and mark it visited.

Time Complexity: O(M * N) - Every cell is processed at most once.
Space Complexity: O(M * N) - For the visited array and queue.
Why better than previous method: Avoids deep recursion stack overflows, making it safer for 
large constraints.
When to use: Preferred for grid traversal problems to ensure stability, or if we needed 
the shortest path (though not strictly required here, it's good practice).

Comparison Table:
Method | TC       | SC       | Best Use Case
-------------------------------------------------------------------------------
DFS    | O(M * N) | O(M * N) | Simple implementation, good for smaller grids.
BFS    | O(M * N) | O(M * N) | Safer for large grids, no recursion limit issues.

Final Recommended Solution: Method 2 (BFS) for iterative safety.
*/

#include <vector>
#include <queue>

using namespace std;

class Solution {
public:
    bool hasValidPath(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        
        // Base case: 1x1 grid
        if (m == 1 && n == 1) return true;
        
        // Visited matrix to prevent cycles
        vector<vector<bool>> visited(m, vector<bool>(n, false));
        queue<pair<int, int>> q;
        
        q.push({0, 0});
        visited[0][0] = true;
        
        // Define direction vectors for each street type (1-indexed to match problem)
        // dx, dy coordinates
        // Up: {-1, 0}, Down: {1, 0}, Left: {0, -1}, Right: {0, 1}
        vector<vector<vector<int>>> dirs = {
            {}, // 0: Placeholder (1-indexed)
            {{0, -1}, {0, 1}},   // 1: Left, Right
            {{-1, 0}, {1, 0}},   // 2: Up, Down
            {{0, -1}, {1, 0}},   // 3: Left, Down
            {{0, 1}, {1, 0}},    // 4: Right, Down
            {{0, -1}, {-1, 0}},  // 5: Left, Up
            {{0, 1}, {-1, 0}}    // 6: Right, Up
        };
        
        while (!q.empty()) {
            auto [x, y] = q.front();
            q.pop();
            
            // If we reached the bottom-right corner, a valid path exists
            if (x == m - 1 && y == n - 1) {
                return true;
            }
            
            int currentStreetType = grid[x][y];
            
            // Check all valid outgoing directions for the current street piece
            for (const auto& dir : dirs[currentStreetType]) {
                int nx = x + dir[0];
                int ny = y + dir[1];
                
                // Check boundaries and if already visited
                if (nx >= 0 && nx < m && ny >= 0 && ny < n && !visited[nx][ny]) {
                    
                    int nextStreetType = grid[nx][ny];
                    bool isConnected = false;
                    
                    // Verify if the next cell has a reciprocal opening pointing back to us
                    for (const auto& backDir : dirs[nextStreetType]) {
                        if (backDir[0] == -dir[0] && backDir[1] == -dir[1]) {
                            isConnected = true;
                            break;
                        }
                    }
                    
                    if (isConnected) {
                        visited[nx][ny] = true;
                        q.push({nx, ny});
                    }
                }
            }
        }
        
        return false; // Queue empty and target not reached
    }
};
