#include <bits/stdc++.h>

using namespace std;


// process, make [j..i] all equal
void solve() {
    int n, K;
    cin >> n >> K;
    vector<int> a(n);
    for (auto& x: a) {
        cin >> x;
    }
    vector<vector<int>> d(n+1, vector<int> (n+1));
    for (int i = 0; i < n; i++) {
        unordered_map<int, int> cnt;
        int mx = 0;
        for (int j = i; j < n; j++) {
            cnt[a[j]]++;
            mx = max(mx, cnt[a[j]]);
            d[i][j+1] = mx;
        }
    }
    // +2 WA->AC, large-set. fk!!
    // fk, i realize n+2. cause K+1. but didn't even try, since small set passed. 
    // !!!! O(n^2 k) could pass, don't think too much!!!!
    // maybe alwasy global dp[N][N]?
    //
    // well, rank could be 75->71
    vector<vector<int>> dp(n+1, vector<int> (n+2, 10000));
    dp[0][0]= 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < i; j++) {
            for (int k = 0; k <= j; k++) {
                dp[i][k+1] = min(dp[i][k+1], dp[j][k] + i-j-d[j][i]);
            }
        }
    }
    int res = 10000;
    for (int i = 0; i <= K+1; i++) {
        res = min(res, dp[n][i]);
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T; cin >> T;
    for (int t = 1; t <= T; t++) {
        cout << "Case #" << t << ": ";
        solve();
        cout << "\n";
    }
    fflush(stdout);
}
