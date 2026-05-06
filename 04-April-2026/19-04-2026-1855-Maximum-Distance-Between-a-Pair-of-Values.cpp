#include <vector>
#include <algorithm>
using namespace std;

// Problem: 1855. Maximum Distance Between a Pair of Values
// Date: 19-04-2026
// Language: C++

/*
=========================================================
Approach 1: Brute Force
=========================================================
Intuition:
Check every valid pair (i, j) such that:
1. i <= j
2. nums1[i] <= nums2[j]

Update maximum distance = (j - i)

Time Complexity: O(n * m)
Space Complexity: O(1)

=========================================================
Approach 2: Optimal Two Pointers
=========================================================
Intuition:
Since both arrays are sorted in non-increasing order,
we use two pointers.

If nums1[i] <= nums2[j]:
    Valid pair, update answer.
    Move j forward to maximize distance.

Else:
    Move i forward to reduce nums1[i].

Maintain j >= i always.

Time Complexity: O(n + m)
Space Complexity: O(1)
=========================================================
*/

class Solution {
public:

    // Brute Force Approach
    int bruteForce(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size();
        int m = nums2.size();

        int ans = 0;

        for (int i = 0; i < n; i++) {
            for (int j = i; j < m; j++) {
                if (nums1[i] <= nums2[j]) {
                    ans = max(ans, j - i);
                }
            }
        }

        return ans;
    }

    // Optimal Approach (Used by LeetCode)
    int maxDistance(vector<int>& nums1, vector<int>& nums2) {
        int i = 0, j = 0;
        int ans = 0;

        while (i < nums1.size() && j < nums2.size()) {

            if (nums1[i] <= nums2[j]) {
                ans = max(ans, j - i);
                j++;
            } 
            else {
                i++;
                j = max(j, i);
            }
        }

        return ans;
    }
};
