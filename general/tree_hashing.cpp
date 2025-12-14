#include <map>
#include <vector>
#include <algorithm>

using namespace std;

#define ll long long
#define vec vector
#define pb push_back
#define all(v) v.begin(), v.end()



map<vec<ll>,ll> hashes;
vec<vec<ll>> g;
ll root = 0;
ll lastid = 0;

ll hashTree(ll id, ll p){
    vec<ll> children;
    for(auto u : g[id]){
        if(u == p) continue;
        children.pb(hashTree(u,id));
    }
    sort(all(children));
    if(hashes.count(children)) return hashes[children];
    hashes[children] = ++lastid;
    return lastid;
}
