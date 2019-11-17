#include <bits/stdc++.h>

using namespace std;
using ll=long long;

void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    for (auto& x: a) {
        cin >> x;
    }
    sort(a.begin(), a.end());
    vector<ll> sum(n+1), res(n+1);
    for (int i = 0; i < n; i++) {
        sum[i+1] = sum[i] + a[i];
        res[i+1] = sum[i+1] + (i+1>=m? res[i+1-m] : 0);
        cout << res[i+1] << ' ';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
