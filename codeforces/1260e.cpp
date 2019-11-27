#include <bits/stdc++.h>

using namespace std;
using ll=long long;

const int L = 18;
const int N = (1<<L) + 10; 
ll dp[N][L+1];

// #winner constraint in prefix-range
void solve() {
    int n; cin >> n;
    vector<int> a(n+1);
    int k;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        if (a[i] == -1) k = i;
    }
    for (int i = 1; i <= k; i++) {
        a[i] = 0;
    }
    memset(dp, 0x3f, sizeof dp);
    dp[1][0] = 0;
    // at most w winners(to choose with 1) till i,
    for (int i = 2; i <= n; i++) {
        int w = 31 - __builtin_clz(i);
        dp[i][0] = dp[i-1][0];
        for (int j = 1; j <= w; j++) {
            dp[i][j] = min(dp[i-1][j], dp[i-1][j-1] + a[i]);
        }
    }
    int w = 31 - __builtin_clz(n);
    cout << dp[n][w];
}

// j-th winner constraint in suffix range
void solve2() {
    int n; cin >> n;
    vector<int> a(n+1);
    int k;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        if (a[i] == -1) k = i;
    }
    for (int i = 1; i <= k; i++) {
        a[i] = 0;
    }
    int w = 31 - __builtin_clz(n);
    multiset<int> s;
    ll res = a[n]; // as winner of n/2
    int i = n-1;
    // each next round largest x could be candidates. dual version of solve
    for (int j = w-1; j >= 1; j--) {
        for (int x = 1<<j; x > 0; i--,x--) {
            s.insert(a[i]);
        }
        res += *s.begin();
        s.erase(s.begin());
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve2();
    cout << endl;
}
