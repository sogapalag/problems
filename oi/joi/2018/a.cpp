#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n,k;
    cin >> n >> k;
    vector<int> a(n);
    for (auto& x: a) cin >> x;
    vector<int> d;
    // saving max unused
    for (int i = 1; i < n; i++) {
        d.push_back(a[i] - a[i-1]-1);
    }
    int res = a[n-1] - a[0] + 1;
    sort(d.begin(), d.end(), greater<int>());
    for (int _ = 0; _ < k-1; _++) {
        res -= d[_];
    }
    cout << res << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
