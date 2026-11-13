#include <bits/stdc++.h>
using namespace std;
using ld = long double;
const ld EPS = 1e-9;
const ld PI = acosl(-1);

int sgn(ld x) { return (x > EPS) - (x < -EPS); }

// ---------------- point / vector ----------------
struct P {
    ld x, y;
    P() : x(0), y(0) {}
    P(ld x, ld y) : x(x), y(y) {}
    P operator + (const P& p) const { return {x + p.x, y + p.y}; }
    P operator - (const P& p) const { return {x - p.x, y - p.y}; }
    P operator * (ld k) const { return {x * k, y * k}; }
    P operator / (ld k) const { return {x / k, y / k}; }
    bool operator == (const P& p) const { return sgn(x - p.x) == 0 && sgn(y - p.y) == 0; }
    bool operator < (const P& p) const { return sgn(x - p.x) ? x < p.x : y < p.y; }
    ld dot(P p) const { return x * p.x + y * p.y; }
    ld cross(P p) const { return x * p.y - y * p.x; }
    ld cross(P a, P b) const { return (a - *this).cross(b - *this); }
    ld norm2() const { return x * x + y * y; }
    ld norm() const { return sqrtl(norm2()); }
    P unit() const { return *this / norm(); }
    P perp() const { return {-y, x}; }
    ld dist(P p) const { return (*this - p).norm(); }
    ld dist2(P p) const { return (*this - p).norm2(); }
    P rotate(ld a) const {
        ld c = cosl(a), s = sinl(a);
        return {x * c - y * s, x * s + y * c};
    }
    ld angle() const { return atan2l(y, x); }
};

// ---------------- basics ----------------
ld sqr_diff(ld a, ld b) { return (a + b) * (a - b); }   // a^2 - b^2 (numerically stable)
P middle(P a, P b) { return (a + b) / 2; }
ld angle(P a, P b) {                                     // angle between vectors, in [0, PI]
    ld c = a.dot(b) / (a.norm() * b.norm());
    c = max((ld)-1, min((ld)1, c));
    return acosl(c);
}

// +1 -> left turn / counterclockwise, -1 -> right turn / clockwise, 0 -> collinear
int orient(P a, P b, P c) {
    ld val = (b - a).cross(c - a);
    ld scale = (b - a).norm() * (c - a).norm() * EPS;
    return (val > scale) - (val < -scale);
}

// ---------------- sorted around O, angle 0 in direction D ----------------
// sort points by polar angle around O; D is the direction vector of angle 0
// and angles increase CCW. Set O and D before sorting.
P O, D;

bool half(P p) {   // is vector p-O in the half [0, PI) measured from direction D?
    P v = p - O;
    ld cr = D.cross(v);
    return sgn(cr) > 0 || (sgn(cr) == 0 && D.dot(v) >= 0);
}

bool angleCmp(P a, P b) {
    bool A = half(a), B = half(b);
    if (A != B) return A > B;
    return sgn((a - O).cross(b - O)) > 0;
}
// sort(v.begin(), v.end(), angleCmp);

// ---------------- polygon ----------------
ld polygonArea2(const vector<P>& p) {   // 2 * signed area
    ld a = 0;
    int n = (int)p.size();
    for (int i = 0; i < n; i++) a += p[i].cross(p[(i + 1) % n]);
    return a;
}
ld polygonArea(const vector<P>& p) { return fabsl(polygonArea2(p)) / 2; }
ld triangleArea(P a, P b, P c) { return fabsl((b - a).cross(c - a)) / 2; }
P polygonCenter(const vector<P>& v) {   // centroid of a polygon
    P res(0, 0);
    ld A = 0;
    int n = (int)v.size();
    for (int i = 0, j = n - 1; i < n; j = i++) {
        ld c = v[j].cross(v[i]);
        res = res + (v[i] + v[j]) * c;
        A += c;
    }
    return res / A / 3;
}

// ---------------- convex hull ----------------
// include_collinear = true keeps points on hull edges too.
vector<P> convexHull(vector<P> p, bool include_collinear = false) {
    sort(p.begin(), p.end());
    p.erase(unique(p.begin(), p.end()), p.end());
    int n = (int)p.size();
    if (n <= 1) return p;
    // fully-collinear degenerate case: monotone chain would duplicate points.
    // NOTE: use exact cross, NOT orient() (relative EPS) — near-collinear points
    // with large coordinates must not be collapsed into a segment.
    bool allCollinear = true;
    for (int i = 2; i < n && allCollinear; i++)
        if ((p[1] - p[0]).cross(p[i] - p[0]) != 0) allCollinear = false;
    if (allCollinear)
        return include_collinear ? p : vector<P>{p[0], p[n - 1]};
    vector<P> h(2 * n);
    int sz = 0, lim = include_collinear ? -1 : 0;
    for (int i = 0; i < n; i++) {
        while (sz >= 2 && sgn((h[sz - 1] - h[sz - 2]).cross(p[i] - h[sz - 1])) <= lim) sz--;
        h[sz++] = p[i];
    }
    int t = sz + 1;
    for (int i = n - 2; i >= 0; i--) {
        while (sz >= t && sgn((h[sz - 1] - h[sz - 2]).cross(p[i] - h[sz - 1])) <= lim) sz--;
        h[sz++] = p[i];
    }
    h.resize(sz - 1);
    return h;
}

