/*
    LeetCode 2515
    Shortest Distance to Target String in a Circular Array

    Approach:
    - Traverse all words
    - If words[i] == target:
        Compute clockwise / anticlockwise distance
        distance = min(abs(i - startIndex), n - abs(i - startIndex))
    - Return minimum distance found
    - If target not found, return -1

    Time Complexity: O(n)
    Space Complexity: O(1)
*/

class Solution {
public:
    int closetTarget(vector<string>& words, string target, int startIndex) {
        int n = words.size();
        int ans = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (words[i] == target) {
                int diff = abs(i - startIndex);
                ans = min(ans, min(diff, n - diff));
            }
        }

        return (ans == INT_MAX) ? -1 : ans;
    }
};
