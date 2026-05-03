/*
Date: 03-05-2026
Problem Name: Rotate String
Platform: LeetCode
Difficulty: Easy
Tags: String, String Matching

Problem Summary:
Given two strings s and goal, return true if and only if s can become goal after some number of shifts on s.
A shift on s consists of moving the leftmost character of s to the rightmost position.

Example:
Input: s = "abcde", goal = "cdeab"
Output: true

Constraints:
1 <= s.length, goal.length <= 100
s and goal consist of lowercase English letters.

------------------------------------------------------------
Methods to Solve:

1. Brute Force
   - Intuition: Try all possible rotations of s and check if any equals goal.
   - Approach: For each rotation, simulate shifting and compare.
   - Dry Run: s="abcde", goal="cdeab"
       Rotate 1 → "bcdea"
       Rotate 2 → "cdeab" → match found.
   - Time Complexity: O(n^2)
   - Space Complexity: O(n)
   - Why better: Simple but inefficient.
   - When to use: Small constraints.

2. Concatenation Trick (Optimal)
   - Intuition: If goal is a rotation of s, then goal must be a substring of s+s.
   - Approach: Check if s and goal have same length, then verify if goal is in s+s.
   - Dry Run: s="abcde", goal="cdeab"
       s+s = "abcdeabcde"
       "cdeab" is substring → true.
   - Time Complexity: O(n)
   - Space Complexity: O(n)
   - Why better: Efficient and elegant.
   - When to use: Always, given constraints.

------------------------------------------------------------
Comparison Table:
Method              | TC     | SC     | Best Use Case
------------------------------------------------------------
Brute Force         | O(n^2) | O(n)   | Small inputs, clarity
Concatenation Trick | O(n)   | O(n)   | Optimal, recommended

------------------------------------------------------------
Final Recommended Solution:
Use the concatenation trick for efficiency and simplicity.
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // Optimal approach using concatenation
    bool rotateString(string s, string goal) {
        if(s.size() != goal.size()) return false;
        string doubled = s + s;
        return doubled.find(goal) != string::npos;
    }

    // Brute force approach for completeness
    bool rotateStringBrute(string s, string goal) {
        if(s.size() != goal.size()) return false;
        int n = s.size();
        for(int i = 0; i < n; i++) {
            rotate(s.begin(), s.begin() + 1, s.end()); // shift leftmost to rightmost
            if(s == goal) return true;
        }
        return false;
    }
};
