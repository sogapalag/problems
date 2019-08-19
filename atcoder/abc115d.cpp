#include <bits/stdc++.h>

using namespace std;

using ll=long long ;

ll dp[60][2];

void solve() {
    int n; ll x;
    cin >> n >> x;
    const int P = 0, B = 1;
    dp[0][P] = 1; dp[0][B] = 0;
    for (int i = 0; i < 51; i++) {
        dp[i+1][P] = 2*dp[i][P] + 1;
        dp[i+1][B] = 2*dp[i][B] + 2;
    }
    ll res = 0;
    while (x) {
        if (!n) {res+=1; break;}
        x--; if (!x) break;
        ll y = dp[n-1][P] + dp[n-1][B];
        if (x <= y) {
            n--; continue;
        }
        res += dp[n-1][P] + 1; x -= y + 1; if (!x) break;
        if (x <= y) {
            n--; continue;
        }
        res += dp[n-1][P]; break;
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
