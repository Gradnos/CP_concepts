// ===
// clasic segment tree. for fast single element updates and range queries
// O(log(n)) update(add), query(get)
// ===
#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>


#define vec vector
#define pb push_back
#define sz(v) (int)v.size()

using namespace std;



// 0 indexed segment tree
template<class T> struct segtree{
    int _n, size, log;
    vec<T> d;
    segtree(): segtree(0){};
    segtree(int n) : segtree(vec<T>(n)){};
    segtree(const vec<T> &v) : _n(sz(v)){
        log = 0;
        while((1<<log) < _n) log++;
        size = 1<<log;
        d = vec<T>(2*size);
        for(int i = 0; i < _n; i++) d[size+i] = v[i];
        for(int i = size - 1; i>=1; i--) upd(i);
    }
 
    void upd(int k) {d[k] = d[2*k] + d[2*k+1];}
 
    void set(int p, T x){
        assert(0<=p && p < _n);
        p+=size;
        d[p] = x;
        for(int i = 1; i <= log; i++) upd(p>>i);
    }
    
    T get(int p){
        assert(0 <= p && p < _n);
        return d[p+size];
    }
 
    // queryes [l, r) meaning {l, l+1 ... r-1} 
    T qr(int l, int r){
        assert(0 <= l && l <= r && r <= _n);
        T sml, smr;
        l+=size;
        r+=size;
 
        while(l < r){
            if(l&1) sml = sml + d[l++];
            if(r&1) smr = d[--r] + smr;
            l >>= 1;
            r >>= 1;
        }
        return sml + smr;
    }
    
    // optional   (v, id) are for constaint
    
    // ll lrec(ll i, ll l, ll r, ll v, ll id){
    //     if(l > id) return -1;
    //     if(d[i].vala < v) return -1; // a check for constraint
    //     if(l+1 == r) return i - size;
    //     ll m = (l + r) / 2;
    //     ll rans = lrec(i*2+1,m,r,v,id);
    //     if(rans != -1) return rans;
    //     return lrec(i*2,l,m,v,id);
    // };
 
    // ll rrec(ll i, ll l, ll r, ll v, ll id){
    //     if(r-1 < id) return -1;
    //     if(d[i].valb < v) return -1; // a check for constraint
    //     if(l+1 == r) return i - size;
    //     ll m = (l+r) / 2;
    //     ll lans = rrec(i*2,l,m,v,id);
    //     if(lans != -1) return lans;
    //     return rrec(i*2+1, m,r,v,id);
    // }
 
 
    // ll qrl(ll v, ll id){
    //     return lrec(1,0,size,v,id);
    // }
 
    // ll qrr(ll v, ll id){
    //     return rrec(1,0,size,v,id);
    // }
 

    T allqr(){
        return d[1];
    }
};
 
 
// example struct for segtree declaration, values must be initialied by default and operator + is megring left and right nodes
struct Info{
    int mxpre = 0;
    int mxsuf = 0;
    int tot = 0;
 
    Info operator+(const Info &o){
        int npre = max(mxpre, tot+o.mxpre);
        int nsuf = max(o.mxsuf, o.tot + mxsuf);
        return {npre, nsuf, tot + o.tot};
    }
 
};
