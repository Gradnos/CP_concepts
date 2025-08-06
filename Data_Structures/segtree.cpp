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