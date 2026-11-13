#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Min convex hull trick: lines y = m*x + b, added in non-increasing slope m.
// query(x) returns min over added lines at x (binary search; any x order).
struct Line { ll m, b; ll eval(ll x) const { return m * x + b; } };

struct CHT {
    vector<Line> h;
    double inter(const Line& a, const Line& b) { return (double)(b.b - a.b) / (a.m - b.m); }
    bool bad(const Line& a, const Line& b, const Line& c) { return inter(a, b) >= inter(b, c); }
    void add(Line l) {
        while (h.size() >= 2 && bad(h[h.size() - 2], h.back(), l)) h.pop_back();
        h.push_back(l);
    }
    ll query(ll x) {
        int lo = 0, hi = (int)h.size() - 1;
        while (lo < hi) {
            int mid = (lo + hi) / 2;
            if (h[mid].eval(x) <= h[mid + 1].eval(x)) hi = mid;
            else lo = mid + 1;
        }
        return h[lo].eval(x);
    }
};

// Fenwick of CHTs (1-indexed): add line to position id,
// query min over lines at positions 1..id evaluated at x. Add in slope order.
struct FenwickCHT {
    int n;
    vector<CHT> t;
    FenwickCHT(int n) : n(n), t(n + 1) {}
    void add(int id, Line l) { for (; id <= n; id += id & -id) t[id].add(l); }
    ll query(int id, ll x) {
        ll mn = 4e18;
        for (; id > 0; id -= id & -id) if (!t[id].h.empty()) mn = min(mn, t[id].query(x));
        return mn;
    }
};
