/*
Date: 12-05-2026
Problem Name: Minimum Initial Energy to Finish Tasks
Platform: LeetCode (Problem #1665)
Difficulty: Hard
Tags: Array, Greedy, Sorting, Binary Search

Problem Summary:
You are given an array 'tasks' where tasks[i] = [actual_i, minimum_i]. 
- actual_i: Energy spent to finish the task.
- minimum_i: Energy required to start the task.
You can finish tasks in any order. The goal is to find the minimum initial energy 
required to complete all tasks.

Methods to Solve:

1. Binary Search on Answer (with Greedy Check)
- Intuition: The required energy is monotonic. If energy 'E' is sufficient, 
  any energy > 'E' is also sufficient. This allows us to binary search the answer.
- Approach: 
    - Sort tasks based on the difference (minimum - actual) in descending order. 
      This is because tasks with a larger "requirement-to-cost" buffer should be handled 
      while we have more energy.
    - Binary search in the range [sum of actuals, 10^9].
    - In the check function, simulate the tasks in the sorted order.
- Dry Run: 
    Tasks: [[1,3], [2,4], [10,11]] -> Sorted by (m-a) desc: [1,3] (diff 2), [2,4] (diff 2), [10,11] (diff 1).
    Check E=13: Task 1 (13>=3, E=12), Task 2 (12>=4, E=10), Task 3 (10>=11 - FAIL).
- Time Complexity: O(N log N + N log(Range)) where Range is 10^9.
- Space Complexity: O(1) or O(N) depending on sorting implementation.
- Why better than previous: First logical step to handle monotonicity.
- When to use: When the search space is defined and a greedy check is available.

2. Pure Greedy Sorting (Optimal Approach)
- Intuition: We can determine the exact energy needed by iterating through the sorted 
  tasks just once. By sorting tasks by (minimum - actual) descending, we prioritize 
  tasks that require a high "start-up" energy relative to what they actually consume.
- Approach:
    - Sort tasks by (tasks[i][1] - tasks[i][0]) descending.
    - Maintain 'current_energy' and 'initial_energy'.
    - For each task, if 'current_energy' < task[1], increase 'initial_energy' and 
      'current_energy' by the deficit (task[1] - current_energy).
    - Subtract task[0] from 'current_energy'.
- Dry Run: 
    Tasks: [[1,2], [2,4], [4,8]] -> Diffs: [1, 2, 4]. Sorted desc: [[4,8], [2,4], [1,2]].
    Start: initial=0, current=0.
    Task [4,8]: current < 8, so add (8-0)=8. initial=8, current=8. Process: current = 8-4 = 4.
    Task [2,4]: current(4) >= 4. Process: current = 4-2 = 2.
    Task [1,2]: current(2) >= 2. Process: current = 2-1 = 1.
    Final initial: 8.
- Time Complexity: O(N log N) due to sorting.
- Space Complexity: O(1).
- Why better than previous: Eliminates the log(Range) factor of binary search.
- When to use: This is the most efficient approach for this problem type.

Comparison Table:
Method               | TC            | SC   | Best Use Case
-----------------------------------------------------------------------
Binary Search        | O(N log N)    | O(1) | General monotonic problems.
Pure Greedy Sorting  | O(N log N)    | O(1) | Optimal for this specific task.

Final Recommended Solution: Pure Greedy Sorting.
*/

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    /**
     * @brief Calculates the minimum initial energy using the optimal Greedy Sorting approach.
     * * Logic: We sort tasks by the difference (minimum - actual) descending. 
     * This ensures we tackle tasks with higher starting requirements relative to 
     * their cost while our energy pool is at its peak.
     */
    int minimumEffort(vector<vector<int>>& tasks) {
        // Sort tasks based on the difference between minimum required and actual energy
        // (minimum[i] - actual[i]) in descending order.
        sort(tasks.begin(), tasks.end(), [](const vector<int>& a, const vector<int>& b) {
            return (a[1] - a[0]) > (b[1] - b[0]);
        });

        int initialEnergy = 0;
        int currentEnergy = 0;

        for (const auto& task : tasks) {
            int actual = task[0];
            int minimum = task[1];

            // If current energy is less than the minimum required for this task
            if (currentEnergy < minimum) {
                // Add the deficit to both the initial pool and current pool
                initialEnergy += (minimum - currentEnergy);
                currentEnergy = minimum;
            }
            
            // Spend the actual energy required for the task
            currentEnergy -= actual;
        }

        return initialEnergy;
    }

    /**
     * @brief Alternative approach: Binary Search on Answer.
     * Provided for comprehensive understanding of different architectural patterns.
     */
    int minimumEffortBinarySearch(vector<vector<int>>& tasks) {
        sort(tasks.begin(), tasks.end(), [](const vector<int>& a, const vector<int>& b) {
            return (a[1] - a[0]) > (b[1] - b[0]);
        });

        auto canFinish = [&](int energy) {
            for (const auto& task : tasks) {
                if (energy < task[1]) return false;
                energy -= task[0];
            }
            return true;
        };

        int low = 0, high = 1e9; // 1e9 is safe based on constraints (10^5 * 10^4)
        int ans = high;

        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (canFinish(mid)) {
                ans = mid;
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }
        return ans;
    }
};
