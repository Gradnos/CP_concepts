

using namespace std;


#define ll long long
#define rep(i,a,b) for(ll i = (a); i <= (b); i++)
#define per(i,a,b) for(ll i = (a); i >= (b); i--)

const ll N = 2e5;
const ll M = 1e9+7;

// uses M outside
struct mint {
    int v = 0;
    mint(ll x=0){v=(x%M+M)%M;}
    mint pow(ll e)const{
        mint r = 1,a = *this;
        for(;e;e>>=1,a=a*a) if(e&1)r=r*a;
        return r;
    }
    mint inv()const{return pow(M-2);}
    mint operator*(const mint& o)const{return mint(1ll*v*o.v%M);};
    mint operator/(const mint& o)const{return *this * o.inv();}
    mint operator+(const mint& o)const{int res = v+o.v; if(res>=M) res-=M; return mint(res);}
    mint operator-(const mint& o)const{int res = v-o.v; if(res<0) res+=M; return mint(res);}
};
 
 
mint f[N+1], fi[N+1];
void initFact() {
    f[0] = 1;
    rep(i,1,N) f[i] = f[i-1] * i;   

    fi[N] = f[N].inv();
    per(i,N-1,1)fi[i] = fi[i + 1] * (i + 1);
    fi[0] = 1;
}
 
mint C(ll n, ll k){
    if(k > n) return 0;
    return f[n] * fi[k] * fi[n-k];
}

// ll binp(ll a, ll b){
//     if(b == 0) return 1;
//     ll k = binp(a,b/2);
//     k = (k*k)%M;
//     if(b&1) k = (k*a)%M;
//     return k;
// }
 
// ll inv(ll a){
//     return binp(a,M-2);
// }
 
 
// ll f[N+1], fi[N+1];
// void initFact(){
//     f[0] = fi[0] = 1;
//     for(int i = 1; i <= N; i++){
//         f[i] = (f[i-1] * i) % M;
//         fi[i] = inv(f[i]);
//     }
// }
 
// ll C(ll n, ll k){
//     if(k > n) return 0;
//     return f[n] * fi[k] % M * fi[n-k] % M;
// }
 