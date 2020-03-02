#include <bits/stdc++.h>

using namespace std;
using ll=long long;
int n;
string s;
int a[111];

ll dp[111][111][111]; // profit to collapse a string with form: t + s[l..r), where t=s[l]* (x-1) 
ll calc(int l, int r, int x) {
    if (l >= r) return 0;
    ll& res = dp[l][r][x];
    if (res != -1) return res;
    res = max(res, a[x] + calc(l+1, r, 1)); // take the prefix
    for (int i = l+1; i < r; i++) {
        if (s[l] == s[i]) {
            // collapse s[l+1..i) to make a connect prefix+i 
            res = max(res, calc(l+1, i, 1) + calc(i, r, x+1));
        }
    }
    return res;
}

void solve() {
    cin >> n >> s;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    memset(dp, -1, sizeof dp);
    cout << calc(0, n, 1);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
