/*
Date: 30-05-2026
Problem Name: Replace with XOR of Adjacent
Platform: GeeksforGeeks
Difficulty: Easy
Tags: Array, Bit Magic, In-place

Problem Summary:
Given an array of `n` integers, modify it in-place such that every element is replaced 
by the XOR of its adjacent elements. The first element is XORed with the second, the 
last element with the second last, and the middle elements with their left and right neighbors.
Important: The calculations must use the *original* values of the adjacent elements, 
not the updated ones.

Methods to Solve:
1. Brute Force (Using Extra Space)
2. Optimal Approach (Space Optimized)

-------------------------------------------------------------------
Method 1: Brute Force (Using Extra Space)
-------------------------------------------------------------------
- Intuition: Since updating the array in-place changes values needed for subsequent 
  calculations, the simplest way to preserve the original values is to make a copy 
  of the array.
- Approach: Create a temporary array `temp` of the same size. Iterate through the 
  original array, compute the XOR logic using `temp`, and overwrite the original `arr`.
- Time Complexity: O(N) where N is the size of the array.
- Space Complexity: O(N) to store the copy of the array.
- Why better than previous method: N/A (Baseline).
- When to use: When array size is small and memory is not a constraint.

-------------------------------------------------------------------
Method 2: Optimal Approach (Space Optimized)
-------------------------------------------------------------------
- Intuition: We don't need the entire original array at any given step. When calculating 
  the value for index `i`, we only need the original value of `arr[i-1]` and `arr[i+1]`. 
  `arr[i+1]` is already untouched, so we only need to keep track of the original `arr[i-1]`.
- Approach: 
  1. Handle edge cases (e.g., array size <= 1).
  2. Store the original `arr[0]` in a variable `prev`.
  3. Update `arr[0] = arr[0] ^ arr[1]`.
  4. Iterate from `i = 1` to `n-2`:
     a. Temporarily store the original `arr[i]` in `curr`.
     b. Update `arr[i] = prev ^ arr[i+1]`.
     c. Update `prev = curr` for the next iteration.
  5. Finally, update the last element `arr[n-1] = prev ^ arr[n-1]`.
- Dry Run: arr = [2, 1, 4, 7]
  - prev = 2
  - arr[0] = 2 ^ 1 = 3.  Array becomes [3, 1, 4, 7]
  - i=1: curr = 1, arr[1] = prev(2) ^ arr[2](4) = 6. prev = 1. Array: [3, 6, 4, 7]
  - i=2: curr = 4, arr[2] = prev(1) ^ arr[3](7) = 6. prev = 4. Array: [3, 6, 6, 7]
  - End loop.
  - arr[3] = prev(4) ^ arr[3](7) = 3. Array: [3, 6, 6, 3].
- Time Complexity: O(N) as we traverse the array exactly once.
- Space Complexity: O(1) as we only use a couple of variables (`prev`, `curr`).
- Why better than previous method: Eliminates the O(N) auxiliary space overhead.
- When to use: Recommended for all cases, especially for large arrays due to O(1) space.

Comparison Table:
Method         | TC   | SC   | Best Use Case
---------------------------------------------------------
Brute Force    | O(N) | O(N) | When immutability of the source is preferred.
Optimal        | O(N) | O(1) | General use, large inputs, strictly in-place.

Final Recommended Solution: Optimal Approach
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    void replaceElements(vector<int>& arr) {
        int n = arr.size();
        
        // Edge case: if array has 1 or fewer elements, no adjacent elements exist to XOR.
        if (n <= 1) return;

        // Store the original value of the previous element
        int prev = arr[0];
        
        // Update the first element
        arr[0] = arr[0] ^ arr[1];

        // Update middle elements
        for (int i = 1; i < n - 1; ++i) {
            int curr = arr[i];          // Store current original value
            arr[i] = prev ^ arr[i + 1]; // XOR previous original with next original
            prev = curr;                // Move prev forward
        }

        // Update the last element
        arr[n - 1] = prev ^ arr[n - 1];
    }
};

// Driver code for standalone local execution
int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    // Simple custom driver to test via console or fall back to default tests
    if (cin >> t) {
        while (t--) {
            int n;
            cin >> n;
            vector<int> arr(n);
            for (int i = 0; i < n; ++i) {
                cin >> arr[i];
            }

            Solution obj;
            obj.replaceElements(arr);

            for (int i = 0; i < n; ++i) {
                cout << arr[i] << " ";
            }
            cout << "\n";
        }
    } else {
        // Fallback test cases if no stdin is provided
        Solution obj;
        
        vector<int> test1 = {2, 1, 4, 7};
        obj.replaceElements(test1);
        cout << "Test 1 Output: ";
        for(int val : test1) cout << val << " ";
        cout << "\n"; // Expected: 3 6 6 3

        vector<int> test2 = {5, 9, 2, 6, 7};
        obj.replaceElements(test2);
        cout << "Test 2 Output: ";
        for(int val : test2) cout << val << " ";
        cout << "\n"; // Expected: 12 7 15 5 1
    }

    return 0;
}
