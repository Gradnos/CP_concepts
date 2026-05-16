#include <bits/stdc++.h>
using namespace std;

using ld = long double;
const ld EPS = 1e-9;
const ld PI = acosl(-1);

int sgn(ld x) { return (x > EPS) - (x < -EPS); }

struct P {
    ld x, y;

    P() : x(0), y(0) {}
    P(ld x, ld y) : x(x), y(y) {}

    P operator + (const P& p) const { return {x + p.x, y + p.y}; }
    P operator - (const P& p) const { return {x - p.x, y - p.y}; }
    P operator * (ld k) const { return {x * k, y * k}; }
    P operator / (ld k) const { return {x / k, y / k}; }
    bool operator == (const P& p) const {
        return sgn(x - p.x) == 0 && sgn(y - p.y) == 0;
    }
    bool operator < (const P& p) const {
        return sgn(x - p.x) ? x < p.x : y < p.y;
    }
    ld dot(P p) const { return x * p.x + y * p.y; }
    ld cross(P p) const { return x * p.y - y * p.x; }

    // optional
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
    ld angle() const {
        return atan2l(y, x);
    }
};

// +1 -> left turn / counterclockwise
// -1 -> right turn / clockwise
//  0 -> collinear
int orient(P a, P b, P c) {
    return sgn((b - a).cross(c - a));
}


// ANGLE SORT AROUND POINT

P O;
bool upper(P p) {
    p = p - O;
    return sgn(p.y) > 0 || (sgn(p.y) == 0 && sgn(p.x) >= 0);
}
bool angleCmp(P a, P b) {
    bool A = upper(a);
    bool B = upper(b);

    if (A != B) return A > B;

    return sgn((a - O).cross(b - O)) > 0;
}
// sort(v.begin(), v.end(), angleCmp);


// POLY AREA
ld polygonArea2(const vector<P>& p) {
    ld a = 0;
    int n = p.size();

    for (int i = 0; i < n; i++)
        a += p[i].cross(p[(i + 1) % n]);

    return a;
}

ld polygonArea(const vector<P>& p) {
    return fabsl(polygonArea2(p)) / 2;
}


// CONVEX HULL
vector<P> convexHull(vector<P> p) {
    sort(p.begin(), p.end());
    p.erase(unique(p.begin(), p.end()), p.end());

    int n = p.size();
    if (n <= 1) return p;

    vector<P> h(2 * n);
    int sz = 0;

    for (int i = 0; i < n; i++) {
        // change to < 0 if want collinear
        while (sz >= 2 &&
               sgn((h[sz - 1] - h[sz - 2]).cross(p[i] - h[sz - 1])) <= 0) 
            sz--;
        h[sz++] = p[i];
    }

    int t = sz + 1;

    for (int i = n - 2; i >= 0; i--) {
        // change to < 0 if want collinear
        while (sz >= t &&
               sgn((h[sz - 1] - h[sz - 2]).cross(p[i] - h[sz - 1])) <= 0)
            sz--;
        h[sz++] = p[i];
    }

    h.resize(sz - 1);
    return h;
}

// LINE AND SEG
bool lineInter(P a, P b, P c, P d, P& out) {
    ld d1 = (b - a).cross(d - c);

    if (sgn(d1) == 0)
        return false;

    ld t = (c - a).cross(d - c) / d1;
    out = a + (b - a) * t;

    return true;
}

P proj(P a, P b, P p) {
    P v = b - a;
    return a + v * (v.dot(p - a) / v.norm2());
}

ld distLine(P a, P b, P p) {
    return fabsl((b - a).cross(p - a)) / (b - a).norm();
}

ld distSeg(P a, P b, P p) {
    if (sgn((b - a).dot(p - a)) < 0)
        return p.dist(a);

    if (sgn((a - b).dot(p - b)) < 0)
        return p.dist(b);

    return distLine(a, b, p);
}

bool onSeg(P a, P b, P p) {
    return sgn((a - p).cross(b - p)) == 0 &&
           sgn((a - p).dot(b - p)) <= 0;
}

bool segInter(P a, P b, P c, P d) {
    ld d1 = (b - a).cross(c - a);
    ld d2 = (b - a).cross(d - a);
    ld d3 = (d - c).cross(a - c);
    ld d4 = (d - c).cross(b - c);

    if (sgn(d1) * sgn(d2) < 0 &&
        sgn(d3) * sgn(d4) < 0)
        return true;

    return onSeg(a,b,c) || onSeg(a,b,d) ||
           onSeg(c,d,a) || onSeg(c,d,b);
}



// MIN ENCLOSING CIRCLE
struct Circle {
    P o;
    ld r;
};

bool inCircle(Circle c, P p) {
    return sgn(c.o.dist(p) - c.r) <= 0;
}

Circle circle2(P a, P b) {
    return {(a + b) / 2, a.dist(b) / 2};
}

Circle circle3(P a, P b, P c) {
    b = b - a;
    c = c - a;

    ld d = 2 * b.cross(c);

    P p = a + P(
        c.y * b.norm2() - b.y * c.norm2(),
        b.x * c.norm2() - c.x * b.norm2()
    ) / d;

    return {p, p.dist(a)};
}

Circle mec(vector<P> p) {
    shuffle(p.begin(), p.end(), mt19937(time(0)));

    Circle c{{0,0}, -1};

    for (int i = 0; i < p.size(); i++) {
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
