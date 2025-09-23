#include "comb_default.h"
using namespace std;

#define ll long long


mint strbr(ll st, ll br){
    return C(st+br-1, br-1);
}
 
// returns the amount of ways to create arrays of SIZE(n) SUM(M) MAX_ELEMENT(mx)
// works in ~ O(M/mx) operations not including the time to compute C(n,k)
mint strbrUprBnd(ll n, ll m, ll mx){ // sum, gropus, max element(upperbound)
    if(n < 0)return 0;
    if(n == 0)return m == 0;
    mint ans = 0;
    for(ll t = 0; t <= n && t*(mx+1) <= m; t++){
        mint added = C(n,t)*strbr(m-t*(mx+1), n);
        if(t%2) added = added * (M-1);
        ans = ans+added;
    }   
    return ans;
}









