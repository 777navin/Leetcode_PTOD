// Date: 20-04-2026
// LeetCode 2078 - Two Furthest Houses With Different Colors
// Language: C++

#include <bits/stdc++.h>
using namespace std;

/*
==================================================
Approach 1: Brute Force
Intuition:
Check every pair of houses. If colors are different,
update maximum distance.

Time Complexity: O(n^2)
Space Complexity: O(1)
==================================================
*/
class SolutionBruteForce {
public:
    int maxDistance(vector<int>& colors) {
        int n = colors.size();
        int ans = 0;

        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (colors[i] != colors[j]) {
                    ans = max(ans, j - i);
                }
            }
        }
        return ans;
    }
};

/*
==================================================
Approach 2: Optimal Greedy / Edge Check
Intuition:
Maximum distance will always involve:
1. First house with farthest different house, or
2. Last house with farthest different house.

Time Complexity: O(n)
Space Complexity: O(1)
==================================================
*/
class Solution {
public:
    int maxDistance(vector<int>& colors) {
        int n = colors.size();
        int ans = 0;

        for (int i = n - 1; i >= 0; i--) {
            if (colors[i] != colors[0]) {
                ans = max(ans, i);
                break;
            }
        }

        for (int i = 0; i < n; i++) {
            if (colors[i] != colors[n - 1]) {
                ans = max(ans, n - 1 - i);
                break;
            }
        }

        return ans;
    }
};
