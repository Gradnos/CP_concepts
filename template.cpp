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
#define show(x) cout<<#x<<"="<<x
#define double double

#define rep(i,a,b) for(ll i = (a); i <= (b); i++)
#define per(i,a,b) for(ll i = (a); i >= (b); i--)
#define fr(i,n) for(ll i = 0; i < n; i++)
#define rf(i,n) for(ll i = n-1; i>=0; i--)
#define prend(x) {cout<<(x)<<"\n"; return;}

#define PR cout<<
#define NDL <<"\n"<<
#define ND <<"\n"
#define SPS <<" "<<
#define SP <<" "

mt19937_64 gen(chrono::steady_clock::now().time_since_epoch().count());
uniform_int_distribution<ll> rnd(0,LLONG_MAX);
// ll randint = rnd(gen);

int inf = 1e9;
ll linf = 1e18;
const ll N = 200000;
const ll M = 998244353;
double pi = acos(-1);    
bool multiCase = 0;
const double eps = 1e-6;

void solve(){}

void preprocess(){}

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif  
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    cout<<fixed<<setprecision(15);
    ll tt = 1;
    if(multiCase) cin >> tt;
    preprocess();
    while (tt--){
        solve();
    }
}
