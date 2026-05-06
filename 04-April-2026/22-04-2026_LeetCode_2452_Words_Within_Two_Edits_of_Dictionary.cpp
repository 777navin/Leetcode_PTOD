/*


Date: 22-04-2026
Problem Name: Words Within Two Edits of Dictionary
Platform: LeetCode
Problem ID: 2452
Difficulty: Medium
Tags:
String, Array, Simulation, Hashing

=========================================================
Problem Summary:
You are given two string arrays:
- queries
- dictionary

All strings have same length.

In one edit, you can change one character to any other character.

Return all words from queries such that they can become
equal to any word in dictionary using at most 2 edits.

Return answers in same order as queries.

=========================================================
Methods to Solve:

1. Brute Force
---------------------------------------------------------
Intuition:
Compare every query with every dictionary word.
Count differing characters.

Approach:
- For each query:
    - For each dictionary word:
        - Count mismatches
        - If mismatches <= 2, include query

Dry Run:
query = "word"
dict = "wood"

w == w
o == o
r != o (1 mismatch)
d == d

Total = 1 <= 2 => valid

Time Complexity:
O(Q * D * L)

Space Complexity:
O(1) extra

Why Good:
Simple and accepted under constraints.

When to Use:
Best for given LeetCode constraints.

---------------------------------------------------------

2. Optimized Early Break
---------------------------------------------------------
Same as brute force but stop checking current pair once
mismatches exceed 2.

This saves time practically.

=========================================================
Comparison Table:

Method              TC              SC      Best Use
---------------------------------------------------------
Brute Force         O(Q*D*L)        O(1)    Small/medium constraints
Early Break         O(Q*D*L)        O(1)    Best practical solution

=========================================================
Final Recommended Solution:
Use mismatch counting with early break.

=========================================================
*/

class Solution {
public:
    
    // Check if two words differ in at most 2 positions
    bool withinTwoEdits(const string& a, const string& b) {
        int mismatches = 0;

        for (int i = 0; i < a.size(); i++) {
            if (a[i] != b[i]) {
                mismatches++;
                if (mismatches > 2)
                    return false;
            }
        }

        return true;
    }

    vector<string> twoEditWords(vector<string>& queries, vector<string>& dictionary) {
        vector<string> answer;

        for (const string& query : queries) {
            for (const string& word : dictionary) {
                if (withinTwoEdits(query, word)) {
                    answer.push_back(query);
                    break;
                }
            }
        }

        return answer;
    }
};
