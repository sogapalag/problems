#include <bits/stdc++.h>

using namespace std;

const int N = 50000*24 + 8; 
bitset<N> dp[25*2][25]; // first i, choose j, could make sum?

// must be pattern
// a0 ->....->
// <-...<-.... a1
// and best max, always be a0 + sum1, or sum0+a1
// so despite a0,a1. after dp, we find minmax (i, sum-i), (n--)
// then restore path
void solve() {
    int n; cin >> n;
    vector<int> a(2*n);
    int sum = 0;
    for (auto& x: a) {
        cin >> x;
        sum += x;
    }
    sort(a.begin(), a.end());
    vector<int> res[2];
    res[0].emplace_back(a[0]);
    res[1].emplace_back(a[1]);
    sum -= a[0]+a[1];
    a.erase(a.begin(), a.begin()+2);
    n--;

    dp[0][0][0] = 1;
    for (int i = 0; i < 2*n; i++) {
        int x = a[i];
        dp[i+1][0] = dp[i][0];
        for (int j = 0; j <= min(i,n-1); j++) {
            dp[i+1][j+1] = dp[i][j+1] | (dp[i][j] << x); 
        }
    }
    
    int mi = 1<<30;
    for (int i = 0; i <= sum; i++) {
        if (dp[2*n][n][i]) mi = min(mi, max(i, sum-i));
    }

    int j = n-1;
    for (int i = 2*n-1; i >= 0; i--) {
        int x = a[i];
        if (j >= 0 && mi >= x && dp[i][j][mi - x]) {
            res[0].emplace_back(x);
            mi -= x;
            j--;
        } else {
            res[1].emplace_back(x);
        }
    }
    sort(res[0].begin(), res[0].end());
    sort(res[1].begin(), res[1].end());
    reverse(res[1].begin(), res[1].end());
    for (auto& x: res[0]) {
        cout << x << ' ';
    }cout << "\n";
    for (auto& x: res[1]) {
        cout << x << ' ';
    }cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
