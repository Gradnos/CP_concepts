#include "bits/stdc++.h"
using namespace std;

// Pisinger's balanced subset sum: largest subset sum <= t. O(n * maxw) time, O(maxw) memory.
int knapsack(const vector<int>& w, int t) {
    int a = 0, b = 0, n = w.size();
    while (b < n && a + w[b] <= t) a += w[b++];   // greedy, break item b
    if (b == n) return a;                          // everything fits
    int m = *max_element(w.begin(), w.end());
    vector<int> u, v(2 * m, -1);                   // index x <-> sum x + t - m, i.e. range (t-m, t+m]
    v[a + m - t] = b;
    for (int i = b; i < n; i++) {
        u = v;
        for (int x = 0; x < m; x++)                // sum <= t: insert item i
            v[x + w[i]] = max(v[x + w[i]], u[x]);
        for (int x = 2 * m - 1; x >= m; x--)       // sum > t: remove items, high sums first
            for (int j = max(0, u[x]); j < v[x]; j++)
                v[x - w[j]] = max(v[x - w[j]], j);
    }
    for (a = t; v[a + m - t] < 0; a--);
    return a;
}