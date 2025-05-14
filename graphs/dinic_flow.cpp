// idea -> https://cp-algorithms.com/graph/dinic.html
// good pbolem -> https://codeforces.com/gym/103438/problem/I
// ===
// find MAX FLOW in a graph.
// O(sqrt(V)*E) - in bipartite graph
// O(min(v^(2/3),sqrt(E)) * E) - in Unit capacity graph
// O(v^2*E) - in worst graphs
// ===
// used in max flow, min cut, max independent subset, bipartite matching ...
#include<iostream>
#include "vector"
#include <queue>

using namespace std;

#define ll long long
#define pb push_back
#define sz(v) (int)v.size()

const ll  N = 1e5;
const ll inf = 1e18;

// needed this kind of array for fast updates on capacities;
struct edge{
    ll to, capacity;
}edges[N];

ll vertex_count = 100;
ll s = 0, t = vertex_count+1; // SOURCE is at [0] index and  SINK is at [vertex_count+1], in total vertex_count+2

vector<ll> adj[N];
ll currentEdgeId = 0;
void addEdge(ll from, ll to, ll capacity){
    
    // forward edge
    edges[currentEdgeId] = {to, capacity};
    adj[from].pb(currentEdgeId); 

    // backward edge
    edges[currentEdgeId+1] = {from, 0};
    adj[to].pb(currentEdgeId+1);

    currentEdgeId+=2; // for later additions
}

ll level[N]; // for tracking which level a vertex is from source
bool bfs(){
    // reset before start
    fill(level,level+N,0); 
    level[s] = 1;

    queue<ll> q; q.push(s);
    while(!q.empty()){
        ll u = q.front(); q.pop();
        for(int i = 0; i < sz(adj[u]); i++){
            ll eid = adj[u][i];
            auto [v,capacity] = edges[eid];
            if(capacity > 0 && level[v] == 0){
                level[v] = level[u]+1;
                q.push(v); // you could check if current is the SINK and stop but finishing probably helps dfs in saturating the paths
            }
        }
    }
    return level[t] != 0;
}

// try to add as much flow as possible and prune bad vertexes.
ll dfs(ll u, ll pushed){
    if(pushed == 0 || u == t) return pushed;
    ll cur = 0;
    for(int i = 0; i < sz(adj[u]); i++){
        ll eid = adj[u][i];
        auto [v,capacity] = edges[eid];
        if(capacity > 0 && level[v] == level[u] + 1){
            ll pos = dfs(v, min(pushed-cur, capacity));
            edges[eid].capacity-=pos; // subtract new flow from forward edge
            edges[eid^1].capacity+=pos; // add new flow to reverse edge
            cur+=pos; if(cur == pushed) break;
        }
    }
    if(cur < pushed) level[u] = 0; // if the given flow was not used fully, no more flow can go here so prune this node for others
    return cur;
}



ll dinic(){
    ll current = 0;
    while(bfs()) current+=dfs(s,inf);
    return current;
}