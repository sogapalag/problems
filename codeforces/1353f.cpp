#include <bits/stdc++.h>

using namespace std;
using ll=long long;
const int N = 102; 
ll a[N][N];
ll dp[N][N];
// note for a path, ai = z+i => z = ai-i
// so replace a = a-i, path cost is sum(a-z), z=min{a}
// note z must be some a, so candidate<=n^2
void solve() {
    int n,m;
    cin >> n >> m;
    vector<ll> candi;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> a[i][j];
            a[i][j] -= i+j;
            candi.push_back(a[i][j]);
        }
    }
    sort(candi.begin(), candi.end());
    candi.erase(unique(candi.begin(), candi.end()), candi.end());
    ll res = 1ll<<61;
    for (ll mi:candi) if(mi<=a[0][0]){
        memset(dp, 0x3f, sizeof dp);
        dp[0][1] = 0;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) if(mi<=a[i-1][j-1]){
                for (int k:{0,1}) {
                    int x = i-k;
                    int y = j-(k^1);
                    dp[i][j] = min(dp[i][j], dp[x][y] + (a[i-1][j-1] - mi));
                }
            }
        }
        res = min(res, dp[n][m]);
    }
    cout << res << "\n";
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
