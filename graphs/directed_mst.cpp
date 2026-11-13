#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define vec vector
#define pb push_back
#define sz(v) (ll)v.size()
#define all(v) v.begin(), v.end()
#define fr(i,n) for(int i = 0; i < n; i++)

/**
 * Minimum directed spanning tree (arborescence) rooted at `root`.
 * Chu-Liu / Edmonds' algorithm, O(V * E).
 *
 * Returns {totalWeight, ok}. If `ok` is false, not every vertex is
 * reachable from `root` (no arborescence exists).
 *
 * Edge weights may be negative. Parallel edges and self-loops are allowed.
 * Source: Wikipedia "Edmonds' algorithm" (Chu-Liu/Edmonds).
 */
struct Edge { int u, v; ll w; };

pair<ll, bool> directedMST(int n, int root, vec<Edge> edges) {
    const ll INF = 4e18;
    ll res = 0;
    vec<int> pre(n), id(n), vis(n);

    while (true) {
        // 1) For each vertex, pick its minimum incoming edge.
        vec<ll> in(n, INF);
        for (const Edge& e : edges)
            if (e.u != e.v && e.w < in[e.v])
                in[e.v] = e.w, pre[e.v] = e.u;
        in[root] = 0;
        fr(i, n)
            if (in[i] == INF) return {res, false};  // unreachable from root

        // 2) Detect and contract cycles.
        int cnt = 0;
        fill(all(id), -1);
        fill(all(vis), -1);
        fr(i, n) {
            res += in[i];
            int v = i;
            while (vis[v] != i && id[v] == -1 && v != root) {
                vis[v] = i;
                v = pre[v];
            }
            if (v != root && id[v] == -1) {         // found a cycle -> contract it
                for (int u = pre[v]; u != v; u = pre[u]) id[u] = cnt;
                id[v] = cnt++;
            }
        }
        if (cnt == 0) break;                        // no cycles: this is the answer

        // 3) Relabel the remaining (non-cycle) vertices.
        fr(i, n)
            if (id[i] == -1) id[i] = cnt++;

        // 4) Rebuild edges, adjusting weights by the chosen incoming edge.
        vec<Edge> ne;
        for (const Edge& e : edges) {
            int u = id[e.u], v = id[e.v];
            if (u != v) ne.pb({u, v, e.w - in[e.v]});
        }
        edges = move(ne);
        n = cnt;
        root = id[root];
    }
    return {res, true};
}
