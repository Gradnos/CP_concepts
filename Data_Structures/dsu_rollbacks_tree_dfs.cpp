#include <bits/stdc++.h>
using namespace std;

#define vec vector
#define all(v) v.begin(), v.end()
#define pb push_back

struct DSU {
    vec<int> p, siz;
    int cnt;
    vec<pair<int*, int>> hist;
 
    DSU(int n) : p(n), siz(n, 1), cnt(0) {
        iota(all(p), 0);
    }
 
    int get(int x) {
        return p[x] == x ? x : get(p[x]);
    }
 
    void unite(int x, int y) {
        x = get(x); y = get(y);
        if (x == y) return;
        if (siz[x] < siz[y]) swap(x, y);
 
        hist.pb({&cnt, cnt});
        hist.pb({&siz[x], siz[x]});
        hist.pb({&p[y], p[y]});
 
        cnt++;
        siz[x] += siz[y];
        p[y] = x;
    }
 
    int snap() { return hist.size(); }
 
    void rollback(int s) {
        while ((int)hist.size() > s) {
            *hist.back().first = hist.back().second;
            hist.pop_back();
        }
    }
};
 
struct Query {
    int u, v;
};
 
struct SegTree {
    int n;
    vec<vec<Query>> t;
 
    SegTree(int n) : n(n), t(4 * n) {}
 
    void add(int ql, int qr, Query q, int v, int l, int r) {
        if (qr <= l || r <= ql) return;
        if (ql <= l && r <= qr) {
            t[v].pb(q);
            return;
        }
        int m = (l + r) / 2;
        add(ql, qr, q, v * 2, l, m);
        add(ql, qr, q, v * 2 + 1, m, r);
    }
 
    void add(int l, int r, Query q) {
        add(l, r, q, 1, 0, n);
    }
 
    void dfs(int v, int l, int r, DSU &dsu, vec<int> &ans) {
        int s = dsu.snap();
        for (auto [u, w] : t[v]) dsu.unite(u, w);
 
        if (l + 1 == r) {
            ans[l] = dsu.cnt;
        } else {
            int m = (l + r) / 2;
            dfs(v * 2, l, m, dsu, ans);
            dfs(v * 2 + 1, m, r, dsu, ans);
        }
 
        dsu.rollback(s);
    }
 
    void dfs(DSU &dsu, vec<int> &ans) {
        dfs(1, 0, n, dsu, ans);
    }
};