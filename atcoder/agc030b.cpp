#include <bits/stdc++.h>

using namespace std;
using ll=long long;

// optim: RRR.... RLRL...RL..
void solve() {
    int M, n;
    cin >> M >> n;
    vector<int> a(n);
    for (auto& x: a) {
        cin >> x;
    }
    ll res = 0;
    for (int _ = 0; _ < 2; _++) {
        vector<ll> sum(n+1);
        for (int i = 1; i <= n; i++) {
            sum[i] = sum[i-1] + a[i-1];
        }
        for (int i = 1; i <= n; i++) {
            int x = i >> 1;
            int l = n - x;
            ll tmp = 0;
            if (i & 1) {
                tmp += (x*1ll*M - (sum[n] - sum[l])) * 2; // L
                tmp += (sum[l] - sum[l-x-1]) * 2 - a[l-1]; // R
            } else {
                tmp += (x*1ll*M - (sum[n] - sum[l])) * 2 - (M - a[l]); //L
                tmp += (sum[l] - sum[l-x]) * 2; // R
            }
            res = max(res, tmp);
        }

        reverse(a.begin(), a.end());
        for (auto& x: a) {
            x = M - x;
        }
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
