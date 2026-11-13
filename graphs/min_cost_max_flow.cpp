#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Min-cost max-flow (successive shortest paths with potentials). No negative cycles.
struct MCMF {
    struct Edge { int to; ll flo, cap, cost; };
    int n;
    vector<ll> pot, dist;
    vector<int> pre;
    vector<Edge> eds;
    vector<vector<int>> adj;

    MCMF(int n) : n(n), pot(n), dist(n), pre(n), adj(n) {}
    void addEdge(int u, int v, ll cap, ll cost) {
        adj[u].push_back((int)eds.size()); eds.push_back({v, 0, cap, cost});
        adj[v].push_back((int)eds.size()); eds.push_back({u, 0, 0, -cost});
    }
    bool path(int s, int t) {
        const ll inf = 4e18;
        fill(dist.begin(), dist.end(), inf);
        using T = pair<ll, int>;
        priority_queue<T, vector<T>, greater<T>> pq;
        pq.push({dist[s] = 0, s});
        while (!pq.empty()) {
            auto [d, u] = pq.top(); pq.pop();
            if (d > dist[u]) continue;
            for (int id : adj[u]) {
                auto& e = eds[id];
                if (e.flo < e.cap && d + e.cost + pot[u] - pot[e.to] < dist[e.to]) {
                    dist[e.to] = d + e.cost + pot[u] - pot[e.to];
                    pre[e.to] = id;
                    pq.push({dist[e.to], e.to});
                }
            }
        }
        return dist[t] != inf;
    }
    pair<ll, ll> calc(int s, int t) {   // returns {max flow, min cost}
        // initial potentials via Bellman-Ford (handles negative edge costs)
        for (int it = 0; it < n; it++)
            for (int e = 0; e < (int)eds.size(); e++) {
                auto& E = eds[e];
                if (E.cap) pot[E.to] = min(pot[E.to], pot[eds[e ^ 1].to] + E.cost);
            }
        ll totFlow = 0, totCost = 0;
        while (path(s, t)) {
            for (int i = 0; i < n; i++) pot[i] += dist[i];
            ll df = 4e18;
            for (int x = t; x != s; x = eds[pre[x] ^ 1].to) df = min(df, eds[pre[x]].cap - eds[pre[x]].flo);
            totFlow += df;
            totCost += (pot[t] - pot[s]) * df;
            for (int x = t; x != s; x = eds[pre[x] ^ 1].to) {
                eds[pre[x]].flo += df;
                eds[pre[x] ^ 1].flo -= df;
            }
        }
        return {totFlow, totCost};
    }
};
