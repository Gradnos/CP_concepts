/**
 * Description: Minimum-cost maximum flow, assumes no negative cycles. 
* It is possible to choose negative edge costs such that the first 
* run of Dijkstra is slow, but this hasn't been an issue in the past. 
* Edge weights $\ge 0$ for every subsequent run. To get flow through 
* original edges, assign ID's during \texttt{ae}.
* Time: Ignoring first run of Dijkstra, $O(FM\log M)$ 
* if caps are integers and $F$ is max flow.
* Source: GeeksForGeeks
* https://courses.csail.mit.edu/6.854/06/scribe/s12-minCostFlowAlg.pdf
* running time is only pseudo-polynomial; see https://codeforces.com/blog/entry/70740
* https://en.wikipedia.org/wiki/Johnson%27s_algorithm (to get non-negative weights)
* https://codeforces.com/contest/1316/submission/72472865 
    * mango_lassi, min cost circulation w/ capacity scaling
* Verification: https://codeforces.com/contest/164/problem/C
* https://codeforces.com/contest/316/problem/C2
    * TLEs, don't use priority queue
*/

#include <iostream>
#include <vector>
#include <assert.h>
#include <queue>


#define ll long long
#define vec vector
#define pb push_back
#define sz(v) (int)v.size()
#define fr(i,n) for(ll i = 0; i < n; i++)
#define F first
#define S second

template<class T>
bool ckmin(T &a, const T &b) {
    return b < a ? a = b, 1 : 0;
}


using namespace std;


struct MCMF { 
	using F = ll; using C = ll; // flow type, cost type
	struct Edge { int to; F flo, cap; C cost; };
	int N; vec<C> p, dist; vec<int> pre; vec<Edge> eds; vec<vec<int>> adj;
	void init(int _N) { N = _N;
		p.resize(N), dist.resize(N), pre.resize(N), adj.resize(N); }
	void ae(int u, int v, F cap, C cost) { assert(cap >= 0); 
		adj[u].pb(sz(eds)); eds.pb({v,0,cap,cost}); 
		adj[v].pb(sz(eds)); eds.pb({u,0,0,-cost});
	} // use asserts, don't try smth dumb
	bool path(int s, int t) { // find lowest cost path to send flow through
		const C inf = numeric_limits<C>::max(); fr(i,N) dist[i] = inf;
		using T = pair<C,int>; priority_queue<T,vector<T>,greater<T>> todo; 
		todo.push({dist[s] = 0,s}); 
		while (sz(todo)) { // Dijkstra
			T x = todo.top(); todo.pop(); if (x.F > dist[x.S]) continue;
			for(auto e : adj[x.S]) { const Edge& E = eds[e]; // all weights should be non-negative
				if (E.flo < E.cap && ckmin(dist[E.to],x.F+E.cost+p[x.S]-p[E.to]))
					pre[E.to] = e, todo.push({dist[E.to],E.to});
			}
		} // if costs are doubles, add some EPS so you 
		// don't traverse ~0-weight cycle repeatedly
		return dist[t] != inf; // return flow
	}
	pair<F,C> calc(int s, int t) { assert(s != t);
		fr(_,N) fr(e,sz(eds)) { const Edge& E = eds[e]; // Bellman-Ford
			if (E.cap) ckmin(p[E.to],p[eds[e^1].to]+E.cost); }
		F totFlow = 0; C totCost = 0;
		while (path(s,t)) { // p -> potentials for Dijkstra
			fr(i,N) p[i] += dist[i]; // don't matter for unreachable nodes
			F df = numeric_limits<F>::max();
			for (int x = t; x != s; x = eds[pre[x]^1].to) {
				const Edge& E = eds[pre[x]]; ckmin(df,E.cap-E.flo); }
			totFlow += df; totCost += (p[t]-p[s])*df;
			for (int x = t; x != s; x = eds[pre[x]^1].to)
				eds[pre[x]].flo += df, eds[pre[x]^1].flo -= df;
		} // get max flow you can send along path
		return {totFlow,totCost};
	}
};