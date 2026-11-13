#include <vector>
#include <numeric>
using namespace std;

struct DSU {
    vector<int> f, siz;
    DSU(int n) : f(n), siz(n, 1) { iota(f.begin(), f.end(), 0); }
    int leader(int x) { while (x != f[x]) x = f[x] = f[f[x]]; return x; }   // path halving
    bool same(int x, int y) { return leader(x) == leader(y); }
    bool merge(int x, int y) {
        x = leader(x), y = leader(y);
        if (x == y) return false;
        if (siz[x] < siz[y]) swap(x, y);   // union by size
        siz[x] += siz[y];
        f[y] = x;
        return true;
    }
    int size(int x) { return siz[leader(x)]; }
};