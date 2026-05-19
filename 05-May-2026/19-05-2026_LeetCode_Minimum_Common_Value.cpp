// 19-05-2026_GFG_Minimum_Multiplications_to_reach_End.cpp

/*
Date: 19-05-2026
Problem Name: Minimum Multiplications to reach End
Platform: GeeksforGeeks
Difficulty: Medium
Tags: BFS, Graph, Shortest Path, Modulo Arithmetic

Problem Summary:
Given a start node, an end node, and an array of multipliers. In one step, 
you can multiply the current node value by any element from the array and 
take the result modulo 1000. Find the minimum steps to reach the end node 
from the start node. If unreachable, return -1.

Methods to Solve:
1. Breadth-First Search (BFS) - Optimal Approach

For Method 1 (BFS):
- Intuition: Since each operation (multiplication) represents an edge with 
  weight 1 in an unweighted graph where nodes are values 0-999, BFS is the 
  most efficient algorithm to find the shortest path.
- Approach: Use a queue to store {current_value, steps}. Keep a distance array 
  initialized to infinity to track visited states and minimum steps to reach 
  each value (0-999).
- Dry Run: start=3, arr=[2, 5], end=30
  - Queue: {(3, 0)}, Dist[3] = 0
  - Pop (3, 0): Next: (3*2)%1000=6, (3*5)%1000=15. Queue: {(6, 1), (15, 1)}
  - Pop (6, 1): Next: (6*2)%1000=12, (6*5)%1000=30. Found 30! Return steps+1 = 2.
- Time Complexity: O(1000 * N), where N is size of arr.
- Space Complexity: O(1000) for the distance array.
- Why better: BFS guarantees the shortest path in an unweighted graph.
- When to use: When finding the shortest path in a graph with uniform edge weights.

Comparison Table:
Method | TC | SC | Best Use Case
BFS    | O(1000*N) | O(1000) | Shortest path in unweighted graphs

Final Recommended Solution: BFS
*/

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Solution {
public:
    int minSteps(vector<int>& arr, int start, int end) {
        if (start == end) return 0;

        // Distance array to store min steps to reach each modulo value (0-999)
        vector<int> dist(1000, 1e9);
        queue<pair<int, int>> q;

        q.push({start, 0});
        dist[start] = 0;

        int mod = 1000;

        while (!q.empty()) {
            int current = q.front().first;
            int steps = q.front().second;
            q.pop();

            for (int multiplier : arr) {
                int next = (current * multiplier) % mod;

                if (steps + 1 < dist[next]) {
                    dist[next] = steps + 1;
                    if (next == end) return steps + 1;
                    q.push({next, steps + 1});
                }
            }
        }

        return -1;
    }
};

// Driver code to demonstrate functionality
int main() {
    Solution sol;
    vector<int> arr = {2, 5, 7};
    int start = 3, end = 30;
    
    int result = sol.minSteps(arr, start, end);
    cout << "Minimum steps: " << result << endl;
    
    return 0;
}
