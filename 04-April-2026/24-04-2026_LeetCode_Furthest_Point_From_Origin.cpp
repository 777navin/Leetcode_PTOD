/*
File Name: 24-04-2026_LeetCode_Furthest_Point_From_Origin.cpp

Date: 24-04-2026
Problem Name: Furthest Point From Origin
Platform: LeetCode
Difficulty: Easy
Tags: String, Greedy, Simulation, Math

Problem Summary:
You are given a string moves consisting of:
'L' = move left by 1
'R' = move right by 1
'_' = unknown move (can be either L or R)

Return the maximum possible distance from origin after performing all moves.

------------------------------------------------------------

Methods to Solve:

1. Brute Force
- Try every possibility for '_'
- Total combinations = 2^(count of '_')
- Very expensive

2. Better Approach
- Count net fixed movement
- Use all unknown moves in direction increasing distance

3. Optimal Approach (Recommended)
- Let:
    left = count('L')
    right = count('R')
    blank = count('_')

- Current displacement:
    abs(left - right)

- Every '_' can increase distance by 1 optimally.

Final Answer:
    abs(left - right) + blank

------------------------------------------------------------

Dry Run:

moves = "L_RL__"

L = 2
R = 1
_ = 3

Base distance = abs(2 - 1) = 1

Use all '_' in same helpful direction:
1 + 3 = 4

Answer = 4

------------------------------------------------------------

Complexities:

Optimal:
Time  : O(n)
Space : O(1)

------------------------------------------------------------

Comparison Table:

Method          TC        SC      Best Use
Brute Force     O(2^k)    O(k)    Very small inputs
Optimal         O(n)      O(1)    Best for all cases

------------------------------------------------------------

Final Recommended Solution:
Use counting + math formula.
*/

class Solution {
public:
    int furthestDistanceFromOrigin(string moves) {
        int left = 0, right = 0, blank = 0;

        for (char ch : moves) {
            if (ch == 'L') left++;
            else if (ch == 'R') right++;
            else blank++;
        }

        return abs(left - right) + blank;
    }
};
