#include <bits/stdc++.h>

using namespace std;

int dp[2][2];
void solve() {
    string s; cin >> s;
    while (s.back() == '0') {
        s.pop_back();
    }
    s = "0" + s;
    int n = s.size();
    // WA
    //vector<int> sum(n + 1);
    //for (int i = 1; i <= n; i++) {
    //    sum[i] = sum[i-1] + (s[i-1] - '0');
    //}
    //int res = sum[n];
    //int cry = min(10 - (s[n-1] - '0'), (s[n-1]-'0') + 1);
    //for (int i = n-2; i >= 0; i--) {
    //    int x = s[i] - '0';
    //    if (x == 9) continue;
    //    res = min(res, 1 + sum[i+1] + cry);
    //    cry += min(9-x, x+2);
    //}
    //cout << res;
    
    int crt = 0;
    for (int _ = 0; _ < n; _++) {
        int x = s[_]-'0';
        int nxt = crt ^ 1;
        memset(dp[nxt], 0x3f, sizeof dp[nxt]);
        for (int i = 0; i < 10; i++) {
            for (int j: {0,1}) if (j || x<=i) {
                int d = j*10 + (i-x);
                dp[nxt][0] = min(dp[nxt][0], dp[crt][j] + d + i);
                if(d)dp[nxt][1] = min(dp[nxt][1], dp[crt][j] + d-1 + i);
            }
        }
        crt ^= 1;
    }
    cout << dp[crt][0];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
