#include <vector>
#include <cassert>
#include <climits>
using namespace std;

// Iterative segment tree, 0-indexed, range queries [l, r). T needs operator+
// and a default value equal to the identity (e.g. 0 for sum, -inf for max).
template<class T> struct segtree {
    int n, size, log;
    vector<T> d;
    segtree(int n = 0) : segtree(vector<T>(n)) {}
    segtree(const vector<T>& v) : n((int)v.size()) {
        log = 0;
        while ((1 << log) < n) log++;
        size = 1 << log;
        d.assign(2 * size, T());
        for (int i = 0; i < n; i++) d[size + i] = v[i];
        for (int i = size - 1; i >= 1; i--) d[i] = d[2 * i] + d[2 * i + 1];
    }
    void set(int p, T x) {
        assert(0 <= p && p < n);
        p += size; d[p] = x;
        for (int i = 1; i <= log; i++) { p >>= 1; d[p] = d[2 * p] + d[2 * p + 1]; }
    }
    T get(int p) { assert(0 <= p && p < n); return d[p + size]; }
    T qr(int l, int r) {                    // [l, r)
        assert(0 <= l && l <= r && r <= n);
        T sml = T(), smr = T();             // identity (must be value-initialized)
        l += size; r += size;
        while (l < r) {
            if (l & 1) sml = sml + d[l++];
            if (r & 1) smr = d[--r] + smr;
            l >>= 1; r >>= 1;
        }
        return sml + smr;
    }
    T all() { return d[1]; }

    // ---- optional: first/last index whose value >= v (constraint queries) ----
    // T must expose a `val` field (the max element in the node) used for pruning,
    // and T() must be "neutral" so padding leaves never satisfy the check.
    int lrec(int i, int l, int r, int v, int id) {   // rightmost index <= id with val >= v
        if (l > id) return -1;
        if (d[i].val < v) return -1;
        if (l + 1 == r) return i - size;
        int m = (l + r) / 2;
        int rans = lrec(i * 2 + 1, m, r, v, id);
        if (rans != -1) return rans;
        return lrec(i * 2, l, m, v, id);
    }
    int rrec(int i, int l, int r, int v, int id) {   // leftmost index >= id with val >= v
        if (r - 1 < id) return -1;
        if (d[i].val < v) return -1;
        if (l + 1 == r) return i - size;
        int m = (l + r) / 2;
        int lans = rrec(i * 2, l, m, v, id);
        if (lans != -1) return lans;
        return rrec(i * 2 + 1, m, r, v, id);
    }
    int qrl(int v, int id) { return (n && id >= 0) ? lrec(1, 0, size, v, min(id, n - 1)) : -1; }
    int qrr(int v, int id) { return (id < n) ? rrec(1, 0, size, v, max(id, 0)) : -1; }
};

// example struct for segtree declaration: values must be default-initializable
// and operator+ merges left and right nodes. This keeps max prefix sum, max
// suffix sum and total sum. The identity {0,0,0} allows the EMPTY subarray, so a
// leaf for element x must be {max(0,x), max(0,x), x} (not {x,x,x}).
struct Info {
    int mxpre = 0;
    int mxsuf = 0;
    int tot = 0;
    Info operator+(const Info& o) const {
        return {max(mxpre, tot + o.mxpre), max(o.mxsuf, o.tot + mxsuf), tot + o.tot};
    }
};

// example for the constraint queries (qrl/qrr): node stores just the max element.
struct MaxNode {
    int val = INT_MIN;
    MaxNode(int v = INT_MIN) : val(v) {}
    MaxNode operator+(const MaxNode& o) const { return max(val, o.val); }
};
