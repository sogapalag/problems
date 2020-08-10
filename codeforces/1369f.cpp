#include <bits/stdc++.h>

using namespace std;
using ll=long long;

// 0 first, 1 second
int win(ll s, ll e) {
    // LWW..WW
    if (s > e) return 0;
    if (s == e) return 1;
    if (e&1) return s&1;
    // LW..LW L
    if (e/2 < s) return ((e-s)&1) ^ 1;
    // WW..W
    if (e/4 < s) return 0;
    return win(s, e/4);
}

// 0 first, 1 second
int lose(ll s, ll e) {
    // WLL..LL
    if (s > e) return 1;
    if (s == e) return 0;
    // WW..WW W
    if (2*s > e) return 0;
    return win(s, e/2);
}


void solve() {
    int n; cin >> n;
    vector<array<int,2>> dp(n);
    for (int i = 0; i < n; i++) {
        ll s, e;
        cin >> s >> e;
        dp[i][0] = win(s, e);
        dp[i][1] = lose(s, e);
    }
    // can decide move as first/second
    int fi = 1, se = 0;
    for (int i = 0; i < n; i++) {
        if (fi == se) break;
        if (fi) {
            fi = dp[i][1]^1;
            se = dp[i][0]^1;
        } else {
            fi = dp[i][1];
            se = dp[i][0];
        }
    }
    // note loser next round first
    cout << se << ' ' << fi;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
