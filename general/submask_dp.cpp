#include <vector>
using namespace std;

// dp[mask] = sum of dp[sub] over all submasks sub of mask. O(k * 2^k).
void submaskSum(vector<int>& dp, int k) {
    for (int i = 0; i < k; i++)
        for (int mask = 0; mask < (1 << k); mask++)
            if (mask & (1 << i)) dp[mask] += dp[mask ^ (1 << i)];
}

// iterate over all non-empty submasks of mask (empty handled separately).
void forEachSubmask(int mask) {
    for (int sub = mask; sub; sub = (sub - 1) & mask) {
        // use `sub`
    }
}
