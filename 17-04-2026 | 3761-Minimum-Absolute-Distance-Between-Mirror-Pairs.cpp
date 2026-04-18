/**
 * Date: 17-04-2026
 * Problem: 3761. Minimum Absolute Distance Between Mirror Pairs
 * Platform: LeetCode
 * Difficulty: Medium
 */

/*
    Intuition:
    The goal is to find the minimum |i - j| such that reverse(nums[i]) == nums[j].
    As we iterate through the array at index 'j', we need to look back and find 
    the most recent index 'i' where the value was equal to the target needed to 
    satisfy the condition. 
    
    Approach:
    1. We use a Hash Map (unordered_map) to store the result of reverse(nums[i]) 
       as the key and the index 'i' as the value.
    2. For every element nums[j]:
       - We check if nums[j] exists in our map. If it does, we found a pair.
       - We update our min_distance using (j - map[nums[j]]).
       - We then reverse the current nums[j] and store it in the map with 
         index 'j' so future elements can pair with it.
    3. We keep overwriting the index in the map for the same key to ensure we 
       always get the "minimum" distance (the closest previous index).

    Time Complexity (TC): O(N * D) 
    where N is the number of elements and D is the number of digits (max 10). 
    Effectively O(N).

    Space Complexity (SC): O(N) 
    to store the indices in the hash map.
*/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <climits>

using namespace std;

class Solution {
public:
    // Function to reverse the digits of a number
    long long getReverse(int n) {
        long long rev = 0;
        while (n > 0) {
            rev = rev * 10 + (n % 10);
            n /= 10;
        }
        return rev;
    }

    int minMirrorPairDistance(vector<int>& nums) {
        // map: {TargetValueNeeded -> LastSeenIndex}
        unordered_map<long long, int> lastSeenTarget;
        int min_dist = INT_MAX;
        bool found = false;

        for (int j = 0; j < nums.size(); ++j) {
            // Check if current number matches a previously stored reversed value
            if (lastSeenTarget.find(nums[j]) != lastSeenTarget.end()) {
                min_dist = min(min_dist, j - lastSeenTarget[nums[j]]);
                found = true;
            }

            // Store the reverse of current number as a target for future elements
            long long reversed_val = getReverse(nums[j]);
            lastSeenTarget[reversed_val] = j;
        }

        return found ? min_dist : -1;
    }
};

int main() {
    Solution sol;
    // Example 1
    vector<int> nums1 = {12, 21, 45, 33, 54};
    cout << "Example 1 Result: " << sol.minMirrorPairDistance(nums1) << endl; // Output: 1

    // Example 2
    vector<int> nums2 = {120, 21};
    cout << "Example 2 Result: " << sol.minMirrorPairDistance(nums2) << endl; // Output: 1

    return 0;
}
