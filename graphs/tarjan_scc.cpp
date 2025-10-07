
#include<vector>

#define ll long long
#define vec vector
#define pb push_back
#define sz(v) (ll)v.size()
#define fr(i,n) for(int i = 0; i < n; i++)

using namespace std;



void tarjan(){
    const int n = 100;
    vec<vec<ll>> g(n);


    ll cnt = 0;
    vec<bool> onstack(n);
    vec<ll> stk;
    vec<ll> low(n, -1);
    vec<ll> ids(n,-1);



    auto dfs = [&](auto && dfs, ll id) -> void{
        ids[id] = cnt++;
        low[id] = ids[id];
        onstack[id] = 1;
        stk.pb(id);

        for(auto u : g[id]){
            if(ids[u] == -1) dfs(dfs,u);
            if(onstack[u]) low[id] = min(low[id], low[u]);
        }

        if(ids[id] == low[id]){
            // new comp 
            while(sz(stk)){
                ll x = stk.back(); stk.pop_back();
                onstack[x] = 0;
                low[x] = low[id];
                // add x to comp  add_to_comp(x, low[id]);
                if(x == id) break;
            }
        }
    };


    fr(i,n){
        if(ids[i] != -1) continue;
        dfs(dfs, i);
    }

}