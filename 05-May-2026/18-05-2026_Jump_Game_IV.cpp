/*
Date: 18-05-2026
Problem Name: Jump Game IV
Platform: LeetCode
Difficulty: Hard
Tags: Array, Hash Table, Breadth-First Search (BFS)

Problem Summary:
Given an array of integers 'arr', you start at the first index (0). In one step, you can 
jump from the current index i to:
1. i + 1 (where i + 1 < arr.length)
2. i - 1 (where i - 1 >= 0)
3. j (where arr[i] == arr[j] and i != j)

Return the minimum number of steps required to reach the last index of the array.

Methods to Solve:
1. Naive Breadth-First Search (BFS)
2. Optimized BFS with Graph Pruning (Optimal)

--------------------------------------------------------------------------------

1. Naive Breadth-First Search (BFS)
- Intuition: 
  The problem asks for the minimum steps to transition from a start state to a goal state 
  in an unweighted graph representation, making Breadth-First Search (BFS) the most direct path strategy.
- Approach:
  - Build an adjacency mapping where each unique number maps to all indices containing that value.
  - Initialize a queue for standard BFS level-order traversal, starting from index 0.
  - Track visited states using a boolean array.
  - For each popped index, check all three transition types: i + 1, i - 1, and all indices j where arr[i] == arr[j].
  - This approach explores every potential path level-by-level, but it blindly checks all equal-value 
    indices repeatedly if multiple identical values exist along the path.
- Dry Run: 
  For arr = [7, 7, 7, 7], starting at index 0, neighbor checks will push indices 1, 2, 3. 
  When evaluating index 1 next, it will re-scan indices 0, 2, 3, causing massive redundant iterations.
- Time Complexity: O(N^2) in the worst-case scenario (e.g., when all elements in the array are identical).
- Space Complexity: O(N) to maintain the map and the BFS queue state.
- Why better than previous method: N/A (Baseline approach).
- When to use: Only effective when N is tiny or all elements are strictly unique.

2. Optimized BFS with Graph Pruning (Optimal)
- Intuition:
  The bottleneck in the naive approach is re-evaluating the list of identical values. Once we have 
  expanded all nodes sharing the value arr[i], we have effectively processed all shortcuts provided 
  by that value group. We can safely erase or clear that value entry from our map to avoid redundant scans.
- Approach:
  - Group identical element indices into an `unordered_map<int, vector<int>>`.
  - Initialize a BFS queue with index 0 and mark it as visited.
  - At each step, process nodes layer by layer to track step increments cleanly.
  - For the current index, evaluate `curr + 1` and `curr - 1`.
  - Extract the vector of identical value indices from the map, push unvisited matching indices to the queue, 
    and instantly remove/clear that key from the map.
  - Terminate and return the step count the exact moment index `n - 1` is encountered.
- Dry Run:
  arr = [100, -23, -23, 404, 100]
  - Map: {100: [0, 4], -23: [1, 2], 404: [3]}
  - Step 0: Q = [0], Visited = {0}
    - Pop 0. Neighbors: 0+1=1 (-23), indices from map for 100 -> [0, 4]. 4 is added. Map entry for 100 cleared.
    - Q becomes [1, 4].
  - Step 1: Q = [1, 4]
    - Pop 1. Neighbors: 1-1=0 (visited), 1+1=2 (-23), indices for -23 -> [1, 2]. 2 is added. Map entry for -23 cleared.
    - Pop 4. Target reached? Yes, 4 == n-1. 
  - Total Steps: 3 (Path: 0 -> 4).
- Time Complexity: O(N) because every node and edge (including equal value list iterations) is processed at most twice.
- Space Complexity: O(N) to store the mapping and tracking structures.
- Why better than previous method: Drastically reduces execution time from quadratic to linear, preventing TLE.
- When to use: Always preferred; required to pass strict performance boundaries.

Comparison Table:
Method        | TC     | SC     | Best Use Case
----------------------------------------------------------------------
Naive BFS     | O(N^2) | O(N)   | Small constraint limits
Optimized BFS | O(N)   | O(N)   | Standard production/Competitive programming

Final Recommended Solution: Optimized BFS with Graph Pruning (Method 2)
*/

#include <vector>
#include <unordered_map>
#include <queue>

using namespace std;

class Solution {
public:
    int minJumps(vector<int>& arr) {
        int n = arr.size();
        // Base Case: If the array contains 0 or 1 elements, no steps are required.
        if (n <= 1) {
            return 0;
        }

        // Map each unique value to all its occurring indices in the array
        unordered_map<int, vector<int>> valueToIndices;
        for (int i = 0; i < n; ++i) {
            valueToIndices[arr[i]].push_back(i);
        }

        // BFS setup structures
        queue<int> searchQueue;
        vector<bool> visited(n, false);

        // Enqueue the starting point
        searchQueue.push(0);
        visited[0] = true;
        int minSteps = 0;

        while (!searchQueue.empty()) {
            int currentLayerSize = searchQueue.size();

            // Process all nodes at the current depth layer
            for (int i = 0; i < currentLayerSize; ++i) {
                int currIdx = searchQueue.front();
                searchQueue.pop();

                // Goal check: If we have reached the last index, return the step tally
                if (currIdx == n - 1) {
                    return minSteps;
                }

                // Path Rule 1: Move forward to i + 1
                if (currIdx + 1 < n && !visited[currIdx + 1]) {
                    visited[currIdx + 1] = true;
                    searchQueue.push(currIdx + 1);
                }

                // Path Rule 2: Move backward to i - 1
                if (currIdx - 1 >= 0 && !visited[currIdx - 1]) {
                    visited[currIdx - 1] = true;
                    searchQueue.push(currIdx - 1);
                }

                // Path Rule 3: Jump to any index containing the identical element value
                if (valueToIndices.count(arr[currIdx])) {
                    for (int targetIdx : valueToIndices[arr[currIdx]]) {
                        if (!visited[targetIdx]) {
                            visited[targetIdx] = true;
                            searchQueue.push(targetIdx);
                        }
                    }
                    // Graph Pruning Optimization: Erase to ensure we never waste O(N) checking this bucket again
                    valueToIndices.erase(arr[currIdx]);
                }
            }
            // Transition to the next layer depth
            minSteps++;
        }

        return -1;
    }
};
