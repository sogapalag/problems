#include <bits/stdc++.h>

using namespace std;

const int N = 512;
const int W = 1e4+4; 
const int INF = 0x3f3f3f3f;

int p[N], w[N];
int dp[W];

void solve() {
    int T; cin >> T;
    while (T--) {
        int e, f;
        cin >> e >> f;
        int ta = f - e;
        int n;
        cin >> n;
        for (int i = 1; i <= n; i++) {
            cin >> p[i] >> w[i];
        }
        memset(dp, INF, sizeof dp);
        dp[0] = 0;// valid start point
        for (int i = 1; i <= ta; i++) {
            for (int j = 1; j <= n; j++) {
                if (w[j] <= i) {
                    dp[i] = min(dp[i], dp[i-w[j]] + p[j]);
                }
            }
        }
        int res = dp[ta];
        if (res < INF) {
            cout << "The minimum amount of money in the piggy-bank is " << res << ".\n";
        }else{
            cout << "This is impossible.\n";
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
