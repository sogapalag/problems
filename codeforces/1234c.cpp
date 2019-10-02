#include <bits/stdc++.h>

using namespace std;
#define rep(i) for(int i=0;i<2;i++)
const int N = 2e5+10; 

bool dp[N][2];

// both L, 0->1, 1->0
// else, !L, j->j
void solve() {
    int n; cin >> n;
    string s[2];
    cin >> s[0];
    cin >> s[1];
    auto L = [](char x){
        return x > '2';
    };
    for (int i = 0; i <= n+2; i++) {
        rep(j) dp[i][j] = 0;
    }
    dp[0][0] = 1;
    for (int i = 0; i < n; i++) {
        if (L(s[0][i]) && L(s[1][i])) {
            rep(j) dp[i+1][j] |= dp[i][j^1];
        } else {
            rep(j) if(!L(s[j][i])) dp[i+1][j] |= dp[i][j];
        }
    }
    auto res = dp[n][1] ? "YES\n" : "NO\n";
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t; cin >> t;
    while(t--) solve();
    cout << endl;
}
