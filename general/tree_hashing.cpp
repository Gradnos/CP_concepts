#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// AHU tree hashing: rooted trees (u, p) are isomorphic iff their hashes are equal.
map<vector<int>, int> mp;
vector<vector<int>> g;

int hashTree(int u, int p) {
    vector<int> h;
    for (int v : g[u]) if (v != p) h.push_back(hashTree(v, u));
    sort(h.begin(), h.end());
    auto it = mp.find(h);
    if (it != mp.end()) return it->second;
    return mp[h] = (int)mp.size();
}
