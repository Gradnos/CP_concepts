#include "comb_default.h"
using namespace std;

// Catalan numbers: C_n = C(2n, n) / (n + 1). Requires initFact().
mint catalan(ll n) {
    return C(2 * n, n) / mint(n + 1);
}

// Bell numbers (count set partitions): B_0 = 1, B_{n+1} = sum_{k=0}^n C(n,k) B_k.
// Requires initFact(). Values are cached across calls.
mint bell(ll n) {
    static vector<mint> B{1};
    while ((ll)B.size() <= n) {
        ll i = (ll)B.size();          // compute B[i]
        mint s = 0;
        for (ll k = 0; k < i; k++) s = s + C(i - 1, k) * B[k];
        B.push_back(s);
    }
    return B[n];
}
