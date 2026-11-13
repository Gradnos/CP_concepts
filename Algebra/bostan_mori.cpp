// [x^k] P(x)/Q(x) via Bostan-Mori. Q[0] must be 1. O(M(d) log k).
// Mostly used with generating functions: the n-th term of a linear recurrence is
// [x^n] P(x)/Q(x). Good problem: https://codeforces.com/contest/1912/problem/J
// Source: https://codeforces.com/blog/entry/111862
#include "vector"
using namespace std;
#define sz(v) (ll)v.size()
#define pb push_back
#define ll long long

using poly = vector<ll>;

poly operator*(const poly& a, const poly& b) {   // naive; swap for FFT/NTT if needed
    poly r(sz(a) + sz(b) - 1);
    for (int i = 0; i < sz(a); i++)
        for (int j = 0; j < sz(b); j++)
            r[i + j] += a[i] * b[j];
    return r;
}

ll bostan_mori(ll k, poly P, poly Q) {
    while (k) {
        poly Qm = Q;
        for (int i = 1; i < sz(Qm); i += 2) Qm[i] = -Qm[i];
        poly U = P * Qm, V = Q * Qm, NP, NQ;
        for (int i = k & 1; i < sz(U); i += 2) NP.pb(U[i]);
        for (int i = 0; i < sz(V); i += 2) NQ.pb(V[i]);
        P = NP, Q = NQ, k >>= 1;
    }
    return P[0];   // == P[0]/Q[0] because Q[0] == 1
}
