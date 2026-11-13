#include <vector>
using namespace std;

// Linear sieve: lp[i] = smallest prime factor of i, pr = list of primes <= N.
void linearSieve(int N, vector<int>& lp, vector<int>& pr) {
    lp.assign(N + 1, 0);
    pr.clear();
    for (int i = 2; i <= N; i++) {
        if (!lp[i]) { lp[i] = i; pr.push_back(i); }
        for (int p : pr) {
            if ((long long)i * p > N) break;   // avoid int overflow
            lp[i * p] = p;
            if (p == lp[i]) break;
        }
    }
}
