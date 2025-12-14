#include <deque>
#include <vector>
using namespace std;

using ll = long long;
#define sz(v) (int)v.size()
struct line {
    ll k, b; 
    line(ll k, ll b) : k(k), b(b){}
    double eval(ll x) { return x * k + b; }
    double interX(line o) { return ((double)o.b - (double)b) / ((double)k - (double)o.k); }
    bool behind(line a, line o) {
        return (a.b - b) * (k - o.k) <= (o.b - b) * (k - a.k);
    }
};
struct lines {
    deque<line> dq;
    void add(line l) {
        while (sz(dq) > 1 && dq[sz(dq)-2].behind(l, dq.back())) dq.pop_back();
        dq.push_back(l);
    }
    ll qr(ll x) {
        while (sz(dq) > 1 && dq[0].eval(x) >= dq[1].eval(x)) dq.pop_front();
        if (sz(dq) == 0) return 1e18;
        return dq[0].eval(x);
    }
};
struct fen {
    vector<lines> v;
    ll n;
    fen(ll n):n(n) {
        v.resize(n);
    }
    void add(ll id, line l) {
        if (id == 0) {
            ll y = 5;
        }
        for (; id < n; id += id & (-id)) {
            v[id].add(l);
        }
        ll x = 5;
    }
    ll get(ll id, ll i) {
        ll mn = 1e18;
        for (; id>0 ; id -= id & (-id)) mn = min(mn, v[id].qr(i));
        return mn;
    }
};
