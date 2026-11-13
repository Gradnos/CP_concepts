// Requires geometry/general_new.cpp (P, ld, sgn, dist2, EPS, ...).
#include "general_new.cpp"

// Closest pair of points, O(n log n) divide and conquer.
// Returns the minimum *squared* distance (ld), or infinity() if no valid pair.
//   closestPair(pts)         : closest pair inside one set.
//   closestPairTwoSets(a, b) : closest pair with one point from each set.

struct Q { P p; int c; };   // a general_new point with a color / set tag

static bool cmpX(const Q& a, const Q& b) {
    return a.p.x != b.p.x ? a.p.x < b.p.x : a.p.y < b.p.y;
}
static bool cmpY(const Q& a, const Q& b) {
    return a.p.y != b.p.y ? a.p.y < b.p.y : a.p.x < b.p.x;
}

static ld best;             // current best squared distance
static bool sameColor;      // true: equal colors (one set); false: different (two sets)

static void upd(const Q& a, const Q& b) {
    if (sameColor == (a.c == b.c)) {
        ld d = a.p.dist2(b.p);
        if (d < best) best = d;
    }
}

static void rec(int l, int r, vector<Q>& a) {
    if (r - l <= 3) {
        for (int i = l; i < r; i++)
            for (int j = i + 1; j < r; j++)
                upd(a[i], a[j]);
        sort(a.begin() + l, a.begin() + r, cmpY);
        return;
    }
    int m = (l + r) >> 1;
    ld midx = a[m].p.x;
    rec(l, m, a);
    rec(m, r, a);

    static vector<Q> tmp;
    tmp.resize(r - l);
    merge(a.begin() + l, a.begin() + m, a.begin() + m, a.begin() + r,
          tmp.begin(), cmpY);
    copy(tmp.begin(), tmp.end(), a.begin() + l);

    int tsz = 0;
    for (int i = l; i < r; i++) {
        ld dx = a[i].p.x - midx;
        if (dx * dx < best) {
            for (int j = tsz - 1; j >= 0; j--) {
                ld dy = a[i].p.y - tmp[j].p.y;
                if (dy * dy >= best) break;
                upd(a[i], tmp[j]);
            }
            tmp[tsz++] = a[i];
        }
    }
}

static ld run(vector<Q> pts, bool same) {
    sort(pts.begin(), pts.end(), cmpX);
    best = numeric_limits<ld>::infinity();
    sameColor = same;
    if (pts.size() >= 2) rec(0, (int)pts.size(), pts);
    return best;
}

ld closestPair(vector<P> pts) {
    vector<Q> q;
    for (const P& p : pts) q.push_back({p, 0});
    return run(q, true);
}

ld closestPairTwoSets(vector<P> a, vector<P> b) {
    vector<Q> q;
    for (const P& p : a) q.push_back({p, 0});
    for (const P& p : b) q.push_back({p, 1});
    return run(q, false);
}
