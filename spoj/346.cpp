#include <bits/stdc++.h>

using namespace std;


void solve() {
    const int N = 1e7+7; 
    vector<int> dp(N);
    dp[0] = 0;
    for (int i = 1; i < N; i++) {
        dp[i] = max(i, dp[i/2] + dp[i/3] + dp[i/4]);
    }
    function<long long (int)> rec = [&](int x) -> long long {
        if (x < N) {
            return dp[x];
        }
        return max(rec(x/2) + rec(x/3) + rec(x/4), (long long)x);
    };
    int n;
    while (cin >> n) {
        cout << rec(n) << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
