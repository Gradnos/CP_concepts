#include <string>
#include <vector>
#include <algorithm>
using namespace std;
#define ll long long

struct StringHash {
    int base = 255;
    const int MOD = 1e9 + 7;
    // a, b must be long long so the product does not overflow 32-bit int.
    int mul(ll a, ll b, ll MOD) { return ((a % MOD) * (b % MOD)) % MOD; }
    // args are already < MOD, so a single conditional is enough (faster than %).
    int sub(int a, int b, int MOD) { int ans = a - b; if (ans < 0) ans += MOD; return ans; }
    int add(int a, int b, int MOD) { int ans = a + b; if (ans >= MOD) ans -= MOD; return ans; }
	string s;
	int n;
	vector<int> pre; //hash of prefix of length i.
	vector<int> powb; //base ^ i (MOD MODs)
	StringHash(string _s = "") : s(_s) {
		n = s.size();
		pre.resize(n + 1);
		powb.resize(n + 1);
		pre[0] = 0;
		powb[0] = 1;
		for (int i = 0; i < n; i++) {
			pre[i + 1] = add(mul(pre[i], base, MOD), s[i], MOD);
			powb[i + 1] = mul(powb[i], base, MOD);
		}
	}
	int hash(int i, int len) {
		if (!len) return 0;
		len = min(len, n - i);
		int j = i + len - 1;
		int ans;
		ans = sub(pre[j + 1], mul(pre[i], powb[len], MOD), MOD);
		return ans;
	}
};
