#include <bits/stdc++.h>

using namespace std;

const int N = 100005; 
int dp[2][N]; // [i][j]=min-index of b, use i op-1, last use at a[j],
void solve() {
    int n,m,s,e;
    cin >> n >> m >> s >> e;
    vector<int> a(n);
    for (auto& x: a) {
        cin >> x;
    }
    vector<vector<int>> pos(N);
    for (int i = 1; i <= m; i++) {
        int x; cin >> x;
        pos[x].push_back(i);
    }
    
    int crt = 0;
    dp[0][0] = 0;
    int best = 0;
    for (int i = 1; i <= s/e; i++) {
        int nxt = crt ^ 1;
        memset(dp[nxt], 0x3f, sizeof dp[nxt]);
        for (int j = 0; j < n; j++) {
            int& res = dp[nxt][j+1];
            res = min(res, dp[nxt][j]);
            auto it = upper_bound(pos[a[j]].begin(), pos[a[j]].end(), dp[crt][j]);
            if (it != pos[a[j]].end()) {
                res = min(res, *it);
            }
            if (i*e + j+1 + res <= s) best = i;
        }
        crt ^= 1;
    }
    cout << best;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
