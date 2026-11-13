#include <vector>
#include <string>
using namespace std;

// odd-palindrome radii (Manacher): d[i] = radius of the longest palindrome
// centered at i (spans [i-d[i]+1, i+d[i]-1], length 2*d[i]-1).
vector<int> manacher_odd(string s) {
    int n = (int)s.size();
    s = "$" + s + "^";
    vector<int> d(n + 2);
    int l = 0, r = 1;
    for (int i = 1; i <= n; i++) {
        d[i] = min(r - i, d[l + r - i]);
        while (s[i - d[i]] == s[i + d[i]]) d[i]++;
        if (i + d[i] > r) l = i - d[i], r = i + d[i];
    }
    return vector<int>(d.begin() + 1, d.end() - 1);
}

// both parities via separator '#': run manacher_odd on "#a#b#...#".
vector<int> manacher(string s) {
    string t;
    for (char c : s) { t += '#'; t += c; }
    t += '#';
    auto res = manacher_odd(t);
    return vector<int>(res.begin() + 1, res.end() - 1);
}
