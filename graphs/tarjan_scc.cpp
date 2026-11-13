#include <vector>
#include <functional>
using namespace std;
using ll = long long;

// Tarjan SCC. Returns components (each a list of vertices).
vector<vector<int>> tarjan(const vector<vector<int>>& g) {
    int n = (int)g.size(), cnt = 0;
    vector<int> id(n, -1), low(n, -1);
    vector<char> on(n, 0);
    vector<int> stk;
    vector<vector<int>> comps;

    function<void(int)> dfs = [&](int u) {
        id[u] = low[u] = cnt++;
        on[u] = 1; stk.push_back(u);
        for (int v : g[u]) {
            if (id[v] == -1) dfs(v);
            if (on[v]) low[u] = min(low[u], low[v]);
        }
        if (id[u] == low[u]) {
            comps.push_back({});
            while (true) {
                int x = stk.back(); stk.pop_back();
                on[x] = 0;
                comps.back().push_back(x);
                if (x == u) break;
            }
        }
    };
    for (int i = 0; i < n; i++) if (id[i] == -1) dfs(i);
    return comps;
}
