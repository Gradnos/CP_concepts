#include <iostream>
#include <vector>

using namespace std;
#define ll long long
#define vec vector



int n, k;
vector<vector<int>> g;
vector<int> mt;
vector<ll> it;

bool try_kuhn(int v, ll cit) {
    if (it[v] == cit)
        return false;
    it[v] = cit;
    for (int to : g[v]) {
        if (mt[to] == -1 || try_kuhn(mt[to], cit)) {
            mt[to] = v;
            return true;
        }
    }
    return false;
}


int main(){
    mt.assign(k, -1);
    ll cit = 1;
    for (int v = 0; v < n; ++v) {
        try_kuhn(v, cit);
        cit++;
    }
}