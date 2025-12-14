#include <string>
#include <vector>
#include <algorithm>
using namespace std;
struct StringHash {
    int base = 255;
    const int MOD = 1e9 + 7;
    int mul(int a, int b, int MOD) {return ((a % MOD) * (b % MOD)) % MOD;}
    int sub(int a, int b, int MOD) {return ((a % MOD) - (b % MOD) + MOD) % MOD;}
    int add(int a, int b, int MOD) {return ((a % MOD) + (b % MOD)) % MOD;}
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
		len = min(len, n - i);   //Note
		int j = i + len - 1;
		int ans;
		ans = sub(pre[j + 1], mul(pre[i], powb[len], MOD), MOD);
		return ans;
	}
};
