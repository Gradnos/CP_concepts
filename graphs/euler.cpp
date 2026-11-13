#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define vec vector
#define pb push_back
#define sz(v) (ll)v.size()
#define all(v) v.begin(), v.end()
#define fr(i,n) for(int i = 0; i < n; i++)

/**
 * Hierholzer's algorithm for Eulerian cycle / path (iterative, so it does not
 * overflow the stack on deep graphs).
 * Returns the walk as a sequence of vertices of length (#edges + 1).
 * The caller must pass a valid start vertex (see findEulerStart*).
 * Assumes the graph is connected (isolated vertices are allowed).
 *
 * Source: cp-algorithms.com "Finding the Eulerian path" (Hierholzer).
 */

// Directed graph: edges are (from, to). Each edge used exactly once.
vec<int> eulerDirected(int n, const vec<pair<int,int>>& edges, int start) {
    int m = sz(edges);
    vec<vec<pair<int,int>>> adj(n);                 // (to, edge_id)
    fr(i, m) adj[edges[i].first].pb({edges[i].second, i});

    vec<int> ptr(n, 0), res;
    stack<int> st;
    st.push(start);
    while (!st.empty()) {
        int v = st.top();
        if (ptr[v] < sz(adj[v])) {
            st.push(adj[v][ptr[v]++].first);
        } else {
            res.pb(v);
            st.pop();
        }
    }
    reverse(all(res));
    return res;
}

// Undirected graph: edges are (u, v). Each edge used once (either direction).
vec<int> eulerUndirected(int n, const vec<pair<int,int>>& edges, int start) {
    int m = sz(edges);
    vec<vec<pair<int,int>>> adj(n);                 // (to, edge_id)
    fr(i, m) {
        adj[edges[i].first].pb({edges[i].second, i});
        adj[edges[i].second].pb({edges[i].first, i});
    }

    vec<int> ptr(n, 0), used(m, 0), res;
    stack<int> st;
    st.push(start);
    while (!st.empty()) {
        int v = st.top();
        while (ptr[v] < sz(adj[v]) && used[adj[v][ptr[v]].second]) ptr[v]++;
        if (ptr[v] < sz(adj[v])) {
            auto [to, id] = adj[v][ptr[v]++];
            used[id] = 1;
            st.push(to);
        } else {
            res.pb(v);
            st.pop();
        }
    }
    reverse(all(res));
    return res;
}

// Start vertex for a directed Eulerian path/circuit, or -1 if none exists.
int findEulerStartDirected(int n, const vec<pair<int,int>>& edges) {
    vec<int> in(n), out(n);
    for (auto& e : edges) out[e.first]++, in[e.second]++;
    int start = -1, end = -1;
    fr(i, n) {
        if (out[i] == in[i]) continue;
        if (out[i] - in[i] == 1)      { if (start != -1) return -1; start = i; }
        else if (in[i] - out[i] == 1) { if (end   != -1) return -1; end   = i; }
        else return -1;
    }
    if (start == -1) {                  // circuit: any vertex with an outgoing edge
        fr(i, n) if (out[i]) return i;
        return 0;
    }
    return start;
}

// Start vertex for an undirected Eulerian path/circuit, or -1 if none exists.
int findEulerStartUndirected(int n, const vec<pair<int,int>>& edges) {
    vec<int> deg(n);
    for (auto& e : edges) deg[e.first]++, deg[e.second]++;
    int start = -1, odd = 0;
    fr(i, n) {
        if (deg[i] & 1) { odd++; if (start == -1) start = i; }
    }
    if (odd != 0 && odd != 2) return -1;
    if (start == -1) {
        fr(i, n) if (deg[i]) return i;
        return 0;
    }
    return start;
}
