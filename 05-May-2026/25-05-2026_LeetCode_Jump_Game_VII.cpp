// 25-05-2026_LeetCode_Jump_Game_VII.cpp

/*
Date: 25-05-2026
Problem Name: 1871. Jump Game VII
Platform: LeetCode
Difficulty: Medium
Tags: String, Dynamic Programming, Sliding Window, Prefix Sum, Breadth-First Search

Problem Summary:
Given a 0-indexed binary string `s` and two integers `minJump` and `maxJump`. Starting at index 0 (which is '0'), you can move from index `i` to index `j` if `i + minJump <= j <= min(i + maxJump, s.length - 1)` and `s[j] == '0'`. Return `true` if you can reach the last index, otherwise `false`.

Methods to Solve:
1. Breadth-First Search (BFS) with Range Optimization
2. Dynamic Programming (DP) with Sliding Window (Optimal)

-------------------------------------------------------------------------------
Method 1: Breadth-First Search (BFS) with Range Optimization
-------------------------------------------------------------------------------
- Intuition:
  We can think of the string as a graph where an edge exists from `i` to `j` if the jump conditions are met. A standard BFS can find if the target is reachable. However, to avoid a Time Limit Exceeded (TLE) error, we cannot process overlapping ranges multiple times.
  
- Approach:
  Use a queue to store reachable indices. Maintain a `farthest` variable to track the maximum index we have processed so far. When at index `curr`, the next possible jumps are between `curr + minJump` and `curr + maxJump`. To avoid redundant checks, we start searching from `max(curr + minJump, farthest + 1)`.

- Dry Run:
  s = "011010", minJump = 2, maxJump = 3
  Queue: [0], farthest: 0
  Pop 0: Jump range [2, 3]. s[2]='1', s[3]='0'. Push 3. farthest = 3.
  Queue: [3]
  Pop 3: Jump range [5, 5] (since 3+2=5, 3+3=6 but bounded by n-1). s[5]='0'. Reachable! Return true.

- Time Complexity: O(N)
  Each index is pushed into the queue at most once, and the `farthest` pointer ensures we only evaluate each index at most once in the loop.
  
- Space Complexity: O(N)
  In the worst-case scenario, the queue can store up to N elements.

- Why better than Brute Force:
  A naive BFS/DFS would revisit intervals, leading to an O(N^2) time complexity. The `farthest` pointer optimizes this to linear time.

- When to use:
  When you need an intuitive traversal method and want to return early the moment the last index is encountered.

-------------------------------------------------------------------------------
Method 2: Dynamic Programming with Sliding Window (Optimal)
-------------------------------------------------------------------------------
- Intuition:
  An index `i` is reachable if `s[i] == '0'` AND there is at least one reachable index `j` in the valid window `[i - maxJump, i - minJump]`. We can maintain a count of reachable indices in this sliding window.
  
- Approach:
  Use a boolean array `dp` where `dp[i]` is `true` if index `i` is reachable.
  Maintain a variable `reachable_count` that tracks the number of `true` values in the window `[i - maxJump, i - minJump]`. 
  As `i` increases:
  1. Add `dp[i - minJump]` to `reachable_count` (as it enters the window).
  2. Subtract `dp[i - maxJump - 1]` from `reachable_count` (as it exits the window).
  If `s[i] == '0'` and `reachable_count > 0`, set `dp[i] = true`.

- Dry Run:
  s = "011010", minJump = 2, maxJump = 3
  dp = [T, F, F, F, F, F], reachable_count = 0
  i=1: window [-2, -1] -> count=0 -> dp[1]=F
  i=2: window [-1, 0] -> add dp[0] -> count=1 -> s[2]='1' -> dp[2]=F
  i=3: window [0, 1] -> add dp[1] -> count=1 -> s[3]='0' -> dp[3]=T
  i=4: window [1, 2] -> add dp[2], remove dp[0] -> count=0 -> dp[4]=F
  i=5: window [2, 3] -> add dp[3], remove dp[1] -> count=1 -> s[5]='0' -> dp[5]=T
  Return dp[5] (True)

- Time Complexity: O(N)
  We iterate through the string of length N exactly once.
  
- Space Complexity: O(N)
  The `dp` array requires linear space.
  
- Why better than previous method:
  It operates with a smaller constant factor and is slightly more elegant to write. No queue overhead.

- When to use:
  Highly recommended for competitive programming and interviews when dealing with contiguous jump/reachability constraints.

-------------------------------------------------------------------------------
Comparison Table:
Method | TC   | SC   | Best Use Case
-------------------------------------------------------------------------------
BFS    | O(N) | O(N) | Best if an early exit is highly probable.
DP     | O(N) | O(N) | Cleanest implementation, strictly bounded O(N) time.

Final Recommended Solution: Method 2 (DP with Sliding Window)
*/

#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>

using namespace std;

class Solution {
public:
    // Method 2: Dynamic Programming with Sliding Window (Optimal Recommended Solution)
    bool canReach(string s, int minJump, int maxJump) {
        int n = s.length();
        
        // If the last character is '1', it can never be reached
        if (s[n - 1] != '0') {
            return false;
        }

        vector<bool> dp(n, false);
        dp[0] = true;
        int reachable_count = 0;

        for (int i = 1; i < n; ++i) {
            // Include the index that just entered the valid jump window
            if (i >= minJump && dp[i - minJump]) {
                reachable_count++;
            }
            // Remove the index that just exited the valid jump window
            if (i > maxJump && dp[i - maxJump - 1]) {
                reachable_count--;
            }

            // If the current spot is '0' and we have a valid launch pad in the window
            if (s[i] == '0' && reachable_count > 0) {
                dp[i] = true;
            }
        }

        return dp[n - 1];
    }

    // Method 1: Breadth-First Search (BFS) with Range Optimization (Alternative)
    bool canReachBFS(string s, int minJump, int maxJump) {
        int n = s.length();
        if (s[n - 1] != '0') {
            return false;
        }

        queue<int> q;
        q.push(0);
        
        // Track the farthest index checked to avoid duplicate processing
        int farthest = 0; 

        while (!q.empty()) {
            int curr = q.front();
            q.pop();

            // Early exit if we reach the end
            if (curr == n - 1) {
                return true;
            }

            // Calculate the bounds for our next jumps
            int start = max(curr + minJump, farthest + 1);
            int end = min(curr + maxJump, n - 1);

            for (int i = start; i <= end; ++i) {
                if (s[i] == '0') {
                    if (i == n - 1) return true;
                    q.push(i);
                }
            }
            
            // Update farthest processed index
            farthest = max(farthest, end);
        }

        return false;
    }
};
