/*
Date: 17-05-2026
Problem Name: Jump Game III
Platform: LeetCode
Difficulty: Medium
Tags: Array, Depth-First Search, Breadth-First Search

Problem Summary
Given an array of non-negative integers 'arr' and an initial position 'start', 
you can jump to index i + arr[i] or i - arr[i] from your current index i. 
Determine if you can reach any index with a value of 0. You are strictly 
prohibited from jumping outside the boundaries of the array at any point.

Methods to Solve:
1. Depth-First Search (DFS) - Recursive
2. Breadth-First Search (BFS) - Iterative

For EACH method include:

Method 1: Depth-First Search (DFS) - Recursive
- Intuition: 
  Treat the array indices as nodes in a graph where directed edges point to 
  (i + arr[i]) and (i - arr[i]). DFS naturally explores each viable branch 
  to its absolute depth until it either hits a 0, an out-of-bounds index, 
  or a loop cycle.
- Approach: 
  Utilize a recursive helper function along with a visited tracker array. 
  For the current index, validate boundaries and check if it has already been 
  evaluated. If the value at the index is 0, return true. Otherwise, mark it 
  as visited and return the logical OR of both potential directional jumps.
- Dry Run (small example): 
  arr = [1, 0], start = 0
  DFS(0) -> Valid, not visited. arr[0] != 0. Mark visited[0] = true.
    Jump Right: 0 + arr[0] = 1 -> DFS(1)
    DFS(1) -> Valid, not visited. arr[1] == 0 -> returns true.
  Logical OR resolves to true.
- Time Complexity: O(N) since each array index is visited at most once.
- Space Complexity: O(N) due to the recursive call stack and visited tracker overhead.
- Why better than previous method: Baseline traversal approach; structurally clean.
- When to use: When deep exploration paths are expected and system stack limits permit.

Method 2: Breadth-First Search (BFS) - Iterative
- Intuition: 
  Explore all reachable positions layer-by-layer. This prevents deep recursion overhead 
  and evaluates nodes in increasing order of jump distance.
- Approach: 
  Initialize a queue and push the starting index while marking it as visited. 
  While the queue is populated, pop the front element, verify if its value equals 0, 
  and compute forward (curr + arr[curr]) and backward (curr - arr[curr]) bounds. 
  Push unvisited, valid paths into the queue.
- Dry Run (small example): 
  arr = [1, 0], start = 0
  Queue = [0], Visited = {0}
  Pop 0: arr[0] = 1. Forward = 1 (Valid), Backward = -1 (Invalid).
  Queue = [1], Visited = {0, 1}
  Pop 1: arr[1] = 0 -> returns true.
- Time Complexity: O(N) as each node is enqueued and dequeued at most once.
- Space Complexity: O(N) for maintaining the state tracking queue and visited buffer.
- Why better than previous method: Eliminates the threat of stack overflow issues in deep call hierarchies.
- When to use: Preferred for explicit, safe state-space expansion or when finding short step variations.

Comparison Table:
Method | TC | SC | Best Use Case
1. Recursive DFS | O(N) | O(N) | Fast to implement, clean code layout.
2. Iterative BFS | O(N) | O(N) | Avoids system stack limits; highly robust.

Final Recommended Solution
Both graph exploration methods execute optimally within linear boundaries. However, 
the Iterative BFS approach is selected as the production baseline because it explicitly 
manages its memory layout on the heap via std::queue, avoiding stack overflow concerns.
*/

#include <vector>
#include <queue>

using namespace std;

class Solution {
private:
    /**
     * @brief Recursive helper method to perform Depth-First Search.
     */
    bool solveDFS(const vector<int>& arr, int curr, vector<bool>& visited) {
        // Base Case: Out of bounds or already evaluated index
        if (curr < 0 || curr >= arr.size() || visited[curr]) {
            return false;
        }
        
        // Target Condition Found
        if (arr[curr] == 0) {
            return true;
        }
        
        // Tracking visited positions to avoid cycles
        visited[curr] = true;
        
        // Branch into both paths (Forward and Backward jumps)
        return solveDFS(arr, curr + arr[curr], visited) || 
               solveDFS(arr, curr - arr[curr], visited);
    }

public:
    /**
     * @brief Primary entry point for LeetCode evaluation.
     * Uses the recommended Iterative BFS approach under the hood.
     */
    bool canReach(vector<int>& arr, int start) {
        return canReachBFS(arr, start);
    }

    /**
     * @brief Approach 1: Depth-First Search Solution Format
     */
    bool canReachDFS(vector<int>& arr, int start) {
        vector<bool> visited(arr.size(), false);
        return solveDFS(arr, start, visited);
    }

    /**
     * @brief Approach 2: Breadth-First Search Solution Format
     */
    bool canReachBFS(const vector<int>& arr, int start) {
        int n = arr.size();
        vector<bool> visited(n, false);
        queue<int> stateQueue;
        
        // Initialize the tracking state
        stateQueue.push(start);
        visited[start] = true;
        
        while (!stateQueue.empty()) {
            int curr = stateQueue.front();
            stateQueue.pop();
            
            // Check if objective is reached
            if (arr[curr] == 0) {
                return true;
            }
            
            // Calculate potential branching indexes
            int forwardJump = curr + arr[curr];
            int backwardJump = curr - arr[curr];
            
            // Evaluate Forward Index
            if (forwardJump < n && !visited[forwardJump]) {
                visited[forwardJump] = true;
                stateQueue.push(forwardJump);
            }
            
            // Evaluate Backward Index
            if (backwardJump >= 0 && !visited[backwardJump]) {
                visited[backwardJump] = true;
                stateQueue.push(backwardJump);
            }
        }
        
        return false;
    }
};
