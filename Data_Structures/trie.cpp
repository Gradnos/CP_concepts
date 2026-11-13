#include <vector>
using namespace std;

// Binary trie (B bits). Caller creates the root: T.pb(node()); then add(x, 0, id).
int B = 30;
struct node {
    int nxt[2] = {-1, -1};
    int cnt = 0;
    int id = 0;
};
vector<node> T;

void add(int x, int v, int id) {
    for (int i = B; i >= 0; i--) {
        int b = (x >> i) & 1;
        if (T[v].nxt[b] == -1) { T[v].nxt[b] = (int)T.size(); T.push_back(node()); }
        v = T[v].nxt[b];
        T[v].cnt++;
    }
    T[v].id = id;
}

void remove(int x, int v) {
    for (int i = B; i >= 0; i--) {
        v = T[v].nxt[(x >> i) & 1];
        T[v].cnt--;
    }
}

// id of the stored element minimizing xor with x (trie must be non-empty).
int getMin(int x, int v) {
    for (int i = B; i >= 0; i--) {
        int b = (x >> i) & 1;
        if (T[v].nxt[b] != -1 && T[T[v].nxt[b]].cnt) v = T[v].nxt[b];
        else v = T[v].nxt[b ^ 1];
    }
    return T[v].id;
}
