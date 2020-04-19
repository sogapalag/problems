#include <bits/stdc++.h>

using namespace std;
using ll=long long;
const int N = 2048; 
ll dp[N][N];

// key, by dec x order, pick index left/right-most.
//  one can argue if not most, swap some won't be better
void solve() {
    int n; cin >> n;
    vector<pair<int, int>> a(n);
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        a[i] = {x,i};
    }
    sort(a.begin(), a.end());
    reverse(a.begin(), a.end());
    for (int i = 0; i < n; i++) {
        int x,k;
        tie(x,k) = a[i];
        for (int j = 0; j <= i; j++) {
            dp[i+1][j+1] = max(dp[i+1][j+1], dp[i][j] + x*1ll* abs(k - j));
            dp[i+1][j] = max(dp[i+1][j], dp[i][j] + x*1ll* abs(k - (n - (i-j) - 1)));
        }
    }
    ll res = *max_element(dp[n], dp[n]+n+1);
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
