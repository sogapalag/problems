#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n; cin >> n;
    vector<int> a(n), b(n), c(n);
    for (auto& x: a) {
        cin >> x;
    }
    for (auto& x: b) {
        cin >> x;
    }
    for (auto& x: c) {
        cin >> x;
    }
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    sort(c.begin(), c.end());
    vector<long long> sum(n+1);
    sum[0] = 0;
    for (int i = 0; i < n; i++) {
        int k = lower_bound(a.begin(), a.end(), b[i]) - a.begin();
        sum[i+1] = sum[i] + k;
    }
    long long res = 0;
    for (int i = 0; i < n; i++) {
        int k = lower_bound(b.begin(), b.end(), c[i]) - b.begin();
        res += sum[k];
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
