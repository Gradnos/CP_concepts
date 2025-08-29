#include<iostream>
#include "vector"
#include <queue>


using namespace std;


#define ll long long
#define rep(i,a,b) for(ll i = (a); i <= (b); i++)
#define per(i,a,b) for(ll i = (a); i >= (b); i--)
#define vec vector

const ll N = 2e5;
const ll M = 1e9+7;


void storeBridge(ll x, ll y){
    // store how you want
}

void findBridges(vec<vec<ll>> &adj, ll n){
    ll timer = 0;
    vec<bool> vis(n+1);
    vec<ll> tin(n+1,-1), low(n+1,-1);

    auto dfs = [&](auto &&dfs, ll id, ll p = -1)-> void{
        vis[id] = 1;
        tin[id] = low[id] = timer++;
        for(auto u : adj[id]){
            if(u ==p) continue;
            if(vis[u]) low[id] = min(low[id], tin[u]);
            else{
                dfs(dfs, u, id);
                low[id] = min(low[id], low[u]);
                if(low[u] > tin[id]) storeBridge(id,u);
            }
        }
    };
    
    rep(i,1,n) if(!vis[i]) dfs(dfs,i);

}


// different dfs if multiple edges are allowed
// makes sure that the parent only gets skipped once
auto dfs = [&](auto &&dfs, ll id, ll p = -1)-> void{
    vis[id] = 1;
    tin[id] = low[id] = timer++;
    bool parSkipped = 0;
    for(auto u : adj[id]){
        if(u ==p && !parSkipped){
            parSkipped = 1; 
            continue;
        }
        if(vis[u]) low[id] = min(low[id], tin[u]);
        else{
            dfs(dfs, u, id);
            low[id] = min(low[id], low[u]);
            if(low[u] > tin[id]) storeBridge(id,u);
        }
    }
};



