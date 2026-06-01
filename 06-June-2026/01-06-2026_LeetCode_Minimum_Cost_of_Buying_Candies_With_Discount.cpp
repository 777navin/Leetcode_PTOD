/*
Date: 01-06-2026
Problem Name: Minimum Cost of Buying Candies With Discount
Platform: LeetCode
Difficulty: Easy
Tags: Array, Greedy, Sorting

Problem Summary:
A shop sells candies with a discount: for every two candies bought, you get a third candy for free (its cost must be less than or equal to the minimum of the two bought). Given an array of candy costs, find the minimum total cost to acquire all the candies.

Methods to Solve:
1. Max-Heap / Priority Queue Approach
2. Greedy + Sorting Approach (Optimal)

---------------------------------------------------------
Method 1: Max-Heap (Priority Queue)
---------------------------------------------------------
- Intuition: To maximize our total savings, we must maximize the cost of the "free" candies. By pairing the most expensive candies together, we get the next largest available candy for free. A Max-Heap naturally serves the largest remaining elements continuously.
- Approach: Push all candy costs into a max-heap. While there are at least 3 candies in the heap, extract the top two (add their costs to the total) and discard the third (this is the free one). If fewer than 3 candies remain, simply extract and pay for the rest.
- Dry Run: 
    cost = [1, 2, 3]
    Heap: [3, 2, 1]
    Pop 3 (cost += 3) -> Pop 2 (cost += 2) -> Pop 1 (free, discarded)
    Total Cost = 5
- Time Complexity: O(N log N) for inserting and popping elements from the priority queue.
- Space Complexity: O(N) to store the elements inside the priority queue data structure.
- Why better than previous method: This is a solid baseline simulation of the process.
- When to use: When implementing a natural simulation of the real-world process, or if dealing with a continuous stream of prices rather than a static array.

---------------------------------------------------------
Method 2: Greedy + Sorting Approach (Optimal)
---------------------------------------------------------
- Intuition: Similar to the heap logic, we want to skip paying for the most expensive possible candies. Sorting the array descending allows us to group candies into triplets easily. In each triplet, we pay for the first two and get the third for free.
- Approach: Sort the `cost` array in descending order. Iterate through the array, keeping track of a 1-based position index. We add the candy's cost to our total unless it falls on a multiple of 3 (i.e., the 3rd, 6th, 9th candy), which represents the free items.
- Dry Run: 
    cost = [6, 5, 7, 9, 2, 2]
    Sorted Descending: [9, 7, 6, 5, 2, 2]
    Index 1: 9 (pay, total = 9)
    Index 2: 7 (pay, total = 16)
    Index 3: 6 (free, skip)
    Index 4: 5 (pay, total = 21)
    Index 5: 2 (pay, total = 23)
    Index 6: 2 (free, skip)
    Total Cost = 23
- Time Complexity: O(N log N) due to the sorting step. The iteration itself is O(N).
- Space Complexity: O(1) or O(log N) auxiliary space depending on the language's internal sorting algorithm.
- Why better than previous method: It avoids the O(N) auxiliary space overhead of the Priority Queue by sorting in place.
- When to use: This is the most optimal and standard approach for competitive programming and interviews.

Comparison Table:
Method          | TC         | SC         | Best Use Case
----------------|------------|------------|---------------------------
1. Max-Heap     | O(N log N) | O(N)       | Simulation / Data streams
2. Greedy Sort  | O(N log N) | O(1)       | Standard optimal solution

Final Recommended Solution: Method 2 (Greedy + Sorting)
*/

#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

class Solution {
public:
    // Method 1: Max-Heap (Priority Queue) Simulation
    int minimumCostHeap(vector<int>& cost) {
        priority_queue<int> pq;
        for (int c : cost) {
            pq.push(c);
        }

        int min_cost = 0;
        
        // Group by triplets
        while (pq.size() >= 3) {
            min_cost += pq.top(); pq.pop(); // Pay for 1st most expensive
            min_cost += pq.top(); pq.pop(); // Pay for 2nd most expensive
            pq.pop();                       // 3rd is free
        }

        // Pay for any leftovers (1 or 2 candies)
        while (!pq.empty()) {
            min_cost += pq.top();
            pq.pop();
        }

        return min_cost;
    }

    // Method 2: Optimal Greedy + Sorting
    int minimumCost(vector<int>& cost) {
        // Sort costs in descending order to maximize free candy value
        sort(cost.rbegin(), cost.rend());

        int min_cost = 0;
        
        for (int i = 0; i < cost.size(); ++i) {
            // 0-indexed positions 2, 5, 8... are multiples of 3 (1-indexed 3, 6, 9...)
            // We get these for free, so we only add to cost if (i + 1) is NOT a multiple of 3
            if ((i + 1) % 3 != 0) {
                min_cost += cost[i];
            }
        }

        return min_cost;
    }
};
