#include <vector>
using namespace std;
using ll = long long;

struct LCA {
    int n, L, timer;
    vector<vector<int>> g, up;
    vector<int> tin, tout;

    LCA(int n) : n(n), g(n), tin(n), tout(n) {
        L = 1; while ((1 << L) <= n) L++;
        up.assign(L + 1, vector<int>(n));
    }
    void addEdge(int u, int v) { g[u].push_back(v); g[v].push_back(u); }

    void dfs(int u, int p) {
        tin[u] = ++timer;
        up[0][u] = p;
        for (int i = 1; i <= L; i++) up[i][u] = up[i - 1][up[i - 1][u]];
        for (int v : g[u]) if (v != p) dfs(v, u);
        tout[u] = ++timer;
    }
    bool isAncestor(int u, int v) { return tin[u] <= tin[v] && tout[v] <= tout[u]; }
    int lca(int u, int v) {
        if (isAncestor(u, v)) return u;
        if (isAncestor(v, u)) return v;
        for (int i = L; i >= 0; i--) if (!isAncestor(up[i][u], v)) u = up[i][u];
        return up[0][u];
    }
    void build(int root = 0) { timer = 0; dfs(root, root); }
};
