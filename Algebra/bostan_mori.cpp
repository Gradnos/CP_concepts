// idea -> https://codeforces.com/blog/entry/111862
// good problem -> https://codeforces.com/contest/1912/problem/J
//====
// find the coefficent a of x^k in P(x)/Q(x) polynomyal
// O(M(d)*log(k)) where d is degree of polynomial and M(d) is polynomial multiplication time 
//===
// mostly used with generating functions
#include "vector"
using namespace std;

#define sz(v) (ll)v.size()
#define pb push_back
#define ll long long


using poly = vector<ll>;
// multiplying polynomials (can be changed for to FFT for faster time complexity)
poly operator*(const poly &a, const poly &b){
    poly res(sz(a)+sz(b)-1);
    for(int i = 0; i < sz(a); i++)
        for(int j = 0; j < sz(b); j++)
            res[i+j]+=a[i]*b[j];
    return res;
}


ll bostan_mori(ll k, poly P, poly Q){
    if(k == 0) return P[0];
    poly Q1 = Q;
    for(int i = 0; i < sz(Q); i++) if(i%2) Q1[i] = -Q1[i];
    poly PQ1 = P*Q1; //new top but we only care about half of it
    poly QQ1 = Q*Q1; //new bottom but half only even degrees are left 
    poly NP,NQ; // actual new polynomials
    for(int i = 0; i < sz(PQ1); i++) if(i%2 == k%2) NP.pb(PQ1[i]);
    for(int i = 0; i < sz(QQ1); i+=2) NQ.pb(QQ1[i]);
    return bostan_mori(k/2, NP, NQ);
}
