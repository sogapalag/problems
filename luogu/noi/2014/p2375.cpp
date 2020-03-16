#include <bits/stdc++.h>

using namespace std;

// z[i] = len of lcp of s, s[i..]; lcp(longest common prefix)
vector<int> z_fn(const string& s) {
    int n = s.size();
    vector<int> z(n, 0);
    for (int i = 1, l = 0, r = 0; i < n; i++) {
        if (i <= r)
            z[i] = min(r-i+1, z[i-l]);
        while (i+z[i] < n && s[z[i]] == s[i+z[i]]) {
            z[i]++;
        }
        if (i+z[i]-1 > r) {
            l = i; r = i+z[i]-1;
        }
    }
    return z;
}

// key, find max-len with pref=suff, dp/res += dp[i-l]
//  since len <= max-len match, are indeed dp[i-l]
// and l is inc. by two-pointer. proof omit
void solve() {
    string s; cin >> s;
    auto z = z_fn(s);
    int n = z.size();
    vector<int> dp(n, 1);
    // relax intersect condition
    // i.e. dp[i] := #prefix=suffix in s[0..i], include itself.
    for (int i = 1, l = 1; i < n; i++) {
        while (l <= i && z[l] < i-l+1) {
            l++;
        }
        if (l <= i) dp[i] += dp[i-l];
    }
    vector<int> res(n);
    for (int i = 1, l = 1; i < n; i++) {
        l = max(l, i/2+1); // not intersect
        while (l <= i && z[l] < i-l+1) {
            l++;
        }
        if (l <= i) res[i] += dp[i-l];
    }
    const int P = 1e9+7; 
    int ans = 1;
    for (auto& x: res) {
        ans = (ans * 1ll * (x+1)) % P;
    }
    cout << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T; cin >> T;
    for (int t = 0; t < T; t++) {
        solve();
    }
    return 0;
}
