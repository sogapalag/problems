#include <bits/stdc++.h>

using namespace std;


// key n > m => res = 0
// so O(n^2) fine
void solve() {
    int n,m;
    cin >> n >> m;
    vector<int> cnt(m);
    vector<int> a(n);
    for (int _ = 0; _ < n; _++) {
        int x; cin >> x;
        a[_] = x;
        cnt[x%m]++;
    }
    for (int i = 0; i < m; i++) {
        if (cnt[i] > 1) {
            cout << 0; return;
        }
    }
    sort(a.begin(), a.end());
    for (auto& x: a) {
        x %= m;
    }
    int res = 1;
    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            res *= (m + a[j] - a[i]);
            res %= m;
        }
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
