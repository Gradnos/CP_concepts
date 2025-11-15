#include<iostream>
#include "vector"
#include <queue>


using namespace std;


#define ll long long
#define rep(i,a,b) for(ll i = (a); i <= (b); i++)
#define per(i,a,b) for(ll i = (a); i >= (b); i--)
#define vec vector
#define pb push_back
#define all(v) v.begin(), v.end()


const ll N = 2e5;
const ll M = 1e9+7;




// not needed
struct CentInfo{
    vec<pair<ll,ll>> dists;
    ll cid = 0;
    vec<pair<ll,ll>> parinfo;
};
vector<CentInfo> info;



struct Centroid{
    int n = 0;
    vector<ll> siz,dead,par;
    vec<vec<ll>> g;
    Centroid(int n) : n(n), siz(n), dead(n), par(n), g(n) {}
 
    void addEdge(int x, int y){g[x].pb(y); g[y].pb(x);}
 
    int sizeDfs(int id, int p){
        siz[id] = 1;
        for(auto u : g[id]){
            if(u == p || dead[u]) continue;
            siz[id]+=sizeDfs(u,id);
        }
        return siz[id];
    }
 
    int findCentroid(int id, int p, int tot){
        for(auto u : g[id]) 
            if(u != p && !dead[u] && siz[u] > tot/2) 
                return findCentroid(u,id,tot);
        return id;
    }
 
    void distsDfs(int id, int p, int c, int cd = 0){
        info[c].dists.pb({cd,id});
        info[id].parinfo.pb({c,cd});
        for(auto u : g[id]){
            if(u == p || dead[u]) continue;
            distsDfs(u,id,c,cd+1);
        }
    }
 
 
    void build(int id = 0, int p = -1){
        par[id] = p;
        int tot = sizeDfs(id, p);
        int c = findCentroid(id, p, tot);
        dead[c] = 1;
        distsDfs(c,p,c); // not needed
        sort(all(info[c].dists)); // not needed
        for(auto u : g[c]) if(!dead[u]) build(u, c);
    }
 
};
 