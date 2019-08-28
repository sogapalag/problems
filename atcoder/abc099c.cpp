#include <bits/stdc++.h>

using namespace std;

int yen[] = {1,6,36,216,1296,7776,46656,9,81,729,6561,59049};

const int N = 100005; 
int dp[N];

void solve() {
    int n; cin >> n;
    memset(dp, 0x3f, sizeof dp);
    dp[0] = 0;
    for (int i = 1; i <= n; i++) {
        for (int x: yen) {
            if (i < x) continue;
            dp[i] = min(dp[i], dp[i-x]+1);
        }
    }
    cout << dp[n];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
