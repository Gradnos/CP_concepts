#include <vector>
using namespace std;

// Fenwick tree: point add + prefix sum. 1-indexed positions.
template<typename T>
struct FEN {
    int n;
    vector<T> f;
    FEN(int n) : n(n), f(n + 1) {}
    void add(int id, T x) { for (; id <= n; id += id & -id) f[id] += x; }
    T get(int id) const { T s = 0; for (; id > 0; id -= id & -id) s += f[id]; return s; }
    T range_sum(int l, int r) { return get(r) - get(l - 1); }   // [l, r] inclusive
};
