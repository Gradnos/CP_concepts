// ===
// clasic fenwick tree. for fast single element updates for prefix sum
// O(log(n)) update(add), query(get)
// ===
// used in max flow, min cut, max independent subset, bipartite matching ...

#include<iostream>
#include "vector"

using namespace std;

#define ll long long
#define pb push_back
#define sz(v) (int)v.size()



template<typename T>
struct FEN{
    int n;
    vector<T> f;
    FEN(int n) : n(n), f(n + 1) {}
    void add(int id, T x) {
        for (; id <= n; id += id & -id)f[id] += x;
    }

    ll get(int id) const {
        ll sum = 0;
        for (; id > 0; id -= id & -id) sum += f[id];
        return sum;
    }

    ll range_sum(int l, int r) {
         return get(r) - get(l - 1);
    }
};