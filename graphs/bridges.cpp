#include <vector>
using namespace std;
using ll = long long;

// Returns all bridges of an undirected graph (multi-edges allowed).
vector<pair<int,int>> bridges;
vector<vector<int>> adj;
vector<int> tin, low;
vector<char> vis;
int timer;

void dfs(int u, int p = -1) {
    vis[u] = 1;
    tin[u] = low[u] = timer++;
    bool skipped = false;
    for (int v : adj[u]) {
        if (v == p && !skipped) { skipped = true; continue; }   // skip parent once (multi-edges)
        if (vis[v]) low[u] = min(low[u], tin[v]);
        else {
            dfs(v, u);
            low[u] = min(low[u], low[v]);
            if (low[v] > tin[u]) bridges.push_back({u, v});
        }
    }
}

vector<pair<int,int>> findBridges(int n) {
    bridges.clear();
    tin.assign(n, -1); low.assign(n, -1); vis.assign(n, 0); timer = 0;
    for (int i = 0; i < n; i++) if (!vis[i]) dfs(i);
    return bridges;
}
