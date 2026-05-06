#include <iostream>
#include <cmath>

using namespace std;

class Solution {
public:
    /**
     * Calculates the absolute difference between n and its reverse.
     * Time Complexity: O(log10 n)
     * Space Complexity: O(1)
     */
    int mirrorDistance(int n) {
        int original = n; 
        long long value = 0; // Prevents overflow during reversal
        
        while(n != 0) {
            int digit = n % 10;
            value = value * 10 + digit;
            n /= 10;
        }
        
        return abs(original - (int)value);
    }
};

int main() {
    Solution sol;
    
    // Test Case 1
    int n1 = 123;
    cout << "Original: " << n1 << ", Mirror Distance: " << sol.mirrorDistance(n1) << endl; 
    // (123 - 321) = 198

    // Test Case 2
    int n2 = 100;
    cout << "Original: " << n2 << ", Mirror Distance: " << sol.mirrorDistance(n2) << endl; 
    // (100 - 001) = 99

    return 0;
}
