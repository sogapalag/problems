#include <bits/stdc++.h>

using namespace std;
using ll=long long;

void solve() {
    int n, S;
    cin >> n >> S;
    mt19937_64 rng(time(0));
    unordered_map<ll, ll> cnt;
    vector<ll> hsh(S+1);
    for (int i = 0; i <= S; i++) {
        hsh[i] = rng();
    }
    vector<int> sz(n);
    vector<vector<int>> g(n);
    for (int i = 0; i < n; i++) {
        cin >> sz[i];
        for (int _ = 0; _ < sz[i]; _++) {
            int x; cin >> x;
            g[i].emplace_back(x);
        }
        int m = sz[i];
        // mark all non-empty subset
        for (int msk = 1; msk < (1<<m); msk++) {
            ll sum = 0;
            for (int j = 0; j < m; j++) {
                if (msk&(1<<j)) sum ^= hsh[g[i][j]];
            }
            cnt[sum]++;
        }
    }

    ll res = 0;
    // only all-have cannot be 
    for (int i = 0; i < n; i++) {
        ll sum = 0;
        for (int x:g[i]) sum ^= hsh[x];
        res += n - cnt[sum];
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T; cin >> T;
    for (int t = 1; t <= T; t++) {
        cout << "Case #" << t << ": ";
        solve();
        cout << "\n";
    }
    fflush(stdout);
}
