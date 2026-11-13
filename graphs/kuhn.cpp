#include <vector>
using namespace std;

// Kuhn bipartite matching. g[v] = neighbors of left vertex v; k = #right vertices.
vector<int> mt, it;
bool tryKuhn(int v, const vector<vector<int>>& g, int cit) {
    if (it[v] == cit) return false;
    it[v] = cit;
    for (int to : g[v]) {
        if (mt[to] == -1 || tryKuhn(mt[to], g, cit)) { mt[to] = v; return true; }
    }
    return false;
}
int kuhn(const vector<vector<int>>& g, int k) {   // returns size of a maximum matching
    mt.assign(k, -1);
    it.assign(g.size(), 0);
    int cit = 0, ans = 0;
    for (int v = 0; v < (int)g.size(); v++) if (tryKuhn(v, g, ++cit)) ans++;
    return ans;
}
