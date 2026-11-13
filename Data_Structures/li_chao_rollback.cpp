#include <bits/stdc++.h>
#define pb push_back
using namespace std;

// Li Chao tree (max) with rollback. Domain is whatever [acl, acr] you pass (root ac=1).
// add() opens a new history frame; rollback() undoes the most recent add().
//
// usage (domain x in [0, n]):
//   lct t(n);
//   t.add(line(a, b), 1, 0, n);       // insert y = a*x + b over [0, n]
//   int best = t.getmax(x, 1, 0, n);  // max y at x
//   t.rollback();                     // undo the last add

struct line{
    int a,b;
    line(int aa,int bb){
        a=aa;
        b=bb;
    }

    int eval(int x){
        return a*x+b;
    }
};

double inter(line l1, line l2){
    return ((double) l2.b-l1.b)/(l1.a-l2.a);
}

struct lct{
    vector<line> tree;
    int n;
    vector<vector<pair<int,line>>> history;

    lct(int nn){
        n=nn;
        tree=vector<line>(4*n+8,line(0,0));
    }

    void add(line l, int ac, int acl, int acr){ //ac=1
        if (ac==1) history.pb({});

        if (l.eval(acl)>=tree[ac].eval(acl) && l.eval(acr)>=tree[ac].eval(acr)){
            history.back().pb(pair<int,line>{ac,tree[ac]});
            tree[ac]=l;
        }
        else if (l.eval(acl)<=tree[ac].eval(acl) && l.eval(acr)<=tree[ac].eval(acr)) return;
        else{
            double mid = inter(l,tree[ac]);
            if ((mid<(acr+acl)/2+0.5) && l.eval(acl)>=tree[ac].eval(acl)) add(l,2*ac,acl,(acl+acr)/2);
            if ((mid<(acr+acl)/2+0.5) && l.eval(acl)<=tree[ac].eval(acl)){
                add(tree[ac],2*ac,acl,(acl+acr)/2);
                history.back().pb(pair<int,line>{ac,tree[ac]});
                tree[ac]=l;
            }
            if ((mid>=(acr+acl)/2+0.5) && l.eval(acr)>=tree[ac].eval(acr)) add(l,2*ac+1,(acl+acr)/2+1,acr);
            if ((mid>=(acr+acl)/2+0.5) && l.eval(acr)<=tree[ac].eval(acr)){
                add(tree[ac],2*ac+1,(acl+acr)/2+1,acr);
                history.back().pb(pair<int,line>{ac,tree[ac]});
                tree[ac]=l;
            }
        }
    }

    int getmax(int obj, int ac, int acl, int acr){
        if (acl==acr) return tree[ac].eval(obj);
        if (obj<=(acl+acr)/2) return max(tree[ac].eval(obj),getmax(obj,2*ac,acl,(acl+acr)/2));
        else return max(tree[ac].eval(obj),getmax(obj,2*ac+1,(acl+acr)/2+1,acr));
    }

    void rollback(){
        for (pair<int,line> p:history.back()) tree[p.first]=p.second;
        history.pop_back();
    }

};
