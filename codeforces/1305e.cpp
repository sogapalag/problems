#include <bits/stdc++.h>

using namespace std;
using ll=long long;

const int N = 5012; 
ll dp[N];

// canonical form  1 2 3 ... i-1  x ..  LARGE + k*N, 
void solve() {
    int n,m;
    cin >> n >> m;
    for (int i = 3; i <= n; i++) {
        dp[i] = dp[i-1] + (i-1)/2;
    }
    if (m > dp[n]) {
        cout << -1; return;
    }
    if (n < 3) {
        for (int i = 1; i <= n; i++) {
            cout << i << ' ';
        }
        return;
    }
    vector<int> a(n+2);
    iota(a.begin(), a.end(), 0);
    a[n+1] = 1e9;
    int i = 2;
    while (i <= n && dp[i] < m) {
        i++;
    }
    for (int k = n; k > i; k--) {
        // 2*N, 1*N might collide match shifted a[i]=x
        // -(n-k) can discard, won't collide
        a[k] = a[k+1] - 2*N - (n-k);
    }
    int r = m - dp[i-1];
    for (int x = i; ; x++) {
        int l = x - (i-1);
        int t = (i-l)/2;
        if (t == r) {
            a[i] = x; break;
        }
    }

    for (int i = 1; i <= n; i++) {
        cout << a[i] << ' ';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
