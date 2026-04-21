# Minimize Hamming Distance After Swap Operations

Solved LeetCode 1722. Minimize Hamming Distance After Swap Operations using C++.

## Problem Statement

You are given two integer arrays `source` and `target` of length `n`.

You are also given `allowedSwaps`, where each pair `[a, b]` means you can swap elements at indices `a` and `b` in `source` any number of times.

Return the minimum Hamming distance between `source` and `target` after performing any number of swaps.

The Hamming distance is the number of positions where:

`source[i] != target[i]`

---

## Approach

### Key Idea

Indices connected through allowed swaps form groups.

Within each connected component:

- Any values can be rearranged freely.
- Count frequencies of values in `source`.
- Match values with `target`.
- Unmatched values contribute to Hamming distance.

We use **Disjoint Set Union (DSU)** to find connected components.

### Why Efficient?

Instead of simulating swaps, DSU groups swappable indices directly.

---

## Data Structures Used

- `DSU / Union Find`
- `unordered_map<int,int>` for frequency counting
- `unordered_map<int, vector<int>>` for components

---

## C++ Code

```cpp
class Solution {
public:
    vector<int> parent, rankv;

    int find(int x) {
        if (parent[x] != x)
            parent[x] = find(parent[x]);
        return parent[x];
    }

    void unite(int a, int b) {
        int pa = find(a), pb = find(b);
        if (pa == pb) return;

        if (rankv[pa] < rankv[pb])
            swap(pa, pb);

        parent[pb] = pa;

        if (rankv[pa] == rankv[pb])
            rankv[pa]++;
    }

    int minimumHammingDistance(vector<int>& source, vector<int>& target, vector<vector<int>>& allowedSwaps) {
        int n = source.size();

        parent.resize(n);
        rankv.assign(n, 0);

        for (int i = 0; i < n; i++)
            parent[i] = i;

        for (auto& e : allowedSwaps)
            unite(e[0], e[1]);

        unordered_map<int, vector<int>> groups;

        for (int i = 0; i < n; i++)
            groups[find(i)].push_back(i);

        int ans = 0;

        for (auto& g : groups) {
            unordered_map<int, int> freq;

            for (int idx : g.second)
                freq[source[idx]]++;

            for (int idx : g.second) {
                if (freq[target[idx]] > 0)
                    freq[target[idx]]--;
                else
                    ans++;
            }
        }

        return ans;
    }
};
