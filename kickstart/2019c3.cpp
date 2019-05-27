#include <bits/stdc++.h>

using namespace std;

const int INF = 0x3f3f3f3f;
const int N = 1001; 

int dp[N][N][2];

// dp[i][k] :~i types, collected k. [0/1] already use 1/2 option
void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> p(n+1);
    vector<int> a(n+1);
    for (int i = 1; i <= n; i++) {
        cin >> p[i];
    }
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    vector<int> C[N];
    for (int i = 0; i < N; i++) {
        C[i].emplace_back(0);
    }
    for (int i = 1; i <= n; i++) {
        C[a[i]].emplace_back(p[i]);
    }
    for (int i = 0; i < N; i++) {
        sort(C[i].begin(), C[i].end());
    }
    memset(dp, INF, sizeof dp);
    dp[0][0][0] = 0;
    for (int i = 1; i < N; i++) {
        int sz = C[i].size();
        for (int j = 0; j < sz; j++) {
            for (int x = 0; x <= k-j; x++) {
                dp[i][x+j][0] = min(dp[i][x+j][0], dp[i-1][x][0] + 2*C[i][j]);
                dp[i][x+j][1] = min(dp[i][x+j][1], dp[i-1][x][1] + 2*C[i][j]);
                dp[i][x+j][1] = min(dp[i][x+j][1], dp[i-1][x][0] + C[i][j]);
            }
        }
    }
    cout << dp[N-1][k][1];
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
