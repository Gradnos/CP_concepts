
#include <iostream>
#include <vector>
#include <assert.h>
#include <queue>


#define ll long long
#define vec vector
#define pb push_back
#define sz(v) (int)v.size()
#define fr(i,n) for(ll i = 0; i < n; i++)
#define F first
#define S second


using namespace std;

vec<int> z_function(string s) {
    int n = s.size();
    vec<int> z(n);
    int l = 0, r = 0;
    for(int i = 1; i < n; i++) {
        if(i < r) {
            z[i] = min(r - i, z[i - l]);
        }
        while(i + z[i] < n && s[z[i]] == s[i + z[i]]) {
            z[i]++;
        }
        if(i + z[i] > r) {
            l = i;
            r = i + z[i];
        }
    }
    return z;
}