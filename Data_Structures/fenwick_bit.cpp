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



// index starts at 1
void add (vector<ll>& f, ll id, ll x){ // add x to f[id]
    for(;id<sz(f); id+=id&(-id)) f[id]+=x;
};

ll get(vector<ll>& f, ll id){ // get the prefix sum to f[id] including
    ll sum = 0;
    for(;id;id-=id&(-id)) sum+=f[id];
    return sum;
};