#include <bits/stdc++.h>

using namespace std;

const int N = 2048; 
int dp[N][N];

void solve() {
    int n,h,l,r;
    cin >> n >> h >> l >> r;
    memset(dp, 0xc0, sizeof dp);
    dp[0][0] = 0;
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        for (int j = 0; j < h; j++) {
            for (int d:{x,x-1}) {
                int k = (j+d)%h;
                dp[i+1][k] = max(dp[i+1][k], dp[i][j] + (l<=k && k<=r));
            }
        }
    }
    cout << *max_element(dp[n], dp[n]+h);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
