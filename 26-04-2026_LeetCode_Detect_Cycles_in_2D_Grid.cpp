/*
Date: 26-04-2026
Problem Name: 1559. Detect Cycles in 2D Grid
Platform: LeetCode
Difficulty: Medium
Tags: Array, Depth-First Search, Breadth-First Search, Union Find, Matrix

Problem Summary:
Given an m x n 2D array of characters 'grid', find if there exists any cycle consisting of the 
same value in the grid. A cycle is a path of length 4 or more that starts and ends at the 
same cell. You can move in four directions (up, down, left, right) to an adjacent cell if it 
has the same value. You cannot move back to the cell you immediately came from.

Methods to Solve:
1. Depth First Search (DFS) - Optimal for cycle detection in graphs/grids.
2. Breadth First Search (BFS) - Similar logic to DFS but uses a queue.
3. Disjoint Set Union (DSU) - Efficient for checking connectivity and cycles.

---------------------------------------------------------------------------
Method 1: Depth First Search (DFS) [Optimal Approach]

- Intuition:
  Treat the grid as an undirected graph where each cell is a node and adjacent cells 
  with the same character have an edge. A cycle exists if we visit a node that is 
  already visited and is NOT the immediate parent of the current node.

- Approach:
  1. Iterate through each cell of the grid.
  2. If a cell is not visited, start a DFS from that cell.
  3. In the DFS, pass the current coordinates, the character value, and the coordinates 
     of the parent cell (to avoid moving back immediately).
  4. For each neighbor with the same character:
     - If it's not visited, recurse.
     - If it is visited and is NOT the parent, a cycle is found.

- Dry Run:
  Grid: [['a', 'a'], ['a', 'a']]
  (0,0) -> Visited. Neighbors: (0,1), (1,0).
  Move to (0,1). Parent is (0,0). Neighbors: (1,1), (0,0).
  (0,0) is parent, skip. Move to (1,1).
  In (1,1), Parent is (0,1). Neighbors: (1,0), (0,1).
  (0,1) is parent, skip. Move to (1,0).
  In (1,0), Parent is (1,1). Neighbors: (0,0), (1,1).
  (0,0) is already visited and NOT parent of (1,0) -> Cycle Found!

- Time Complexity: O(M * N), where M and N are dimensions. Every cell is visited once.
- Space Complexity: O(M * N) for the visited array and recursion stack.
- Why better: Standard, intuitive, and uses minimal memory compared to DSU.
- When to use: General cycle detection in grids.

---------------------------------------------------------------------------
Comparison Table:
Method | TC | SC | Best Use Case
DFS    | O(M*N) | O(M*N) | Simple implementation, standard for cycles.
BFS    | O(M*N) | O(M*N) | Avoiding deep recursion stacks.
DSU    | O(M*N*α) | O(M*N) | Dynamic connectivity or incremental grid updates.

Final Recommended Solution: DFS (Class-based for LeetCode)
*/

#include <vector>

using namespace std;

class Solution {
public:
    /**
     * @brief Detects if a cycle exists in the grid using DFS.
     * * @param grid 2D grid of characters
     * @return true if a cycle exists, false otherwise
     */
    bool containsCycle(vector<vector<char>>& grid) {
        int rows = grid.size();
        int cols = grid[0].size();
        vector<vector<bool>> visited(rows, vector<bool>(cols, false));

        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (!visited[i][j]) {
                    // Start DFS for unvisited component
                    if (dfs(grid, visited, i, j, -1, -1, grid[i][j])) {
                        return true;
                    }
                }
            }
        }
        return false;
    }

private:
    // Direction vectors for moving Right, Left, Down, Up
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};

    /**
     * @brief Standard DFS for detecting cycles in an undirected graph (grid).
     * * @param grid The input grid
     * @param visited Matrix to keep track of visited nodes
     * @param r Current row
     * @param c Current column
     * @param pr Parent row
     * @param pc Parent column
     * @param target The character value we are looking for in the cycle
     * @return true if cycle found
     */
    bool dfs(vector<vector<char>>& grid, vector<vector<bool>>& visited, int r, int c, int pr, int pc, char target) {
        visited[r][c] = true;

        for (int i = 0; i < 4; ++i) {
            int nr = r + dx[i];
            int nc = c + dy[i];

            // Boundary and Value Check
            if (nr >= 0 && nr < grid.size() && nc >= 0 && nc < grid[0].size() && grid[nr][nc] == target) {
                // If neighbor is visited and not the cell we just came from, it's a cycle
                if (visited[nr][nc]) {
                    if (nr != pr || nc != pc) {
                        return true;
                    }
                } else {
                    // Recursive DFS call
                    if (dfs(grid, visited, nr, nc, r, c, target)) {
                        return true;
                    }
                }
            }
        }
        return false;
    }
};
