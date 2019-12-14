#include <bits/stdc++.h>

using namespace std;
using ll=long long;

const int N = 18; 
const int M = 105; 
ll dp[1<<N][M]; // #used which digits, remainder is k

void solve() {
    string s; int m;
    cin >> s >> m;
    int n = s.size();
    vector<int> a(n);
    vector<int> pw(n); int x = 1%m;
    for (int i = 0; i < n; i++) {
        a[i] = s[i]-'0';
        pw[i] = x;
        (x *= 10) %= m;
    }

    const int MSK = 1<<n; 
    vector<vector<int>> g(n+1);
    for (int msk = 0; msk < MSK; msk++) {
        g[__builtin_popcount(msk)].push_back(msk);
    }
    dp[0][0] = 1;
    for (int i = 0; i < n; i++) {
        for (int msk: g[i]) {
            for (int j = 0; j < n; j++) {
                if (msk>>j&1) continue;
                if (i == 0 && a[j] == 0) continue;
                for (int k = 0; k < m; k++) {
                    if (dp[msk][k]) {
                        dp[msk|1<<j][(k + a[j]*pw[n-i-1])%m] += dp[msk][k];
                    }
                }
            }
        }
    }
    ll rep = 1;
    vector<int> cnt(10, 0);
    for (int x: a) cnt[x]++;
    for (int c: cnt) {
        for (int i = 1; i <= c; i++) {
            rep *= i;
        }
    }
    cout << dp[MSK-1][0]/rep;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
