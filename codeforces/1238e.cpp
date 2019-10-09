#include <bits/stdc++.h>

using namespace std;

const int L = 20; 
int d[L][L];
int dp[1<<L];

// rephrase || to f(pos) i.e. for cost[x][y], it must * (larger idx - smaller idx)
// so when set x in pos, for x's contribute, +/-pos*cost_y for those y before/after x, 
void solve() {
    int n,m;
    cin >> n >> m;
    string s; cin >> s;
    for (int i = 1; i < n; i++) {
        int x = s[i-1]-'a';
        int y = s[i] - 'a';
        if (x!=y)++d[x][y],++d[y][x];
    }
    memset(dp, 0x3f, sizeof dp);
    dp[0] = 0;
    const int MSK = 1<<m; 
    for (int msk = 0; msk < MSK; msk++) {
        int pos = __builtin_popcount(msk);
        for (int i = 0; i < m; i++) {
            if (msk & (1<<i)) continue;
            int cost = 0;
            for (int j = 0; j < m; j++) {
                if (msk & (1<<j)) cost += d[i][j];
                else cost -= d[i][j];
            }
            cost *= pos;
            dp[msk|(1<<i)] = min(dp[msk|(1<<i)], dp[msk] + cost);
        }
    }
    cout << dp[MSK-1];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
