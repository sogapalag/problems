#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n,m,d;
    cin >> n >> m >> d;
    vector<pair<int, int>> a(n*m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int x; cin >> x; x--;
            a[x] = {i,j};
        }
    }
    vector<vector<int>> sum(d);
    for (int k = 0; k < d; k++) {
        sum[k].emplace_back(0);
        int crt = k;
        while (crt+d < n*m) {
            int cost = abs(a[crt+d].first-a[crt].first) + abs(a[crt+d].second-a[crt].second);
            sum[k].emplace_back(sum[k].back() + cost);
            crt += d;
        }
    }
    int q; cin >> q;
    while (q--) {
        int l, r;
        cin >> l >> r;
        l--; r--;
        int k = l%d;
        l/=d; r/=d;
        int res = sum[k][r] - sum[k][l];
        cout << res << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
