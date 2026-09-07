
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

vec<ll> prefix_function(string s)
{
    ll n = s.size();
    vec<ll> pi(n);
    // Iterate through the string starting from the second
    for (int i = 1; i < n; i++) {
        int j = pi[i - 1];
        while (j > 0 && s[i] != s[j]) j = pi[j - 1];
        if(s[i] == s[j]) j++;
        pi[i] = j;
    }
    return pi;
}
