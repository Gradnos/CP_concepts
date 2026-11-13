#include <vector>
using namespace std;

// Persistent segment tree: point update + range sum, keeps every version.
// 0-indexed positions. node 0 = null. root[version] = root node index.
//
// usage:
//   PST pst({1, 2, 3, 4, 5});      // version 0 = the original array
//   int v1 = pst.set(0, 4, 1);     // version 1: a[4] = 1  (fork of version 0)
//   int v2 = pst.set(v1, 2, 10);   // version 2: a[2] = 10 (fork of version 1)
//   pst.query(0,  0, 4);           // sum over [0,4] in version 0 = 15
//   pst.query(v1, 0, 4);           // sum over [0,4] in version 1 = 11
//   pst.query(v2, 0, 4);           // sum over [0,4] in version 2 = 16
struct PST {
    struct Node { int l = 0, r = 0, sum = 0; };
    vector<Node> t;
    vector<int> root;
    int n;

    PST(const vector<int>& a) : n((int)a.size()) {
        t.push_back(Node());                          // null node
        root.push_back(build(a, 0, n - 1));
    }
    int build(const vector<int>& a, int lo, int hi) {
        int v = (int)t.size(); t.push_back(Node());
        if (lo == hi) { t[v].sum = a[lo]; return v; }
        int m = (lo + hi) / 2;
        t[v].l = build(a, lo, m);
        t[v].r = build(a, m + 1, hi);
        t[v].sum = t[t[v].l].sum + t[t[v].r].sum;
        return v;
    }
    // returns the new version id after setting a[p] = x on top of `version`
    int set(int version, int p, int x) {
        int v = upd(p, x, root[version], 0, n - 1);
        root.push_back(v);
        return (int)root.size() - 1;
    }
    int upd(int p, int x, int prev, int lo, int hi) {
        int v = (int)t.size(); t.push_back(t[prev]);
        if (lo == hi) { t[v].sum = x; return v; }
        int m = (lo + hi) / 2;
        if (p <= m) t[v].l = upd(p, x, t[prev].l, lo, m);
        else        t[v].r = upd(p, x, t[prev].r, m + 1, hi);
        t[v].sum = t[t[v].l].sum + t[t[v].r].sum;
        return v;
    }
    int query(int version, int ql, int qr) { return qry(root[version], ql, qr, 0, n - 1); }  // [ql, qr]
    int qry(int v, int ql, int qr, int lo, int hi) {
        if (!v || qr < lo || hi < ql) return 0;
        if (ql <= lo && hi <= qr) return t[v].sum;
        int m = (lo + hi) / 2;
        return qry(t[v].l, ql, qr, lo, m) + qry(t[v].r, ql, qr, m + 1, hi);
    }
};
