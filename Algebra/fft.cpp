// NTT (Number-Theoretic Transform) mod 998244353: exact polynomial multiplication.
// multiply(a, b) returns the convolution of a and b mod 998244353 (no rounding error).
#include <bits/stdc++.h>
using namespace std;
#define ll long long
const ll MOD = 998244353, G = 3;

ll pw(ll a, ll b) { ll r = 1; for (; b; b >>= 1, a = a * a % MOD) if (b & 1) r = r * a % MOD; return r; }

// in-place iterative NTT (Cooley-Tukey, mod 998244353). n must be a power of 2 <= 2^23.
void ntt(vector<ll>& a, bool invert) {
    int n = (int)a.size();
    for (int i = 1, j = 0; i < n; i++) {          // bit-reversal permutation
        int bit = n >> 1;
        for (; j & bit; bit >>= 1) j ^= bit;
        j ^= bit;
        if (i < j) swap(a[i], a[j]);
    }
    for (int len = 2; len <= n; len <<= 1) {
        ll wlen = pw(G, (MOD - 1) / len);
        if (invert) wlen = pw(wlen, MOD - 2);
        for (int i = 0; i < n; i += len) {
            ll w = 1;
            for (int j = 0; j < len / 2; j++) {
                ll u = a[i + j], v = a[i + j + len / 2] * w % MOD;
                a[i + j] = (u + v) % MOD;
                a[i + j + len / 2] = (u - v + MOD) % MOD;
                w = w * wlen % MOD;
            }
        }
    }
    if (invert) { ll inv = pw(n, MOD - 2); for (ll& x : a) x = x * inv % MOD; }
}

// polynomial multiplication mod 998244353.
vector<ll> multiply(vector<ll> a, vector<ll> b) {
    if (a.empty() || b.empty()) return {};
    for (ll& x : a) x = (x % MOD + MOD) % MOD;
    for (ll& x : b) x = (x % MOD + MOD) % MOD;
    int need = (int)a.size() + (int)b.size() - 1, n = 1;
    while (n < need) n <<= 1;
    a.resize(n); b.resize(n);
    ntt(a, false); ntt(b, false);
    for (int i = 0; i < n; i++) a[i] = a[i] * b[i] % MOD;
    ntt(a, true);
    a.resize(need);
    return a;
}
