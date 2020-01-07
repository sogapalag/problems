#include <bits/stdc++.h>

using namespace std;

const int N = 110; 
int dp[N][N][2];
void mini(int& r, int x) {
    if (r > x) r = x;
}
// could greedy, omit
void solve() {
    int n; cin >> n;
    vector<int> a(n);
    int cnt[2] = {n/2, n - n/2};
    for (auto& x: a) {
        cin >> x;
        if (x) cnt[x&1]--;
    }
    memset(dp, 0x3f, sizeof dp);
    dp[0][0][0] = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < 2; k++) {
                if (a[i]) {
                    mini(dp[i+1][j][a[i]&1], dp[i][j][k] + (i>0 && (a[i]-k)%2!=0) );
                } else {
                    mini(dp[i+1][j][0], dp[i][j][k] + (i>0 && (k!=0)) );
                    mini(dp[i+1][j+1][1], dp[i][j][k] + (i>0 && (k!=1)));
                }
            }
        }
    }
    int res = min(dp[n][cnt[1]][0],dp[n][cnt[1]][1] );
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
