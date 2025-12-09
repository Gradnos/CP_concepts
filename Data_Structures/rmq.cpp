#include <vector>
using namespace std;

struct RMQ {
    int n;
    vector<vector<int>> st;
    vector<int> lg;
    const vector<long long>& a;

    int op(int i, int j) const {
        return (a[i] < a[j] ? i : j);
    }

    RMQ(const vector<long long>& arr) : n(arr.size()), a(arr) {
        if (n == 0) return;

        lg.assign(n + 1, 0);
        for (int i = 2; i <= n; i++) lg[i] = lg[i >> 1] + 1;

        int LOGN = lg[n];
        st.assign(LOGN + 1, vector<int>(n));

        for (int i = 0; i < n; i++) st[0][i] = i;

        for (int k = 1; k <= LOGN; k++) 
            for (int i = 0; i + (1 << k) <= n; i++) 
                st[k][i] = op(st[k - 1][i], st[k - 1][i + (1 << (k - 1))]);
    }

    // Query for the minimum elements index in the range [l, r] (inclusive)
    inline int qr(int l, int r) const {
        if (l > r) return 1e9; // Or handle error appropriately
        int k = lg[r - l + 1];
        return op( st[k][l], st[k][r - (1 << k) + 1]);
    }
};
    