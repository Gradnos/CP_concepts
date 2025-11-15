#include <vector>


#define vec vector
#define ll long long

using namespace std;

ll n, L, timer;
vec<vec<ll>> g(n); // adjacency graph
vec<ll> tin(n), tout(n);
vec<vec<ll>> up;

void dfsL(ll id, ll p){
    tin[id] = ++timer;
    up[0][id] = p;
    for(int i = 1; i <= L; i++) up[i][id] = up[i-1][up[i-1][id]];
    for(auto u : g[id]) if(u != p) dfsL(u,id);
    tout[id] = ++timer;
}

bool isAncestor(ll u, ll v){
    return tin[u] <= tin[v] && tout[v] <= tout[u];
}

ll lca(ll u, ll v){
    if(isAncestor(u,v)) return u;
    if(isAncestor(v,u)) return v;
    for(int i = L; i>= 0; i--) if(!isAncestor(up[i][u], v)) u = up[i][u];
    return up[0][u];
}

void initLca(){
    ll root = 0;
    timer = 0;   
    L = ceil(log2(n));
    up.assign(L+1, vec<ll>(n));
    dfsL(root,root);
}