// ---------------- line / segment ----------------
bool lineInter(P a, P b, P c, P d, P& out) {   // line ab x line cd
    ld d1 = (b - a).cross(d - c);
    if (sgn(d1) == 0) return false;            // parallel
    ld t = (c - a).cross(d - c) / d1;
    out = a + (b - a) * t;
    return true;
}
bool parallel(P a, P b, P c, P d) { return sgn((b - a).cross(d - c)) == 0; }
P proj(P a, P b, P p) {                         // projection of p onto line ab
    P v = b - a;
    return a + v * (v.dot(p - a) / v.norm2());
}
P reflect(P p, P a, P b) { return proj(a, b, p) * 2 - p; }   // reflection across line ab
ld distLine(P a, P b, P p) { return fabsl((b - a).cross(p - a)) / (b - a).norm(); }
ld distSeg(P a, P b, P p) {
    if (sgn((b - a).dot(p - a)) < 0) return p.dist(a);
    if (sgn((a - b).dot(p - b)) < 0) return p.dist(b);
    return distLine(a, b, p);
}
bool onSeg(P a, P b, P p) { return sgn((a - p).cross(b - p)) == 0 && sgn((a - p).dot(b - p)) <= 0; }
bool segInter(P a, P b, P c, P d) {
    ld d1 = (b - a).cross(c - a), d2 = (b - a).cross(d - a);
    ld d3 = (d - c).cross(a - c), d4 = (d - c).cross(b - c);
    if (sgn(d1) * sgn(d2) < 0 && sgn(d3) * sgn(d4) < 0) return true;
    return onSeg(a, b, c) || onSeg(a, b, d) || onSeg(c, d, a) || onSeg(c, d, b);
}

// ---------------- circle ----------------
struct Circle { P o; ld r; };
bool inCircle(Circle c, P p) { return sgn(c.o.dist(p) - c.r) <= 0; }
Circle circle2(P a, P b) { return {(a + b) / 2, a.dist(b) / 2}; }   // diameter ab
Circle circle3(P a, P b, P c) {                                     // circumcircle
    b = b - a; c = c - a;
    ld d = 2 * b.cross(c);
    P p = a + P(c.y * b.norm2() - b.y * c.norm2(), b.x * c.norm2() - c.x * b.norm2()) / d;
    return {p, p.dist(a)};
}
Circle mec(vector<P> p) {   // minimum enclosing circle
    shuffle(p.begin(), p.end(), mt19937(time(0)));
    Circle c{{0, 0}, -1};
    int n = (int)p.size();
    for (int i = 0; i < n; i++) {
        if (c.r >= 0 && inCircle(c, p[i])) continue;
        c = {p[i], 0};
        for (int j = 0; j < i; j++) {
            if (inCircle(c, p[j])) continue;
            c = circle2(p[i], p[j]);
            for (int k = 0; k < j; k++) {
                if (inCircle(c, p[k])) continue;
                c = circle3(p[i], p[j], p[k]);
            }
        }
    }
    return c;
}

// ---------------- half-plane intersection ----------------
// Each half-plane keeps the region to the LEFT of its directed line (a -> b).
// hp_intersect returns the vertices of the intersection polygon in CCW order,
// or an empty vector if the intersection is empty/unbounded-in-a-way (boxed).
struct Halfplane {
    P p, pq;              // p = a point on the line, pq = direction vector
    ld angle;
    Halfplane() : p(), pq(), angle(0) {}
    Halfplane(const P& a, const P& b) : p(a), pq(b - a) { angle = pq.angle(); }
    bool out(const P& r) const { return sgn(pq.cross(r - p)) < 0; }   // r is on the right
    bool operator < (const Halfplane& e) const { return angle < e.angle; }
};
P hpInter(const Halfplane& s, const Halfplane& t) {
    ld alpha = (t.p - s.p).cross(t.pq) / s.pq.cross(t.pq);
    return s.p + s.pq * alpha;
}
vector<P> hp_intersect(vector<Halfplane> H) {
    P box[4] = {P(1e9, 1e9), P(-1e9, 1e9), P(-1e9, -1e9), P(1e9, -1e9)};
    for (int i = 0; i < 4; i++) H.push_back(Halfplane(box[i], box[(i + 1) % 4]));
    sort(H.begin(), H.end());
    deque<Halfplane> dq;
    int len = 0;
    for (int i = 0; i < (int)H.size(); i++) {
        while (len > 1 && H[i].out(hpInter(dq[len - 1], dq[len - 2]))) { dq.pop_back(); --len; }
        while (len > 1 && H[i].out(hpInter(dq[0], dq[1]))) { dq.pop_front(); --len; }
        if (len > 0 && sgn(H[i].pq.cross(dq[len - 1].pq)) == 0) {
            if (H[i].pq.dot(dq[len - 1].pq) < 0) return vector<P>();  // opposite half-planes
            if (H[i].out(dq[len - 1].p)) { dq.pop_back(); --len; }
            else continue;
        }
        dq.push_back(H[i]); ++len;
    }
    while (len > 2 && dq[0].out(hpInter(dq[len - 1], dq[len - 2]))) { dq.pop_back(); --len; }
    while (len > 2 && dq[len - 1].out(hpInter(dq[0], dq[1]))) { dq.pop_front(); --len; }
    if (len < 3) return vector<P>();
    vector<P> ret(len);
    for (int i = 0; i + 1 < len; i++) ret[i] = hpInter(dq[i], dq[i + 1]);
    ret.back() = hpInter(dq[len - 1], dq[0]);
    return ret;
}
