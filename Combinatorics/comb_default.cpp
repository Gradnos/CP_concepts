

using namespace std;


#define ll long long

const ll N = 2e5;
const ll M = 1e9;

ll binp(ll a, ll b){
    if(b == 0) return 1;
    ll k = binp(a,b/2);
    k = (k*k)%M;
    if(b&1) k = (k*a)%M;
    return k;
}
 
ll inv(ll a){
    return binp(a,M-2);
}
 
 
ll f[N+1], fi[N+1];
void initFact(){
    f[0] = fi[0] = 1;
    for(int i = 1; i <= N; i++){
        f[i] = (f[i-1] * i) % M;
        fi[i] = inv(f[i]);
    }
}
 
ll C(ll n, ll k){
    if(k > n) return 0;
    return f[n] * fi[k] % M * fi[n-k] % M;
}
 