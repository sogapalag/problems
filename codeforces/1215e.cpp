#include <bits/stdc++.h>

using namespace std;
using ll=long long ;
ll d[20][20];
ll dp[1<<20];

// K_20 directed graph, one lowest cost path(19 edges)
void solve() {
    int n; cin >> n;
    vector<int> a[20];
    for (int i = 1; i <= n; i++) {
        int x; cin >> x;
        a[x-1].emplace_back(i);
    }
    // inversions
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 20; j++) {
            ll sum = 0;
            for (int x: a[j]) sum += lower_bound(a[i].begin(), a[i].end(), x) - a[i].begin();
            d[i][j] = sum;
        }
    }
    // for msk, choose i as occur before other set bits
    // since sub less msk, so increase-order process
    memset(dp, 0x3f, sizeof dp);
    const int MSK = 1<<20; 
    dp[0] = 0;
    for (int msk = 1; msk < MSK; msk++) {
        for (int i = 0; i < 20; i++) {
            if (msk & (1<<i)) {
                ll sum = 0;
                for (int j = 0; j < 20; j++) {
                    if (j!=i && (msk & (1<<j))) {
                        sum += d[i][j];
                    }
                }
                dp[msk] = min(dp[msk], dp[msk^(1<<i)] + sum);
            }
        }
    }
    cout << dp[MSK-1];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
