int main(){
    int k = 20;
    int dp[1<<20];
    // dp[x] = sum(dp[i]) i is a submask of x || O (k * 2^k)
    for (int i = 0; i < k; i++) {
        for (int mask = 0; mask < (1 << k); mask++) {
            if (mask & (1 << i)) {
                dp[mask] += dp[mask ^ (1 << i)];
            }
        }
    }
    int mask = 0x10101001;
    int sum = 0;
    // iterate over all submasks of mask || O(3^k)
    for (int sub = mask; sub; sub = (sub - 1) & mask) {
        sum += sub;
    }
}
