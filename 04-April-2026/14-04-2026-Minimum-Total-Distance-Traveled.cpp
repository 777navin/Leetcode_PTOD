/*🚀 LeetCode Daily | 2463. Minimum Total Distance Traveled
💡 Problem Overview

Aaj ka problem tha Hard level DP + Greedy combination

👉 Given:

Robots ke positions
Factories ke positions + repair limit

🎯 Goal:
Har robot ko assign karo kisi factory ko, aise ki
total travel distance minimum ho

🧠 Key Insight

Sabse important observation:

✔ Agar robots aur factories dono sort kar dein
→ Optimal assignment bhi sorted order follow karega

👉 Matlab:

Left robots → left factories
Cross assignment avoid → distance minimize
⚙️ Approach (DP + Greedy)
dp[i] = minimum distance to repair first i robots

For each factory:

Try assigning k robots (within limit)
Cost calculate karo (distance sum)
DP update karo

👉 Reverse loop use kiya to avoid reuse issue

📊 Complexity
⏱ Time: O(F * N * Limit)
💾 Space: O(N) */

//code
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

class Solution {
public:
    long long minimumTotalDistance(vector<int>& robot, vector<vector<int>>& factory) {
        sort(robot.begin(), robot.end());
        sort(factory.begin(), factory.end());

        int n = robot.size();
        vector<ll> dp(n + 1, 1e18);
        dp[0] = 0;

        for (const auto& f : factory) {
            int pos = f[0], limit = f[1];

            for (int i = n; i >= 0; --i) {
                ll cost = 0;

                for (int k = 1; k <= min(i, limit); ++k) {
                    cost += abs((ll)robot[i - k] - pos);
                    dp[i] = min(dp[i], dp[i - k] + cost);
                }
            }
        }

        return dp[n];
    }
};
