// File Name: 28-05-2026_LeetCode_Longest_Common_Suffix_Queries.cpp

/*
Date: 28-05-2026
Problem Name: Longest Common Suffix Queries
Platform: LeetCode
Difficulty: Hard
Tags: Array, String, Trie

Problem Summary:
Given two string arrays, `wordsContainer` and `wordsQuery`, find the index of the string in 
`wordsContainer` that shares the longest common suffix with each query in `wordsQuery`. 
If there's a tie in suffix length, prefer the string with the smallest length. If still tied, 
prefer the string that appears earlier in `wordsContainer` (smaller index).

Methods to Solve:
1. Brute Force
2. Optimal Approach (Trie with Reversed Strings)

--------------------------------------------------------------------------------------------------

Method 1: Brute Force (Will TLE)
- Intuition: For each query, compare its suffix with every word in the container. Keep track 
  of the maximum suffix match, updating the best index based on the problem's tie-breaking rules.
- Approach: Use nested loops. Outer loop for queries, inner loop for container words. Compare 
  characters from the back.
- Dry Run: Query="cd", Container=["abcd", "xbcd"]. Match "cd" with "abcd" -> suffix len 2. Match 
  "cd" with "xbcd" -> suffix len 2. Tie! Lengths are both 4. Tie! "abcd" is earlier (idx 0), so ans=0.
- Time Complexity: O(Q * N * min(L_q, L_c)), where Q is query count, N is container count, and L is word length.
- Space Complexity: O(1) auxiliary space.
- Why better than previous method: N/A (Baseline).
- When to use: When input sizes are very small (N, Q <= 100).

--------------------------------------------------------------------------------------------------

Method 2: Optimal Approach (Trie)
- Intuition: Since we are matching suffixes, reversing the strings transforms the problem into finding 
  the Longest Common Prefix (LCP). A Trie is the optimal data structure for prefix matching.
- Approach: 
  1. Build a Trie where each node stores a `best_idx`.
  2. Initialize nodes with `-1` so they only record strings that actually traverse them.
  3. Insert all reversed words from `wordsContainer`. For every node visited, check if the current 
     string's index is "better" (shorter length, or same length but smaller index).
  4. For each query, reverse it and traverse down the Trie. The `best_idx` at the deepest reachable 
     node is the correct answer.
- Dry Run: 
  wordsContainer = ["abcdefgh","poiuygh","ghghgh"], wordsQuery = ["acbfgh"]
  Reversed container: "hgfedcba" (idx 0, len 8), "hgyuiop" (idx 1, len 7), "hghghg" (idx 2, len 6)
  Insert "hgfedcba": Root(best=0) -> 'h'(best=0) -> 'g'(best=0) -> 'f'(best=0) ... 
  Insert "hgyuiop": Root(best=1) -> 'h'(best=1) -> 'g'(best=1) -> 'y'(best=1) ...
  Insert "hghghg": Root(best=2) -> 'h'(best=2) -> 'g'(best=2) -> 'h'(best=2) ...
  (Notice 'f' branch retains best_idx=0 because only word 0 passed through it).
  Query reversed: "hgfbca"
  Traverse: Root -> 'h' -> 'g' -> 'f'. Next char 'b' not found. Stop at 'f'. 
  Node 'f' best_idx = 0. Answer = 0.
- Time Complexity: O(SUM(L_c) + SUM(L_q)), where SUM(L) is the total number of characters in all strings.
- Space Complexity: O(SUM(L_c) * 26) for the Trie nodes.
- Why better than previous method: Eliminates redundant suffix checking and precalculates optimal answers.
- When to use: When total string lengths sum up to 10^5 or larger.

--------------------------------------------------------------------------------------------------

Comparison Table:
Method       | TC                       | SC                  | Best Use Case
--------------------------------------------------------------------------------------------------
Brute Force  | O(Q * N * min(L))        | O(1)                | Small arrays / Interviews for baseline
Trie         | O(SUM(L_c) + SUM(L_q))   | O(SUM(L_c) * 26)    | Optimal solution / Production / CP

Final Recommended Solution: Optimal Approach (Trie)
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Fast I/O for Competitive Programming
static const int _ = []() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    return 0;
}();

// ---------------- LeetCode Required Class Block ---------------- 
class Solution {
    // Array-based Trie to avoid pointer overhead and memory leaks (faster for CP)
    struct TrieNode {
        int children[26];
        int best_idx;
        
        TrieNode() {
            fill(begin(children), end(children), -1);
            best_idx = -1; // Initialize to -1 to avoid polluting nodes with unrelated defaults
        }
    };

    vector<TrieNode> trie;
    
    // Helper to determine if a new index is "better" than the current best
    bool isBetter(int new_idx, int old_idx, const vector<string>& words) {
        if (old_idx == -1) return true;
        
        int len_new = words[new_idx].length();
        int len_old = words[old_idx].length();
        
        if (len_new < len_old) return true;
        if (len_new == len_old && new_idx < old_idx) return true;
        
        return false;
    }

public:
    vector<int> stringIndices(vector<string>& wordsContainer, vector<string>& wordsQuery) {
        // Initialize Root
        trie.emplace_back(); 
        
        // Step 1: Insert reversed words into the Trie
        for (int i = 0; i < wordsContainer.size(); ++i) {
            int curr = 0; // Start at root
            const string& word = wordsContainer[i];
            
            // Update root for the empty suffix case
            if (isBetter(i, trie[curr].best_idx, wordsContainer)) {
                trie[curr].best_idx = i;
            }
            
            // Traverse from end of the string to front (Reversed)
            for (int j = word.length() - 1; j >= 0; --j) {
                int char_idx = word[j] - 'a';
                
                if (trie[curr].children[char_idx] == -1) {
                    trie[curr].children[char_idx] = trie.size();
                    trie.emplace_back(); // init new node with -1
                }
                
                curr = trie[curr].children[char_idx];
                
                // Update best_idx for the current prefix node
                if (isBetter(i, trie[curr].best_idx, wordsContainer)) {
                    trie[curr].best_idx = i;
                }
            }
        }
        
        // Step 2: Answer queries
        vector<int> ans;
        ans.reserve(wordsQuery.size());
        
        for (const string& query : wordsQuery) {
            int curr = 0; // Start at root
            
            for (int j = query.length() - 1; j >= 0; --j) {
                int char_idx = query[j] - 'a';
                if (trie[curr].children[char_idx] == -1) {
                    break; // No more matching suffix
                }
                curr = trie[curr].children[char_idx];
            }
            
            ans.push_back(trie[curr].best_idx);
        }
        
        return ans;
    }
};
// ---------------------------------------------------------------- 

// Standalone Driver Code for Local Execution
int main() {
    Solution sol;
    
    // Test Case 1
    vector<string> wordsContainer1 = {"abcd", "bcd", "xbcd"};
    vector<string> wordsQuery1 = {"cd", "bcd", "xyz"};
    vector<int> result1 = sol.stringIndices(wordsContainer1, wordsQuery1);
    
    cout << "Test Case 1 Output: [";
    for (int i = 0; i < result1.size(); ++i) {
        cout << result1[i] << (i == result1.size() - 1 ? "" : ", ");
    }
    cout << "]\n"; // Expected: [1, 1, 1]
    
    // Test Case 2 (Failing Case Addressed)
    vector<string> wordsContainer2 = {"abcdefgh", "poiuygh", "ghghgh"};
    vector<string> wordsQuery2 = {"gh", "acbfgh", "acbfegh"};
    vector<int> result2 = sol.stringIndices(wordsContainer2, wordsQuery2);
    
    cout << "Test Case 2 Output: [";
    for (int i = 0; i < result2.size(); ++i) {
        cout << result2[i] << (i == result2.size() - 1 ? "" : ", ");
    }
    cout << "]\n"; // Expected: [2, 0, 2]

    return 0;
}
