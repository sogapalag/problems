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

void solve() {
    int n,a,b;
    cin >> n >> a >> b;
    string s; cin >> s;
    vector<int> dp(n+1, 1<<30);
    dp[0] = 0;
    for (int i = 0; i < n; i++) {
        dp[i+1] = min(dp[i+1], dp[i] + a);
        auto z = z_fn(s.substr(i) + s.substr(0,i));
        int len = 0;
        for (int j = n-i; j < n; j++) {
            len = max(len, z[j]);
        }
        len = min(len, n-i);
        for (int k = 1; k <= len; k++) {
            dp[i + k] = min(dp[i + k], dp[i] + b);
        }
    }
    cout << dp[n];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
