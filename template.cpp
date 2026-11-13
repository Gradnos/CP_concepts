#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <map>
#include <stack>
#include <climits>
#include <functional>
#include <numeric>
#include <math.h>
#include <queue>
#include <random>
#include <bitset>
#include <array>
#include <iomanip>
#include <cfloat>
#include <chrono>
#include <cstring>
#include <assert.h>

using namespace std;
#define ll long long
#define pll pair<ll,ll>
#define all(v) v.begin(), v.end()
#define sz(v) (ll)v.size()
#define pb push_back
#define eb emplace_back
#define bpc __builtin_popcount
#define bpcll __builtin_popcountll
#define S second
#define F first
#define vec vector
using ld = long double;

mt19937_64 gen(chrono::steady_clock::now().time_since_epoch().count());
uniform_int_distribution<ll> rnd(0,LLONG_MAX);
// ll randint = rnd(gen);

const ll INF = 4e18;
const ll inf = 2e9;
const ll N = 200000;
const ll M = 998244353;
const ld pi = acosl(-1);    
const ld EPS = 1e-9;

// primes (1e9+7) (1e9+9) (1e18+3) (1e18+9) (1e18+31)

void solve(){

}

int32_t main(){
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(0);
    cout<<fixed<<setprecision(10);
    int t = 1;
    // cin>>t;
    while(t--) solve();
}
