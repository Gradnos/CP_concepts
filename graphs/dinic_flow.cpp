#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll INF = 4e18;

// Dinic's max flow. 0-indexed vertices.
// Used for: max flow, min cut, max bipartite matching, max independent set in bipartite graphs.
// Idea: https://cp-algorithms.com/graph/dinic.html
struct Dinic {
    struct Edge { int to; ll cap; };
    int n;
    vector<Edge> edges;
    vector<vector<int>> adj;
    vector<int> level, ptr;

    Dinic(int n) : n(n), adj(n), level(n), ptr(n) {}
    void addEdge(int u, int v, ll cap) {
        adj[u].push_back((int)edges.size()); edges.push_back({v, cap});
        adj[v].push_back((int)edges.size()); edges.push_back({u, 0});
    }
    bool bfs(int s, int t) {
        fill(level.begin(), level.end(), -1);
        queue<int> q; q.push(s); level[s] = 0;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int id : adj[u]) {
                auto& e = edges[id];
                if (e.cap > 0 && level[e.to] == -1) { level[e.to] = level[u] + 1; q.push(e.to); }
            }
        }
        return level[t] != -1;
    }
    ll dfs(int u, int t, ll pushed) {
        if (u == t || pushed == 0) return pushed;
        for (int& cid = ptr[u]; cid < (int)adj[u].size(); cid++) {
            int id = adj[u][cid];
            auto& e = edges[id];
            if (e.cap > 0 && level[e.to] == level[u] + 1) {
                ll tr = dfs(e.to, t, min(pushed, e.cap));
                if (tr) { e.cap -= tr; edges[id ^ 1].cap += tr; return tr; }
            }
        }
        return 0;
    }
    ll maxFlow(int s, int t) {
        ll flow = 0;
        while (bfs(s, t)) {
            fill(ptr.begin(), ptr.end(), 0);
            while (ll pushed = dfs(s, t, INF)) flow += pushed;
        }
        return flow;
    }
};
