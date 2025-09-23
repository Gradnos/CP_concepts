#include<vector>
using namespace std;
#define pb push_back
#define sz(v) (int)v.size()
#define ll long long


// binary trie

int B = 30; //   1<<30 max bytes

struct node{
    int nxt[2] = {-1,-1};
    int cnt = 0;
    int id = 0;
};
vector<node> T;

void add(int x, int v, int id){
    for(int i = B; i>=0; i--){
        int b = (x>>i)&1;
        if(T[v].nxt[b] == -1){
            T[v].nxt[b] = sz(T);
            T.pb(node());
        }
        v = T[v].nxt[b];
        T[v].cnt++;
        if(i == 0){
            T[v].id = id;
        }
    }
};

void remove(int x, int v, int id){
    for(int i = B; i >= 0; i--){
        int b = (x>>i)&1;
        v = T[v].nxt[b];
        T[v].cnt--;
        if(i == 0) T[v].id = 0;
    }
};

int getMin(int x, int v){
    for(int i = B; i>= 0; i--){
        int b = (x>>i)&1;
        if(b==1){
            ll xx= 1;
        }
        if(T[v].nxt[b] != -1 && T[T[v].nxt[b]].cnt) v = T[v].nxt[b];
        else v = T[v].nxt[b^1];
    }
    return T[v].id;
}
