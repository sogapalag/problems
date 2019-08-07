#include <bits/stdc++.h>

using namespace std;

using ll=long long ;

// there're m settings 010..001
void solve() {
    int n, m, k;
    cin >> n >> m >> k;
    vector<ll> sum(n+1);
    sum[0] = 0;
    for (int i = 1; i <= n; i++) {
        cin >> sum[i];
        sum[i] += sum[i-1];
    }
    vector<vector<int>> cost(m, vector<int>(n+1));
    for (int j = 0; j < m; j++) {
        cost[j][0] = 0;
        for (int i = 1; i <= n; i++) {
            // 010..001, 1 when =j mod m
            cost[j][i] = cost[j][i-1] + (i%m == j);
        }
    }
    ll res = 0;
    // setting j's minimum
    vector<ll> mi(m, 0);
    for (int i = 1; i <= n; i++) {
        ll tmp = sum[i] - (ll)k * cost[i%m][i];
        res = max(res, tmp - mi[i%m]);
        for (int j = 0; j < m; j++) {
            mi[j] = min(mi[j], sum[i] - (ll)k*cost[j][i]);
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
