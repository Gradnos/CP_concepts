#include <vector>
using namespace std;
using ll = long long;

struct Centroid {
    int n;
    vector<vector<int>> g;
    vector<int> siz, dead, par;

    Centroid(int n) : n(n), g(n), siz(n), dead(n), par(n) {}
    void addEdge(int x, int y) { g[x].push_back(y); g[y].push_back(x); }

    int sizeDfs(int u, int p) {
        siz[u] = 1;
        for (int v : g[u]) if (v != p && !dead[v]) siz[u] += sizeDfs(v, u);
        return siz[u];
    }
    int findCentroid(int u, int p, int tot) {
        for (int v : g[u]) if (v != p && !dead[v] && siz[v] > tot / 2) return findCentroid(v, u, tot);
        return u;
    }
    void build(int u = 0, int p = -1) {   // par = parent in the centroid tree
        int tot = sizeDfs(u, p);
        int c = findCentroid(u, p, tot);
        par[c] = p;
        dead[c] = 1;
        for (int v : g[c]) if (!dead[v]) build(v, c);
    }
};
