#include <bits/stdc++.h>

using namespace std;

// well, I saw some method using hash. ck ways from(1,1)->(i,j), (i,j)->(n,m). prod =? dp(n,m)
void solve() {
    int n,m;
    cin >> n >> m;
    vector<string> s(n+3, string(m+5, '#'));
    for (int i = 1; i <= n; i++) {
        cin >> &(s[i][1]);
    }
    vector<vector<bool>> dp(n+3, vector<bool>(m+5, false));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (i==1&&j==1) dp[1][1] = true;
            else {
                if (s[i][j]=='#') continue;
                dp[i][j] = dp[i-1][j] || dp[i][j-1];
            }
        }
    }
    if (!dp[n][m]) {
        cout << 0; return;
    }
    if (!dp[n-1][m] || !dp[n][m-1] || !dp[1][2] || !dp[2][1]) {
        cout << 1; return;
    }
    vector<vector<bool>> trk(n+1, vector<bool>(m+1, false));
    // up first
    int x=n,y=m;
    while (x!=1 || y!=1) { // || not &&. fk!!!!
        while (dp[x-1][y]) {
            x--;
            trk[x][y] = true;
        }
        if (dp[x][y-1]) {
            y--;
            trk[x][y] = true;
        }
    }
    trk[1][1]=false;
    // left first
    x=n,y=m;
    while (x!=1 || y!=1) {
        while (dp[x][y-1]) {
            y--;
            if (trk[x][y]) {
                cout << 1; return;
            }
        }
        if (dp[x-1][y]) {
            x--;
            if (trk[x][y]) {
                cout << 1; return;
            }
        }
    }
    cout << 2;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
