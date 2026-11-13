#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define vec vector
#define pb push_back
#define sz(v) (ll)v.size()
#define all(v) v.begin(), v.end()
#define fr(i,n) for(int i = 0; i < n; i++)

/**
 * Stoer-Wagner global minimum cut (undirected, weighted, non-negative weights).
 * mat[i][j] = weight of edge (i,j); 0 means no edge (symmetric matrix).
 * Self-loops (diagonal) are allowed and ignored correctly.
 * Returns {minCutValue, oneSide}: oneSide lists the vertices of one side
 * of an optimal cut (empty when the graph has no edges).
 * Complexity: O(V^3).
 */
pair<ll, vec<int>> stoerWagner(vec<vec<ll>> mat) {
    const ll INF = 4e18;
    int n = (int)mat.size();
    if (n == 0) return {INF, {}};

    pair<ll, vec<int>> best = {INF, {}};
    vec<vec<int>> co(n);                    // co[i] = original vertices contracted into i
    fr(i, n) co[i] = {i};

    for (int ph = 1; ph < n; ph++) {
        vec<ll> w = mat[0];                 // w[v] = weight connecting v to the growing set A
        int s = 0, t = 0;                   // s, t = last two vertices added (t = last)
        for (int it = 0; it < n - ph; it++) {
            w[t] = -INF;                    // mark t as taken, never selected again
            s = t;
            t = (int)(max_element(all(w)) - w.begin());
            fr(i, n) w[i] += mat[t][i];
        }
        ll cutVal = w[t] - mat[t][t];       // cut separating t from the rest
        if (cutVal < best.first) best = {cutVal, co[t]};

        co[s].insert(co[s].end(), all(co[t]));  // merge t into s
        fr(i, n) mat[s][i] += mat[t][i];
        fr(i, n) mat[i][s] = mat[s][i];
        mat[0][t] = -INF;                   // remove vertex t from future phases
    }
    return best;
}
