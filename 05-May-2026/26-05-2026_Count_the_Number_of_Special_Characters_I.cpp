/*
Date: 26-05-2026
Problem Name: Count the Number of Special Characters I
Platform: LeetCode
Difficulty: Easy
Tags: Hash Table, String, Bit Manipulation

Problem Summary:
You are given a string `word`. A letter is considered "special" if it appears in both its lowercase and uppercase forms within the string. The task is to return the total count of such special letters.

Methods to Solve:
1. Brute Force (String Scanning)
2. Better Approach (Boolean Hash Arrays)
3. Optimal Approach (Bit Manipulation)

-------------------------------------------------------------------
Method 1: Brute Force (String Scanning)
-------------------------------------------------------------------
- Intuition: 
  Since there are only 26 letters in the English alphabet, we can simply iterate through all 26 letters. For each letter, we scan the entire string to see if both the lowercase and uppercase versions exist.
- Approach:
  1. Loop a character `c` from 'a' to 'z'.
  2. For each `c`, find if `c` and `toupper(c)` both exist in the string using string search methods.
  3. If both exist, increment the count.
- Dry Run: 
  `word` = "abBC"
  Check 'a': 'a' exists, 'A' missing. Count = 0.
  Check 'b': 'b' exists, 'B' exists. Count = 1.
  Check 'c': 'c' exists, 'C' missing. Count = 1.
- Time Complexity: $O(26 \times N)$ where $N$ is the length of the string.
- Space Complexity: $O(1)$
- Why better than previous method: N/A (Baseline)
- When to use: When string length is extremely small and built-in search functions are highly optimized.

-------------------------------------------------------------------
Method 2: Better Approach (Boolean Hash Arrays)
-------------------------------------------------------------------
- Intuition: 
  Instead of scanning the string multiple times, we can scan it exactly once. We can use two boolean arrays of size 26 to act as hash tables to record the presence of lowercase and uppercase letters.
- Approach:
  1. Initialize two boolean arrays `lower` and `upper` of size 26 with `false`.
  2. Iterate through each character in `word`.
  3. If it's lowercase, set `lower[char - 'a'] = true`.
  4. If it's uppercase, set `upper[char - 'A'] = true`.
  5. Iterate from 0 to 25. If both `lower[i]` and `upper[i]` are true, increment the count.
- Dry Run: 
  `word` = "aAb"
  'a' -> lower[0] = true
  'A' -> upper[0] = true
  'b' -> lower[1] = true
  Loop 0 to 25: Index 0 has both true. Count = 1.
- Time Complexity: $O(N)$ for a single pass through the string.
- Space Complexity: $O(1)$ since the array size is always strictly 26.
- Why better than previous method: Reduces the time complexity to a single pass $O(N)$ instead of $O(26 \times N)$.
- When to use: Best standard approach for clarity and performance in typical interview settings.

-------------------------------------------------------------------
Method 3: Optimal Approach (Bit Manipulation)
-------------------------------------------------------------------
- Intuition: 
  We only need to track 26 states. A 32-bit integer can easily hold 26 bits. We can use two integers as bitmasks: one for lowercase presence, one for uppercase.
- Approach:
  1. Initialize two integers `lowerMask = 0` and `upperMask = 0`.
  2. Iterate through the string. If lowercase, turn on the $i$-th bit of `lowerMask`. If uppercase, turn on the $i$-th bit of `upperMask`.
  3. The bitwise AND of `lowerMask` and `upperMask` will give a number where the $i$-th bit is 1 only if both cases were present.
  4. Count the set bits (using `__builtin_popcount`) of the resulting bitmask.
- Dry Run: 
  `word` = "aAb"
  'a' -> lowerMask |= (1 << 0)  => lowerMask = 001
  'A' -> upperMask |= (1 << 0)  => upperMask = 001
  'b' -> lowerMask |= (1 << 1)  => lowerMask = 011
  Both present: lowerMask & upperMask = 011 & 001 = 001.
  Set bits in 001 = 1.
- Time Complexity: $O(N)$
- Space Complexity: $O(1)$
- Why better than previous method: Reduces space overhead from boolean arrays to just two integers, resulting in minimal memory allocation and extremely fast bitwise operations.
- When to use: When seeking extreme optimization and minimal memory footprint.

-------------------------------------------------------------------
Comparison Table:
Method         | TC            | SC   | Best Use Case
-------------------------------------------------------------------
Brute Force    | $O(26 \times N)$ | $O(1)$ | Simple prototyping
Hash Arrays    | $O(N)$        | $O(1)$ | Standard interviews
Bitwise Mask   | $O(N)$        | $O(1)$ | Maximum efficiency/CP
-------------------------------------------------------------------

Final Recommended Solution: Method 3 (Bit Manipulation) for competitive programming, Method 2 for readability. Both are included below.
*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    // Method 3: Optimal Approach (Bit Manipulation)
    int numberOfSpecialChars(string word) {
        int lowerMask = 0;
        int upperMask = 0;
        
        for (char c : word) {
            if (c >= 'a' && c <= 'z') {
                lowerMask |= (1 << (c - 'a'));
            } else if (c >= 'A' && c <= 'Z') {
                upperMask |= (1 << (c - 'A'));
            }
        }
        
        // Bitwise AND gives bits that are set in BOTH masks
        int specialMask = lowerMask & upperMask;
        
        // __builtin_popcount counts the number of set bits (1s) in the integer
        return __builtin_popcount(specialMask);
    }

    // Method 2: Better Approach (Boolean Hash Arrays) - Alternative
    int numberOfSpecialChars_ArrayApproach(string word) {
        vector<bool> lower(26, false);
        vector<bool> upper(26, false);
        
        for(char c : word) {
            if (c >= 'a' && c <= 'z') {
                lower[c - 'a'] = true;
            } else if (c >= 'A' && c <= 'Z') {
                upper[c - 'A'] = true;
            }
        }
        
        int count = 0;
        for (int i = 0; i < 26; i++) {
            if (lower[i] && upper[i]) {
                count++;
            }
        }
        
        return count;
    }
};

// ---------------------------------------------------------
// Driver Code to make it a standalone, testable file
// ---------------------------------------------------------
int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    Solution sol;
    
    // Test Case 1
    string word1 = "aaAbcBC";
    cout << "Input: " << word1 << "\n";
    cout << "Output: " << sol.numberOfSpecialChars(word1) << " (Expected: 3)\n\n";
    
    // Test Case 2
    string word2 = "abc";
    cout << "Input: " << word2 << "\n";
    cout << "Output: " << sol.numberOfSpecialChars(word2) << " (Expected: 0)\n\n";
    
    // Test Case 3
    string word3 = "abBCab";
    cout << "Input: " << word3 << "\n";
    cout << "Output: " << sol.numberOfSpecialChars(word3) << " (Expected: 1)\n\n";

    return 0;
}
