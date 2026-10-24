// usage:
//   vector<vector<int>> a(n, vector<int>(m + 1));
//   ... fill coefficients a[i][j] and RHS a[i][m] ...
//   auto [status, x] = gauss(a);
//   if (status == 0) -> no solution;
//   if (status == 2) -> free variables, x = particular solution (free = 0);

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int mod = 998244353;
int add(int a, int b){ int r = a + b; return r < mod ? r : r - mod; }
int sub(int a, int b){ int r = a - b; return r < 0 ? r + mod : r; }
int mul(int a, int b){ return int((ll)a * b % mod); }
int pw(int a, int b){ int r = 1; for(; b; b >>= 1, a = mul(a, a)) if(b & 1) r = mul(r, a); return r; }
int divide(int a, int b){ return mul(a, pw(b, mod - 2)); }   // b != 0 (Fermat inverse)
bool isZero(int a){ return a == 0; }
bool equal(int a, int b){ return a == b; }

const double EPS = 1e-12;
double add(double a, double b){ return a + b; }
double sub(double a, double b){ return a - b; }
double mul(double a, double b){ return a * b; }
double divide(double a, double b){ return a / b; }
bool isZero(double a){ return fabs(a) < EPS; }
bool equal(double a, double b){ return fabs(a - b) < EPS; }

template<class T>
pair<int, vector<T>> gauss(vector<vector<T>> a){
    int n = (int)a.size();
    int m = (int)a[0].size() - 1;

    vector<int> where(m, -1);
    for(int col = 0, row = 0; col < m && row < n; ++col){
        int sel = row;
        for(int i = row; i < n; ++i) 
            if(abs(a[i][col]) > abs(a[sel][col]))
                sel = i;
        if(isZero(a[sel][col]))
            continue;
        swap(a[sel], a[row]);
        where[col] = row;

        for(int i = 0; i < n; ++i)
            if(i != row){
                T c = divide(a[i][col], a[row][col]);
                for(int j = col; j <= m; ++j)
                    a[i][j] = sub(a[i][j], mul(a[row][j], c));
            }
        ++row;
    }

    vector<T> ans(m);
    for(int col = 0; col < m; ++col)
        if(where[col] != -1)
            ans[col] = divide(a[where[col]][m], a[where[col]][col]);

    for(int i = 0; i < n; ++i){
        T got = 0;
        for(int j = 0; j < m; ++j)
            got = add(got, mul(ans[j], a[i][j]));
        if(!equal(got, a[i][m]))
            return {0, ans};
    }
    for(int col = 0; col < m; ++col)
        if(where[col] == -1)
            return {2, ans};
    return {1, ans};
}
