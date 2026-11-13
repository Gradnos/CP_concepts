#include <vector>
using namespace std;

// 2-SAT (Kosaraju). The formula is a conjunction of clauses of the form (a OR b).
//   clause ( x OR  y) -> addOr(x, 0, y, 0)
//   clause ( x OR !y) -> addOr(x, 0, y, 1)
//   clause (!x OR  y) -> addOr(x, 1, y, 0)
// solve() returns a satisfying assignment, or empty if unsatisfiable.
struct TwoSAT {
    int n;
    vector<vector<int>> g, gt;
    vector<char> used;
    vector<int> order, comp;

    TwoSAT(int n) : n(n), g(2 * n), gt(2 * n), used(2 * n), comp(2 * n, -1) {}

    void addImpl(int a, int b) { g[a].push_back(b); gt[b].push_back(a); }
    void addOr(int a, bool na, int b, bool nb) {   // (a xor na) OR (b xor nb)
        a = 2 * a ^ na; b = 2 * b ^ nb;
        addImpl(a ^ 1, b);
        addImpl(b ^ 1, a);
    }

    void dfs1(int v) { used[v] = 1; for (int u : g[v]) if (!used[u]) dfs1(u); order.push_back(v); }
    void dfs2(int v, int cl) { comp[v] = cl; for (int u : gt[v]) if (comp[u] == -1) dfs2(u, cl); }

    // returns an assignment, or empty if unsatisfiable
    vector<char> solve() {
        for (int i = 0; i < 2 * n; i++) if (!used[i]) dfs1(i);
        for (int i = 2 * n - 1, j = 0; i >= 0; i--) if (comp[order[i]] == -1) dfs2(order[i], j++);
        vector<char> ans(n);
        for (int i = 0; i < n; i++) {
            if (comp[2 * i] == comp[2 * i + 1]) return {};
            ans[i] = comp[2 * i] > comp[2 * i + 1];
        }
        return ans;
    }
};
